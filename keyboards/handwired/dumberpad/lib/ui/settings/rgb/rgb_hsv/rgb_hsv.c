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

#include "rgb_hsv.h"
#include "../../../dial_menu/dial_menu.h"
#include "../../../styles/styles.h"
#include "../../../bindings/bindings.h"

lv_obj_t* color_wheel = NULL;
lv_obj_t* previous_focus_item;

static uint8_t selected_mode = 0;

static void close_rgb_hsv_pane(lv_event_t* event)
{
    // Return focus to previous obj
    lv_group_focus_obj(previous_focus_item);

    // Save to EEPROM after exit
    lv_color_hsv_t hsv = lv_custom_colorwheel_get_hsv(color_wheel);
    qmk_lv_rgb_matrix_sethsv(hsv.h, hsv.s, hsv.v, true);

    // Delete both objs
    if (lv_obj_is_valid(color_wheel))
        lv_obj_del(color_wheel);
}

static void change_cw_mode(lv_event_t* event)
{
    // Change mode
    selected_mode++;
    selected_mode = selected_mode % 3;
    lv_custom_colorwheel_set_mode(color_wheel, selected_mode);
}


static void cw_value_changed(lv_event_t* event)
{
    lv_color_hsv_t hsv = lv_custom_colorwheel_get_hsv(color_wheel);
   
    char str[11];
    sprintf(str, "0x%02X%02X%02X", (uint8_t)hsv.h, hsv.s, hsv.v);
    
    dial_menu_set_label_text(str);

    qmk_lv_rgb_matrix_sethsv(hsv.h, hsv.s, hsv.v, false);
}

void init_rgb_hsv_pane()
{
    previous_focus_item = *(lv_group_get_default()->obj_focus);

    color_wheel = lv_custom_colorwheel_create(lv_scr_act(), true, 10);

    lv_color_hsv_t color = qmk_lv_rgb_matrix_get_hsv();
    lv_custom_colorwheel_set_hsv(color_wheel, color);    

    lv_obj_add_style(color_wheel, &style_dial_menu_arc, 0);
    lv_obj_add_style(color_wheel, &style_cw_knob, LV_PART_KNOB);

    lv_custom_colorwheel_set_mode(color_wheel, selected_mode);
    lv_group_add_obj(lv_group_get_default(), color_wheel);

    lv_group_focus_obj(color_wheel);

    dial_menu_set_label_text("");

    lv_obj_add_event_cb(color_wheel, close_rgb_hsv_pane, LV_EVENT_LONG_PRESSED_REPEAT, NULL);
    lv_obj_add_event_cb(color_wheel, change_cw_mode, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(color_wheel, cw_value_changed, LV_EVENT_VALUE_CHANGED, NULL);
}
