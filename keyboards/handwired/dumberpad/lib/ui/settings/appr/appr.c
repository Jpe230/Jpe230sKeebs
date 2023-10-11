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

#include "appr.h"
#include "layer/layer.h"
#include "img/img.h"

lv_obj_t* appr_widget = NULL;

void register_widget(lv_obj_t* widget) {
    if(lv_obj_is_valid(appr_widget)) {
        lv_obj_del(appr_widget);
    }

    appr_widget = widget;
}

void init_layer_widget() {
    lv_obj_t* obj = init_layer_indicator(lv_scr_act());
    register_widget(obj);
}

void init_image_widget() {
    lv_obj_t* obj = init_static_image(lv_scr_act());
    register_widget(obj);
}

void hide_current_widget() {
    if(appr_widget != NULL) {
        lv_obj_add_flag(appr_widget, LV_OBJ_FLAG_HIDDEN);
    }
}

void show_current_widget() {
    if (appr_widget != NULL) {
        lv_obj_clear_flag(appr_widget, LV_OBJ_FLAG_HIDDEN);
    }
}
