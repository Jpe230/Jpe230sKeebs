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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "styles.h"
#include "../fonts/fonts.h"

//////////////////////////////////////////////////////////////
// Main Screen Styles
const lv_style_const_prop_t style_main_screen_props[] = {
    LV_STYLE_CONST_BG_COLOR(LV_COLOR_MAKE16(0x23, 0x1c, 0x54)),
    LV_STYLE_CONST_BG_OPA(LV_OPA_COVER),
    LV_STYLE_CONST_BG_GRAD_COLOR(LV_COLOR_MAKE16(0x00, 0x00, 0x00)),
    LV_STYLE_CONST_BG_MAIN_STOP(0),
    LV_STYLE_CONST_BG_GRAD_STOP(255),
    LV_STYLE_CONST_BG_GRAD_DIR(LV_GRAD_DIR_VER),
    C_LV_STYLE_PROP_INV,
};
LV_STYLE_INIT(style_main_screen, style_main_screen_props);

//////////////////////////////////////////////////////////////
// Dial Menu Styles
const lv_style_const_prop_t style_dial_menu_arc_props[] = {
    LV_STYLE_CONST_ARC_COLOR(LV_COLOR_MAKE16(0xff, 0xff, 0xff)),
    LV_STYLE_CONST_ARC_WIDTH(ARC_WIDTH),
    LV_STYLE_CONST_ARC_ROUNDED(false),
    LV_STYLE_CONST_X(ARC_POS_X),
    LV_STYLE_CONST_Y(ARC_POS_Y),
    LV_STYLE_CONST_WIDTH(ARC_SIZE),
    LV_STYLE_CONST_HEIGHT(ARC_SIZE),
    LV_STYLE_CONST_ALIGN(LV_ALIGN_CENTER),
    C_LV_STYLE_PROP_INV,

};
LV_STYLE_INIT(style_dial_menu_arc, style_dial_menu_arc_props);

const lv_style_const_prop_t style_dial_menu_arc_indicator_props[] = {
    LV_STYLE_CONST_ARC_COLOR(LV_COLOR_MAKE16(0x09, 0x2a, 0x43)),
    LV_STYLE_CONST_ARC_WIDTH(ARC_WIDTH),
    LV_STYLE_CONST_ARC_ROUNDED(false),
    C_LV_STYLE_PROP_INV,

};
LV_STYLE_INIT(style_dial_menu_arc_indicator, style_dial_menu_arc_indicator_props);

const lv_style_const_prop_t sstyle_dial_menu_knob_props[] = {
    LV_STYLE_CONST_BG_COLOR(LV_COLOR_MAKE16(0xb5, 0x00, 0x75)),
    LV_STYLE_CONST_BG_OPA(LV_OPA_COVER),
    LV_STYLE_CONST_BG_GRAD_COLOR(LV_COLOR_MAKE16(0xfe, 0x47, 0x3c)),
    LV_STYLE_CONST_BG_MAIN_STOP(0),
    LV_STYLE_CONST_BG_GRAD_STOP(255),
    LV_STYLE_CONST_BG_GRAD_DIR(LV_GRAD_DIR_VER),
    LV_STYLE_CONST_BORDER_WIDTH(0),
    LV_STYLE_CONST_RADIUS(LV_RADIUS_CIRCLE),
    LV_STYLE_CONST_X(ARC_POS_X),
    LV_STYLE_CONST_Y(ARC_POS_Y),
    LV_STYLE_CONST_WIDTH(MENU_KNOB_SIZE),
    LV_STYLE_CONST_HEIGHT(MENU_KNOB_SIZE),
    LV_STYLE_CONST_ALIGN(LV_ALIGN_CENTER),
    C_LV_STYLE_PROP_INV,

};
LV_STYLE_INIT(style_dial_menu_knob, sstyle_dial_menu_knob_props);

//////////////////////////////////////////////////////////////
// Button Icon Styles
const lv_style_const_prop_t default_btn_style_props[] = {
    LV_STYLE_CONST_TEXT_COLOR(LV_COLOR_MAKE16(0x00, 0x00, 0x00)),
    LV_STYLE_CONST_TEXT_FONT(&extra_icons),
    LV_STYLE_CONST_WIDTH(LV_SIZE_CONTENT),
    LV_STYLE_CONST_HEIGHT(LV_SIZE_CONTENT),
    LV_STYLE_CONST_ALIGN(LV_ALIGN_CENTER),
    C_LV_STYLE_PROP_INV,

};
LV_STYLE_INIT(default_btn_style, default_btn_style_props);

const lv_style_const_prop_t focused_btn_style_props[] = {
    LV_STYLE_CONST_TEXT_COLOR(LV_COLOR_MAKE16(0xff, 0xff, 0xff)),
    C_LV_STYLE_PROP_INV,

};
LV_STYLE_INIT(focused_btn_style, focused_btn_style_props);

//////////////////////////////////////////////////////////////
// Flex (Layer) Styles
const lv_style_const_prop_t style_flex_layer_props[] = {
    //LV_STYLE_CONST_FLEX_FLOW(LV_FLEX_FLOW_ROW),
    //LV_STYLE_CONST_FLEX_MAIN_PLACE(LV_FLEX_FLOW_ROW),
    //LV_STYLE_CONST_LAYOUT(LV_LAYOUT_FLEX),
    LV_STYLE_CONST_WIDTH(LV_SIZE_CONTENT),
    LV_STYLE_CONST_HEIGHT(LV_SIZE_CONTENT),
    LV_STYLE_CONST_Y(LAYER_POS_Y),
    LV_STYLE_CONST_X(LAYER_POS_X),
    LV_STYLE_CONST_ALIGN(LV_ALIGN_CENTER),
    C_LV_STYLE_PROP_INV,

};
LV_STYLE_INIT(style_flex_layer, style_flex_layer_props);

//////////////////////////////////////////////////////////////
// Label Styles
lv_style_t style_label_mons_22;

const lv_style_const_prop_t style_label_imp_22_props[] = {
    LV_STYLE_CONST_TEXT_COLOR(LV_COLOR_MAKE16(0xff, 0xff, 0xff)),
    LV_STYLE_CONST_TEXT_FONT(&impact_22),
    LV_STYLE_CONST_WIDTH(LV_SIZE_CONTENT),
    LV_STYLE_CONST_HEIGHT(LV_SIZE_CONTENT),
    LV_STYLE_CONST_ALIGN(LV_ALIGN_CENTER),
    C_LV_STYLE_PROP_INV,

};
LV_STYLE_INIT(style_label_imp_22, style_label_imp_22_props);

const lv_style_const_prop_t style_label_imp_45_props[] = {
    LV_STYLE_CONST_TEXT_COLOR(LV_COLOR_MAKE16(0xff, 0xff, 0xff)),
    LV_STYLE_CONST_TEXT_FONT(&impact_45),
    LV_STYLE_CONST_WIDTH(LV_SIZE_CONTENT),
    LV_STYLE_CONST_HEIGHT(LV_SIZE_CONTENT),
    LV_STYLE_CONST_ALIGN(LV_ALIGN_CENTER),
    C_LV_STYLE_PROP_INV,

};
LV_STYLE_INIT(style_label_imp_45, style_label_imp_45_props);

//////////////////////////////////////////////////////////////
// Panel Styles
lv_style_t style_panel_bg;

//////////////////////////////////////////////////////////////
// Panel Styles
const lv_style_const_prop_t style_cw_knob_props[] = {
    LV_STYLE_CONST_TEXT_COLOR(LV_COLOR_MAKE16(0xff, 0xff, 0xff)),
    LV_STYLE_CONST_BG_COLOR(LV_COLOR_MAKE16(0xff, 0xff, 0xff)),
    LV_STYLE_CONST_BG_OPA(LV_OPA_COVER),
    LV_STYLE_CONST_PAD_TOP(0),
    LV_STYLE_CONST_PAD_BOTTOM(0),
    LV_STYLE_CONST_PAD_LEFT(0),
    LV_STYLE_CONST_PAD_RIGHT(0),
    LV_STYLE_CONST_PAD_ROW(0),
    LV_STYLE_CONST_PAD_COLUMN(0),
    C_LV_STYLE_PROP_INV,

};
LV_STYLE_INIT(style_cw_knob, style_cw_knob_props);
