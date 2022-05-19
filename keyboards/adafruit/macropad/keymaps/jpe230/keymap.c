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

#include "jpe230.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MEDIA] = LAYOUT(
                         RGB_TOG,
        __xxx__, KC_VOLU, __xxx__,
        __xxx__, KC_VOLD, __xxx__,
        __xxx__, KC_MUTE, __xxx__,
        KC_MPRV, KC_MPLY, KC_MNXT
    ),
    [TEAMS] = LAYOUT(
                         RGB_TOG,
        KC_VOLU, TM_AVC, TM_MUT,
        KC_VOLD, TM_AAC, TM_VID,
        KC_MUTE, TM_DC,  __xxx__,
        __xxx__, TM_EC,  __xxx__
    ),
    [EDGE] = LAYOUT(
                          RGB_TOG,
        ED_ZOP,  ED_NEWT, KC_VOLU,
        ED_ZON,  ED_NTAB, KC_VOLD,
        ED_CTAB, ED_PTAB, KC_MUTE,
        KC_MPRV, KC_MPLY, KC_MNXT
    ),
    [VSCODE] = LAYOUT(
                          RGB_TOG,
        ED_ZOP,  __xxx__, VS_SB,
        ED_ZON,  ED_NTAB, VS_COM,
        __xxx__, ED_PTAB, VS_UCOM,
        VS_BCUR, __xxx__, VS_NCUR
    ),
    [VS] = LAYOUT(
                          RGB_TOG,
        VS_ZOP,  KC_F5,   __xxx__,
        VS_ZON,  __xxx__, VS_COM,
        __xxx__, KC_F11,  VS_UCOM,
        VS_BCUR, KC_F10,  VS_NCUR
    ),
    [DISCORD] = LAYOUT(
                          RGB_TOG,
          DC_AC, DC_PUCM, DC_NUCM,
        __xxx__, KC_PGUP, KC_VOLU,
        __xxx__, KC_PGDN, KC_VOLD,
        __xxx__, __xxx__, __xxx__
    ),
    [CONFS] = LAYOUT(
                          RGB_TOG,
        MC_ODEF, MC_INDI, MC_MSKI,
        MC_OBNC, RGB_HUI, MC_SHWA,
        MC_OLOG, RGB_SAI, RGB_MOD,
        KC_LSFT, RGB_VAI, RGB_SPI
    ),
    [EMPTLAYER] = LAYOUT(
                          RGB_TOG,
        __xxx__, __xxx__, __xxx__,
        __xxx__, __xxx__, __xxx__,
        __xxx__, __xxx__, __xxx__,
        __xxx__, __xxx__, __xxx__
    )
};

#ifndef OPENRGB_ENABLE
    #ifdef VIA_ENABLE
    void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    #else
    void raw_hid_receive(uint8_t *data, uint8_t length) {
    #endif
        /* Get command ID */
        uint8_t command_id = data[0];
        /* Get Layer, minus 10 to avoid overlapping with a VIA command */
        uint8_t layer = data[1] - 10;
        /* Command Id = 3 = via_keyboard_set */
        if(command_id == 3){
            /* Handle to move the layer */
            handle_layer_move(layer);
        }
    }
#endif

