/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


const fs = require('fs');
let validator = require('jsonschema').Validator;
let v = new validator();
let use_secrets = false;

const header_file = fs.readFileSync(`${__dirname}/transpiler_template.h`, 'utf8');
const keymap_json = fs.readFileSync(`${__dirname}/../t_keymap.json`, 'utf8');

const secrets_json_path = `${__dirname}/../secrets.json`;
const secrets_template_path = `${__dirname}/keys_template.h`;
let secrets, key_file;
if (fs.existsSync(secrets_json_path) && fs.existsSync(secrets_template_path)) {
  use_secrets = true;

  const secret_json = fs.readFileSync(secrets_json_path, 'utf8');
  secrets = JSON.parse(secret_json);

  key_file = fs.readFileSync(secrets_template_path, 'utf8');
}

const keymap = JSON.parse(keymap_json);

const keycodeSchema = {
  "type": "array",
  "items": {
    "properties": {
      "alias": { "type": "string" },
      "action": { "type": "string" }
    },
    "required": ["alias", "action"]
  }
};

const layerSchema = {
  "id": "/layer",
  "type": "array",
  "items": {
    "properties": {
      "layer_label": {"type": "string"},
      "layer": {
        "type": "array",
        "items": { 
          "propierties":{
            "type": "array",
            "items": {"type": "string"},
          },
          "minItems": 3,
          "maxItems": 3
        }, 
        "minItems": 13,
        "maxItems": 13
      }
    },
    "required": [ "layer_label", "layer" ]
  },
  "minItems": 1,
}

const completeSchema = {
  "id": "/keymap",
  "type": "object",
  "properties": {
    "totp_layer": { "type": "integer" },
    "keycodes": {"$ref": "/keycode"},
    "keymap": {"$ref": "/layer"},
  },
  "required": ["keymap"]
}

v.addSchema(keycodeSchema, '/keycode');
v.addSchema(layerSchema, '/layer');

const res = v.validate(keymap, completeSchema);

if(!res.valid){
  console.log(res);
  return;
}

// Get OTP Layer
const totp_layer = keymap.totp_layer;

// Get layer number
const layer_count = keymap.keymap.length;

// Get custom keycodes 
const keycodes_enum = keymap.keycodes.map(k => k.alias).join();

// Transpile custom keycodes
const custom_keycodes = keymap.keycodes.map(k => {
  return `case ${k.alias}: SEND_STRING(${k.action}); break;`;
}).join(' ');

// Get layer strings
const layer_string = keymap.keymap.map(l => {
  return `"${l.layer_label}"`
}).join();

// Get keymap strings
const keymap_string = keymap.keymap.map(l => {

  // Special case: encoder button
  let rows_strings = [`{"","","${l.layer[0][1]}"}`];

  for(let row = 0; row < 4; row++)
  {
    let col_strings = [];
    for(let col = 0; col < 3; col++)
    {
      let index = (row * 3) + col + 1;
      col_strings.push(`"${l.layer[index][1]}"`);
    }

    rows_strings.push(`{${col_strings.join()}}`);
  }

  return `{${rows_strings.join()}}`;
}).join();

// Get indicator
const indicators = keymap.keymap.map(l => {

  let rows_strings = [];

  for(let row = 0; row < 4; row++)
  {
    let col_strings = [];
    for(let col = 0; col < 3; col++)
    {
      let index = (row * 3) + col + 1;
      col_strings.push(`{${l.layer[index][0]}}`);
    }

    rows_strings.push(`{${col_strings.join()}}`);
  }

  return `{${rows_strings.join()}}`;
}).join();

// Get keymap
const t_keymap = keymap.keymap.map((l, index) => {
  const keys = l.layer.map(k => k[2]).join();
  return `[${index}] = LAYOUT(${keys})`;
}).join();

// Replace layer no
let new_file;
new_file = header_file.replace("{{trans_layer_no}}", layer_count);
new_file = new_file.replace("{{trans_keycodes_enum}}", keycodes_enum);
new_file = new_file.replace("{{trans_custom_keycodes}}", custom_keycodes);
new_file = new_file.replace("{{trans_layer_string}}", layer_string);
new_file = new_file.replace("{{trans_keymap_string}}", keymap_string);
new_file = new_file.replace("{{trans_indicators}}", indicators);
new_file = new_file.replace("{{trans_keymap}}", t_keymap);
new_file = new_file.replace("{{totp_layer}}", totp_layer);

fs.writeFile(`${__dirname}/../transpiler.h`, new_file, 'utf-8', function (err) {
  if(err)
    console.log(err);
});

if(use_secrets) {
  let new_sfile;
  new_sfile = key_file.replace("{{totp_keys}}", secrets.keys.join());
  new_sfile = new_sfile.replace("{{password}}", `"${secrets.password}"`);
  new_sfile = new_sfile.replace("{{password_len}}", secrets.password.length);

  fs.writeFile(`${__dirname}/../keys.h`, new_sfile, 'utf-8', function (err) {
    if(err)
      console.log(err);
  });
  
}

console.log("Done!");