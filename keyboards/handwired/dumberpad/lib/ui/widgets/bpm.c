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

#include "bpm.h"
#include "../settings/appr/appr.h"
#include "../bindings/bindings.h"

bool active = false;

lv_obj_t* chart = NULL;
lv_timer_t* timer = NULL;

void destroy_chart(void) {
    if (timer != NULL) {
        lv_timer_del(timer);
        timer = NULL;
    }
    if (lv_obj_is_valid(chart)) {
        lv_obj_del(chart);
    }
}

static void add_data(lv_timer_t* timer) {
    LV_UNUSED(timer);
    lv_obj_t* chart = timer->user_data;
    
    lv_chart_set_next_value(chart, lv_chart_get_series_next(chart, NULL), qmk_lv_get_bpm());
}

void init_chart(void) {
    
    /*Create a chart*/
    chart = lv_chart_create(lv_scr_act());
    lv_obj_set_size(chart, 110, 60);
    lv_obj_set_y(chart, -50);
    lv_obj_set_align(chart, LV_ALIGN_CENTER);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);   /*Show lines and points too*/
    lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_SHIFT); /*Shift the data when set a new point*/
    
    lv_chart_add_series(chart, lv_color_hex(0x00dce6), LV_CHART_AXIS_PRIMARY_Y);
    
    lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_X, 2, 1, 10, 1, false, 10);
    lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_Y, 4, 1, 3, 2, true, 45);

    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_X, 0, 10);
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 100, 200);

    timer = lv_timer_create(add_data, 1000, chart);
}

void toggle_bpm(void) {
    active = !active;
    if (active) {
        hide_current_widget();
        init_chart();
    }
    else {
        destroy_chart();
        show_current_widget();
    }
}
