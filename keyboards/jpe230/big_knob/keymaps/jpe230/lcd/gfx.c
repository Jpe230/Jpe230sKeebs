// Copyright 2023 jpe230 (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gfx.h"
#include "qp.h"

static lv_obj_t * layer_text;

void init_layer() {
    layer_text = lv_label_create(lv_scr_act());
    lv_label_set_text(layer_text, "");
    lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xffffff), LV_PART_MAIN);
}

lv_color_t hsv_to_color(HSV color) {
    RGB rgb_color = hsv_to_rgb_nocie(color);

    uint32_t r = rgb_color.r << 16;
    uint32_t g = rgb_color.g << 8;
    uint32_t b = rgb_color.b;
    uint32_t p_color = r | g | b;

    return lv_color_hex(p_color);
}

void set_layer(const char * text, HSV color) {
    if(layer_text == NULL)
    {
        return;
    }

    lv_obj_set_style_bg_color(lv_scr_act(), hsv_to_color(color), LV_PART_MAIN);
    lv_label_set_long_mode(layer_text, LV_LABEL_LONG_SCROLL);
    lv_obj_set_style_anim_speed(layer_text, 50, LV_PART_MAIN);
    lv_obj_set_width(layer_text, LCD_WIDTH);
    lv_label_set_text(layer_text, text);
    lv_obj_set_style_text_align(layer_text, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(layer_text, LV_ALIGN_CENTER, 0, 0);
}
