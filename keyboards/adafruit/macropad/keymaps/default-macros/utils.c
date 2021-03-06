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

#include "keymap.h"

/* Count of Layers */
// Fix this
static uint8_t layer_count = NUMBER_OF_LAYERS;

/* Desired states */
uint8_t desired_oled_state = DEFAULT_OLED;
uint8_t desired_indicator_state = DEFAULT_INDI;

/* Timers and timer states */
bool is_showing_indicators = false;
bool rgb_matrix_idling = false;
static uint16_t indicators_timers;
static uint16_t rgb_idle_timer;

/* Show temporarly the indicators */
void temp_show_indicators(void) {
    /* If we are not showing the indicators, save the current state */
    if(!is_showing_indicators){
        desired_oled_state = oled_state;
        desired_indicator_state = indicator_state;
    }

    /* Set the states to defaults to show them temporarily */
    oled_state = DEFAULT_OLED;
    indicator_state = DEFAULT_INDI;

    /* Start Timers */
    is_showing_indicators = true;
    indicators_timers = timer_read();
}

void restore_indicators(void) {
    /* Return states to the original states */
    oled_state = desired_oled_state;
    indicator_state = desired_indicator_state;

    /* Dont show the indicators */
    is_showing_indicators = false;
}

void handle_layer_move(uint8_t layer) {
    /* Get Layer */
    int layer_idx = get_highest_layer(layer_state|default_layer_state);

    /* If we are not in the layer and the layer is valid */
    if(layer != layer_idx && layer < layer_count){
        /* Move the Layer to the desired one */
        uprintf("Moving layer to: %d number of layer: %d\n", layer, layer_count);
        layer_move(layer);

        /* Reset IDLING status and timer */
        rgb_idle_timer = timer_read();
        rgb_matrix_idling = false;

        /* Show the indicatos temporarily */
        temp_show_indicators();

        /* Turn the OLED in case it is turned off */
        oled_on();
    }
}

void cycle_layer(bool next) {
    /* Get Layer */
    int layer_idx = get_highest_layer(layer_state|default_layer_state);

    /* Add or substract the next layer */
    layer_idx = (layer_idx + (next ?  1 : -1));

    /* Check if the layer is valid */
    if(layer_idx >= layer_count)
        layer_idx = 0;
    else if(layer_idx < 0)
        layer_idx = layer_count - 1;
    
    /* Move the Layer */
    handle_layer_move(layer_idx);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    /* Cycle layers if the first encoder is turned */
    if (index == 0) {
        cycle_layer(clockwise);
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;

    /* Save the pressed/released key */
    indicator_oled_state[row][col] = record->event.pressed;

    if (record->event.pressed){
        /* Reset the IDLE timer since we pressed a key */
        rgb_idle_timer = timer_read();
        rgb_matrix_idling = false;

        /* Increment the fake wpm */
        fake_wpm_increment();
        switch (keycode) {
            TRANS_CUSTOM_KEYCODES
            case MC_INDI:
                desired_indicator_state = DEFAULT_INDI;
                restore_indicators();
                break;
            case MC_MSKI:
                desired_indicator_state = MASK_ANIM;
                restore_indicators();
                break;
            case MC_SHWA:
                desired_indicator_state = SHOW_ANIM;
                restore_indicators();
                break;
            case MC_ODEF:
                desired_oled_state = DEFAULT_OLED;
                restore_indicators();
                break;
            case MC_OBNC:
                desired_oled_state = BONGO_CAT;
                restore_indicators();
                break;
            case MC_OLOG:
                desired_oled_state = LOGO;
                restore_indicators();
                break;
        }
    }
    return true;
}

void matrix_scan_user(void) {

    /* Hide Indicators after n seconds */
    if(is_showing_indicators && timer_elapsed(indicators_timers) > SHOW_DEFAULT){
        restore_indicators();
    }

    /* Set the matrix to IDLE after n seconds without input*/
    if(!rgb_matrix_idling && timer_elapsed(rgb_idle_timer) > RGB_IDLE_TIMEOUT){
        rgb_matrix_idling = true;
    }
}