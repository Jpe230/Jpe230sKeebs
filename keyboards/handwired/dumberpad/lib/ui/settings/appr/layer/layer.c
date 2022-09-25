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

#include "layer.h"
#include "../../../ui.h"
#include "../../../styles/styles.h"
#include "../../../bindings/bindings.h"

lv_timer_t* timer;

void set_layer_text_value(uint8_t i, lv_obj_t* lbl) {
    if (lv_obj_is_valid(lbl)) {
        char buf[5];
        snprintf(buf, sizeof(buf), "%02d", i+1);
        lv_label_set_text(lbl, buf);
    }
}

static void poll_layer(lv_timer_t* timer) {
    LV_UNUSED(timer);
    lv_obj_t* lbl = timer->user_data;

    set_layer_text_value(qmk_lv_geT_layer(), lbl);
}

lv_obj_t* init_layer_indicator(lv_obj_t* screen) {

    if (timer != NULL) {
        lv_timer_del(timer);
        timer = NULL;
    }

    lv_obj_t* cont = lv_obj_create(screen);
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE); // Disable scrolling
    lv_obj_remove_style_all(cont); // Remove default style
    lv_obj_set_style_flex_flow(cont, LV_FLEX_FLOW_COLUMN_WRAP, 0);
    lv_obj_set_style_flex_main_place(cont, LV_FLEX_ALIGN_SPACE_EVENLY, 0);
    lv_obj_set_style_layout(cont, LV_LAYOUT_FLEX, 0);
    lv_obj_add_style(cont, &style_flex_layer, 0);

    lv_obj_t* layer_desc_lbl = lv_label_create(cont);
    lv_obj_remove_style_all(layer_desc_lbl);
    lv_obj_add_style(layer_desc_lbl, &style_label_imp_22, 0);

    lv_obj_set_style_text_color(layer_desc_lbl, lv_color_hex(0x635EC1), 0);
    lv_label_set_text(layer_desc_lbl, "Layer");

    lv_obj_t* layer_value_lbl = lv_label_create(cont);
    lv_obj_remove_style_all(layer_value_lbl);
    lv_obj_add_style(layer_value_lbl, &style_label_imp_45, 0);

    lv_obj_set_style_text_color(layer_value_lbl, lv_color_hex(0x00dce6), 0);
    lv_label_set_text(layer_value_lbl, "01");

    timer = lv_timer_create(poll_layer, 100, layer_value_lbl);

    return cont;
}
