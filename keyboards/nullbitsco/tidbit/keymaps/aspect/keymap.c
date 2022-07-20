/* Copyright 2021 Chris Tanaka <https://github.com/christanaka>
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

#include "keymap.h"
#include "bongo.h"
#include "status.h"

enum layers {
    _BASE = 0,
    _VIA1,
    _VIA2,
    _VIA3,
    _VIA4,
    _VIA5,
    _VIA6,
    _VIA7
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
                           KC_PSLS, KC_PAST, KC_PMNS,
  KC_VOLD, KC_VOLU, KC_P7, QK_BOOT, EE_CLR,  KC_PPLS,
  KC_TRNS, KC_TRNS, KC_P4, KC_P5,   KC_P6,   KC_PPLS,
  KC_TRNS, KC_TRNS, KC_P1, KC_P2,   KC_P3,   KC_PENT,
  KC_TRNS, KC_TRNS, KC_P0, KC_P0,   KC_PDOT, KC_PENT
  ),

  [_VIA1] = LAYOUT(
                 ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___
  ),

  [_VIA2] = LAYOUT(
                 ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___
  ),

  [_VIA3] = LAYOUT(
                 ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___
  ),

  [_VIA4] = LAYOUT(
                 ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___
  ),

  [_VIA5] = LAYOUT(
                 ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___
  ),

  [_VIA6] = LAYOUT(
                 ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___
  ),

  [_VIA7] = LAYOUT(
                 ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___,
  ___, ___, ___, ___, ___, ___
  ),
};

void keyboard_post_init_user(void) {
    debug_enable=true;
}


bool oled_task_user(void) {
  bongo_render(0, 0);

  oled_write("ASPECT94", false);
  status_render_layer(0, 1);
  status_render_caps_lock(0, 2);

  return false;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bongo_process_record(record);
    if (record->event.pressed) {
        switch (keycode) {
            case AP_NEW:
                SEND_STRING(SS_LCTL("n"));
                break;
            case AP_OPEN:
                SEND_STRING(SS_LCTL("o"));
                break;
            case AP_CLOSE:
            case AP_PINC:
                SEND_STRING(SS_LCTL("w"));
                break;
            case AP_SAVE:
                SEND_STRING(SS_LCTL("s"));
                break;
            case AP_SAVEAS:
                SEND_STRING(SS_LCTL(SS_LSFT("s")));
                break;
            case AP_PRINT:
            case AP_PIN:
                SEND_STRING(SS_LCTL("p"));
                break;
            case AP_QUIT:
                SEND_STRING(SS_LCTL("q"));
                break;
            case AP_COPY:
                SEND_STRING(SS_LCTL("c"));
                break;
            case AP_CUT:
                SEND_STRING(SS_LCTL("x"));
                break;
            case AP_UNDO:
                SEND_STRING(SS_LCTL("z"));
                break;
            case AP_REDO:
                SEND_STRING(SS_LCTL(SS_LSFT("z")));
                break;
            case AP_PASTE:
                SEND_STRING(SS_LCTL("v"));
                break;
            case AP_DUPL:
            case AP_DESEL:
                SEND_STRING(SS_LCTL("d"));
                break;
            case AP_SELALL:
                SEND_STRING(SS_LCTL("a"));
                break;
            case AP_SELINV:
                SEND_STRING(SS_LCTL(SS_LALT("i")));
                break;
            case AP_SELLAY:
                SEND_STRING(SS_LCTL(SS_LALT("a")));
                break;
            case AP_ZOOMP:
                SEND_STRING(SS_LCTL("+"));
                break;
            case AP_ZOOMN:
                SEND_STRING(SS_LCTL("-"));
                break;
            case AP_FITSCRN:
                SEND_STRING(SS_LCTL("0"));
                break;
            case AP_ACTUAL:
                SEND_STRING(SS_LCTL(SS_LALT("0")));
                break;
            case AP_GRID:
                SEND_STRING(SS_LCTL("'"));
                break;
            case AP_GUIDES:
                SEND_STRING(SS_LCTL(";"));
                break;
            case AP_GROUP:
                SEND_STRING(SS_LCTL("g"));
                break;
            case AP_AE_DIV:
            case AP_UNGROUP:
                SEND_STRING(SS_LCTL(SS_LSFT("d")));
                break;
            case AP_PASTEF:
                SEND_STRING(SS_LCTL("f"));
                break;
            case AP_COLBAL:
            case AP_PASTEB:
            case AP_TOOL:
                SEND_STRING(SS_LCTL("b"));
                break;
            case AP_PASTEUB:
                SEND_STRING(SS_LCTL(SS_LSFT("v")));
                break;
            case AP_LEVELS:
                SEND_STRING(SS_LCTL("l"));
                break;
            case AP_CURVES:
                SEND_STRING(SS_LCTL("m"));
                break;
            case AP_HUESAT:
                SEND_STRING(SS_LCTL("u"));
                break;
            case AP_NEWLAY:
                SEND_STRING(SS_LCTL(SS_LSFT("n")));
                break;
            case AP_LAYCPY:
                SEND_STRING(SS_LCTL("j"));
                break;
            case AP_LAYCUT:
                SEND_STRING(SS_LCTL(SS_LSFT("j")));
                break;
            case AP_CLIPMSK:
                SEND_STRING(SS_LCTL(SS_LALT("g")));
                break;
            case AP_BRINGF:
                SEND_STRING(SS_LCTL("]"));
                break;
            case AP_SENDF:
                SEND_STRING(SS_LCTL(SS_LSFT("]")));
                break;
            case AP_BRINGB:
                SEND_STRING(SS_LCTL("["));
                break;
            case AP_SENDB:
                SEND_STRING(SS_LCTL(SS_LSFT("[")));
                break;
            case AP_MERGE:
                SEND_STRING(SS_LCTL("e"));
                break;
            case AP_UNMERGE:
                SEND_STRING(SS_LCTL(SS_LSFT("g")));
                break;
            case AP_TEXT:
                SEND_STRING(SS_LCTL("t"));
                break;
            case AP_AE_VOL:
                SEND_STRING("l" SS_DELAY(20) "l");
                break;
            case AP_AE_ME:
                SEND_STRING(SS_LCTL(SS_LALT("m")));
                break;
            case AP_AE_LAYER:
                SEND_STRING("u" SS_DELAY(20) "u");
                break;

        }
    }
    return true;
}
