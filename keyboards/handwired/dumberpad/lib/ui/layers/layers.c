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

#include "layers.h"
#include "../bindings/bindings.h"

void set_layer(uint8_t i) {
    qmk_lv_set_layer(i);
}

void set_layer_1() {
    set_layer(0);
}
void set_layer_2() {
    set_layer(1);
}
void set_layer_3() {
    set_layer(2);
}
void set_layer_4() {
    set_layer(3);
}
