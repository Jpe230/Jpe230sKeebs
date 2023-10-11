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

#include "screensaver.h"
#include "../../assets/assets.h"
#include "../../styles/styles.h"
#include "../../../../dumberpad.h"

lv_obj_t* img_cont = NULL;

bool use_sama = true;

void set_sama_svr() {
    use_sama = true;
}

void set_logo_svr() {
    use_sama = false;
}

void show_screensaver() {
    lv_obj_t* obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_black(), 0);
    lv_obj_set_style_border_width(obj, 0, 0);
    lv_obj_set_style_pad_all(obj, 0, 0);
    lv_obj_center(obj);

    lv_obj_t* img = lv_img_create(obj);

    if(use_sama)
        lv_img_set_src(img, &sama);
    else
        lv_img_set_src(img, &badge_dark);
    
    lv_obj_center(img);

    img_cont = obj;

    disable_lvgl();
}

void hide_screensaver() {
    if (lv_obj_is_valid(img_cont)) {
        lv_obj_del(img_cont);
    }
}
