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
#include "settings/rgb/rgb_hsv/rgb_hsv.h"
#include "settings/rgb/rgb_speed/rgb_speed.h"
#include "settings/rgb/rgb_mode/rgb_mode.h"
#include "settings/dev/dev.h"
#include "settings/appr/appr.h"
#include "settings/screensaver/screensaver.h"
#include "layers/layers.h"
#include "widgets/bpm.h"

menu_obj_t root = { "", "", JP_NEXT_ITEM, NULL, 0, NULL, NULL };

void init_menu(void) {

    // Max 5 position per dial
    static menu_obj_t exit = { "Home", JP_ICON_KEYBOARD, JP_WIDGET, &show_screensaver, 4, &root, NULL, NULL };
    static menu_obj_t github = { "Github", JP_ICON_GITHUB, JP_NEXT_ITEM, 0, 3, &root, &exit, NULL };
    static menu_obj_t wpm = { "WPM", JP_ICON_CHART, JP_WIDGET, &toggle_bpm, 2, &root, &github, NULL };
    static menu_obj_t layers = { "Layers", JP_ICON_LAYER, JP_NEXT_ITEM, 0, 1,&root, &wpm, NULL };
    static menu_obj_t settings = { "Settings", JP_ICON_COG, JP_NEXT_ITEM, 0, 0, &root, &layers, NULL };

    root.first_child = &settings;

    static menu_obj_t settings_back = { "Back",  JP_ICON_ARROW_LEFT, JP_PREV_ITEM, 0, 4, &settings, NULL, NULL };
    static menu_obj_t settings_appr = { "Appearance", JP_ICON_IMAGES, JP_NEXT_ITEM, 0, 2, &settings, &settings_back, NULL };
    static menu_obj_t settings_dev = { "Developer", JP_ICON_CODE, JP_NEXT_ITEM, 0, 1, &settings, &settings_appr, NULL };
    static menu_obj_t settings_rgb = { "RGB", JP_ICON_PALETTE, JP_NEXT_ITEM, 0, 0, &settings, &settings_dev, NULL };

    settings.first_child = &settings_rgb;

    static menu_obj_t rgb_back = { "Back",  JP_ICON_ARROW_LEFT, JP_PREV_ITEM, 0, 4, &settings_rgb, NULL, NULL };
    static menu_obj_t rgb_mode = { "Mode", JP_ICON_SWATCH, JP_WIDGET, &init_rgb_mode_pane, 2, &settings_rgb, &rgb_back, NULL };
    static menu_obj_t rgb_speed = { "Speed", JP_ICON_TACHOMETER, JP_WIDGET, &init_rgb_speed_pane, 1, &settings_rgb, &rgb_mode, NULL };
    static menu_obj_t rgb_hsv = { "HSV", JP_ICON_BRUSH, JP_WIDGET, &init_rgb_hsv_pane, 0, &settings_rgb, &rgb_speed, NULL };

    settings_rgb.first_child = &rgb_hsv;

    static menu_obj_t dev_back = { "Back",  JP_ICON_ARROW_LEFT, JP_PREV_ITEM, NULL, 4, &settings_dev, NULL, NULL };
    static menu_obj_t dev_enable = { "QK_BOOT", JP_ICON_SYNC, JP_WIDGET, &dev_qk_boot, 2, &settings_dev, &dev_back, NULL };
    static menu_obj_t dev_boot = { "DB_TOGG", JP_ICON_TERMINAL, JP_WIDGET, &dev_dbg_toggle, 1, &settings_dev, &dev_enable, NULL };
    static menu_obj_t dev_clreeprom = { "EE_CLR", JP_ICON_ERASER, JP_WIDGET, &dev_clr_eeprom, 0, &settings_dev, &dev_boot, NULL };

    settings_dev.first_child = &dev_clreeprom;

    static menu_obj_t appr_back = { "Back",  JP_ICON_ARROW_LEFT, JP_PREV_ITEM, NULL, 4, &settings_appr, NULL, NULL };
    static menu_obj_t appr_img = { "Screensvr",  JP_ICON_DESKTOP, JP_NEXT_ITEM, NULL, 2, &settings_appr, &appr_back, NULL };
    static menu_obj_t appr_widget = { "Widget",  JP_ICON_COGS, JP_NEXT_ITEM, NULL, 1, &settings_appr, &appr_img, NULL };

    settings_appr.first_child = &appr_widget;

    static menu_obj_t widget_back = { "Back",  JP_ICON_ARROW_LEFT, JP_PREV_ITEM, NULL, 4, &appr_widget, NULL, NULL };
    static menu_obj_t widget_img = { "Image",  JP_ICON_IMAGE, JP_WIDGET, &init_image_widget, 2, &appr_widget, &widget_back, NULL };
    static menu_obj_t widget_layer = { "Layer",  JP_ICON_LAYER, JP_WIDGET, &init_layer_widget, 1, &appr_widget, &widget_img, NULL };

    appr_widget.first_child = &widget_layer;

    static menu_obj_t layer_back = { "Back",  JP_ICON_ARROW_LEFT, JP_PREV_ITEM, NULL, 4, &layers, NULL, NULL };
    static menu_obj_t layer_4 = { "Layer 4",  "4", JP_WIDGET, &set_layer_4, 3, &layers, &layer_back, NULL};
    static menu_obj_t layer_3 = { "Layer 3",  "3", JP_WIDGET, &set_layer_3, 2, &layers, &layer_4, NULL };
    static menu_obj_t layer_2 = { "Layer 2",  "2", JP_WIDGET, &set_layer_2, 1, &layers, &layer_3, NULL };
    static menu_obj_t layer_1 = { "Layer 1",  "1", JP_WIDGET, &set_layer_1, 0, &layers, &layer_2, NULL};

    layers.first_child = &layer_1;

    static menu_obj_t screensvr_back  = { "Back",  JP_ICON_ARROW_LEFT, JP_PREV_ITEM, NULL, 4, &appr_img, NULL, NULL };
    static menu_obj_t screensvr_logo   = { "Logo",  JP_ICON_CODE, JP_WIDGET, &set_logo_svr, 2, &appr_img, &screensvr_back, NULL};
    static menu_obj_t screensvr_sama = { "Sama",  JP_ICON_FEMALE, JP_WIDGET, &set_sama_svr, 1, &appr_img, &screensvr_logo, NULL };

    appr_img.first_child = &screensvr_sama;
}
