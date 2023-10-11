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

//////////////////////////////////////////////////////////////
// Main Screen Styles
const lv_style_const_prop_t style_main_screen_props[] = {
    LV_STYLE_CONST_BG_COLOR(LV_COLOR_MAKE16(0xee, 0xef, 0xee)),
    LV_STYLE_CONST_BG_OPA(LV_OPA_COVER),
    LV_STYLE_CONST_BORDER_WIDTH(0),
    LV_STYLE_CONST_RADIUS(0),
    C_LV_STYLE_PROP_INV
};
LV_STYLE_INIT(style_main_screen, style_main_screen_props);
