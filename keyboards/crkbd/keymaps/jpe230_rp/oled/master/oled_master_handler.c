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
#include "master_graphics.h"

extern uint8_t logged_row, logged_col;

void oled_render_layer_state(void) {
    int current_layer_idx = get_highest_layer(layer_state | default_layer_state);

    /* Sanity check */
    if(current_layer_idx >= NUMBERS_ARRAY_SIZE)
    {
        return;
    }

    /* Write the big font number */
    oled_write_raw_P(
      numbers_array[current_layer_idx],
      GRAPHIC_SIZE);
}

void render_master_oled() {
    
    /* Check if we need to turn the off the display */
	if(turn_oled_off){
        oled_off();
        return;
    }else{
        oled_on();
    }

    /* Render the layar state */
    oled_render_layer_state();

    /* Move cursor bellow the graphic */
    oled_set_cursor(0, 12);

    /* Print logged col and row
     * Format: 00x00
     */
    char logged_matrix[6] = {0};
    sprintf(logged_matrix, "%02dx%02d", logged_col, logged_row);

    /* Write a separator char: ◆, 
     * make sure to add a NULL terminator otherwise strlen will fail
     */ 
    static const char PROGMEM separator[] = {4, 4, 4, 4, 4, 0};
    oled_write(separator, false);

    /* Write logged matrix position */
    oled_write(logged_matrix, false);

    /* Write another separator */
    oled_write(separator, false);

    /* Write scanrate */
    oled_write(get_u16_str(get_matrix_scan_rate(), ' '), false);
}