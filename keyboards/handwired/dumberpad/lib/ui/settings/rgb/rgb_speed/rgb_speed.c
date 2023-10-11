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

#include "rgb_speed.h"

#include "../../../dial_menu/dial_menu.h"
#include "../../../styles/styles.h"
#include "../../../bindings/bindings.h"

lv_obj_t* arc = NULL;
lv_obj_t* previous_focus_item = NULL;

static void close_rgb_speed_pane(lv_event_t* event) {
    // Return focus to previous obj
    lv_group_focus_obj(previous_focus_item);

    uint16_t speed = lv_arc_get_value(arc) << 2;

    if (speed > 255) {
        speed = 255;
    }
    qmk_lv_rgb_matrix_set_speed(speed, true);

    if (lv_obj_is_valid(arc)) {
        lv_obj_del(arc);
    }
}

static void arc_value_changed(lv_event_t* event)
{
    uint16_t speed = lv_arc_get_value(arc) << 2;

    if(speed > 255) {
        speed = 255;
    }

    dial_menu_set_label_text_fml("%03d", speed);

    qmk_lv_rgb_matrix_set_speed(speed, false);
    
}

void init_rgb_speed_pane() {
    previous_focus_item = *(lv_group_get_default()->obj_focus);

    arc = lv_arc_create(lv_scr_act());

    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/

    lv_obj_add_style(arc, &style_dial_menu_arc, LV_STATE_DEFAULT);
    lv_obj_add_style(arc, &style_dial_menu_arc_indicator, LV_PART_INDICATOR);

    lv_arc_set_rotation(arc, 135);
    lv_arc_set_bg_angles(arc, 30, 240);
    lv_arc_set_value(arc, qmk_lv_rgb_matrix_get_speed() >> 2);
    lv_arc_set_range(arc, 0, 63);

    lv_group_add_obj(lv_group_get_default(), arc);
    lv_group_focus_obj(arc);

    lv_obj_add_event_cb(arc, close_rgb_speed_pane, LV_EVENT_LONG_PRESSED_REPEAT, NULL);
    lv_obj_add_event_cb(arc, close_rgb_speed_pane, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(arc, arc_value_changed, LV_EVENT_VALUE_CHANGED, NULL);
}
