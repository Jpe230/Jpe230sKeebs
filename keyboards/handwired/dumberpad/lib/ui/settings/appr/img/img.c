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

#include "img.h"
#include "../../../ui.h"
#include "../../../assets/assets.h"
#include "../../../styles/styles.h"

lv_obj_t* init_static_image(lv_obj_t* screen) {

    lv_obj_t* img1 = lv_img_create(screen);
    lv_img_set_src(img1, &badge_dark);
    lv_img_set_zoom(img1, 200);
    lv_obj_add_style(img1, &style_flex_layer, 0);
        
    return img1;
}
