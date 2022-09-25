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

#include "ui.h"
#include "menu.h"
#include "dial_menu/dial_menu.h"
#include "settings/appr/appr.h"
#include "styles/styles.h"
#include "widgets/bpm.h"
#include "settings/screensaver/screensaver.h"

lv_obj_t* main_screen;

void main_ui_unit(void) {
    // Init the main screen
    main_screen = lv_obj_create(NULL);
    lv_obj_clear_flag(main_screen, LV_OBJ_FLAG_SCROLLABLE); // Disable scrolling

    lv_obj_t* background = lv_obj_create(main_screen);

    lv_obj_set_size(background, 240, 240);
    lv_obj_set_style_border_width(background, 0, 0);
    lv_obj_set_style_pad_all(background, 0, 0);
    lv_obj_center(background);

    lv_obj_add_style(background, &style_main_screen, 0);
}

void main_screen_init(void){
    lv_disp_t* dispp = lv_disp_get_default();
    lv_theme_t* theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    init_menu();
    main_ui_unit();
    
    lv_disp_load_scr(main_screen);
    
    init_dial_menu(main_screen);
    create_dial_menu(main_screen, &root);

    init_layer_widget();

 #ifdef SHOW_TEST_CIRCLE
     lv_obj_t* limit_circle = lv_obj_create(main_screen);
     lv_obj_set_size(limit_circle, 250, 250);
     lv_obj_set_style_radius(limit_circle, LV_RADIUS_CIRCLE, 0);
     lv_obj_set_style_border_width(limit_circle, 10, 0);
     lv_obj_set_style_bg_opa(limit_circle, 0, 0);
     lv_obj_center(limit_circle);
 #endif
}
