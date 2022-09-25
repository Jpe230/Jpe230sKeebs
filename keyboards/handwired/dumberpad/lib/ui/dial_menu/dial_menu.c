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

#include "dial_menu.h"
#include "../ui.h"
#include "../styles/styles.h"

static lv_obj_t* arc;
static lv_obj_t* menu_lbl;

static int16_t dial_angle = 190;
static lv_point_t positions[] = { {-69, 12}, {-45,54}, {0, 70}, {45,54}, {69, 12} };

static lv_obj_t* buttons[5];
static lv_obj_t* labels[5];


static void anim_angle_cb(void* var, int32_t v) {
    dial_angle = v;
    lv_arc_set_angles(var, dial_angle - 20, dial_angle + 20);
}

void update_menu_state(void* user_data) {
    menu_obj_t* focused_menu_obj = (menu_obj_t*)user_data;

    static lv_anim_t dial_animation;

    lv_anim_init(&dial_animation);

    lv_anim_set_var(&dial_animation, arc);

    uint16_t angle = dial_angle;

    if (angle > 360)
    {
        angle = angle % 360;
    }

    lv_anim_set_values(&dial_animation, angle, (focused_menu_obj->position * 40) + 190);

    lv_anim_set_time(&dial_animation, 100);

    lv_anim_set_exec_cb(&dial_animation, anim_angle_cb);

    lv_anim_set_path_cb(&dial_animation, lv_anim_path_overshoot);
    lv_anim_start(&dial_animation);

    dial_menu_set_label_text(focused_menu_obj->value);
}

void btn_focus_event(lv_event_t* e) {
    update_menu_state(e->user_data);
}

extern lv_obj_t* main_screen;

void destroy_objs(void) {
    for (int i = 0; i < 5; i++)
    {
        if (lv_obj_is_valid(labels[i]))
            lv_obj_del(labels[i]);
        
        if (lv_obj_is_valid(buttons[i]))
            lv_obj_del(buttons[i]);

        labels[i] = NULL;
        buttons[i] = NULL;
    }
}

void handle_widget_action(menu_obj_t* menu_obj) {
    menu_obj->do_action();
}

void handle_prev_action(menu_obj_t* menu_obj) {
    if(menu_obj->parent != NULL) {
        destroy_objs();
        create_dial_menu(main_screen, menu_obj->parent->parent);
    }
}

void handle_next_action(menu_obj_t* menu_obj) {
    if (menu_obj->first_child != NULL) {
        destroy_objs();
        create_dial_menu(main_screen, menu_obj);
    }
}

void btn_clicked_event(lv_event_t* e) {
    menu_obj_t* clicked_menu_obj = (menu_obj_t*)e->user_data;

    switch(clicked_menu_obj->action) {
        case JP_WIDGET:
            handle_widget_action(clicked_menu_obj);
            break;
        case JP_PREV_ITEM:
            handle_prev_action(clicked_menu_obj);
            break;
        case JP_NEXT_ITEM:
            handle_next_action(clicked_menu_obj);
            break;
    }
}

void init_dial_menu(lv_obj_t* screen) {

    arc = lv_arc_create(screen);

    lv_arc_set_bg_angles(arc, 0, 360);
    lv_arc_set_value(arc, 0);
    lv_arc_set_angles(arc, dial_angle - 20, dial_angle + 20);

    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/

    lv_obj_add_style(arc, &style_dial_menu_arc, LV_STATE_DEFAULT);
    lv_obj_add_style(arc, &style_dial_menu_arc_indicator, LV_PART_INDICATOR);

    lv_obj_t* ui_Knob = lv_obj_create(screen);

    lv_obj_add_style(ui_Knob, &style_dial_menu_knob, LV_STATE_DEFAULT);

    menu_lbl = lv_label_create(screen);
    lv_obj_remove_style_all(menu_lbl); // Remove default style

    lv_obj_add_style(menu_lbl, &style_label_imp_22, 0);
    lv_obj_set_pos(menu_lbl, 0, ARC_POS_Y);
}

void create_dial_menu(lv_obj_t* screen, menu_obj_t* menu_root) {
    if (menu_root->first_child == NULL) return;

    // Reset Position of dial to the first_child
    update_menu_state(menu_root->first_child);

    menu_obj_t* current_child = menu_root->first_child;

    uint8_t i = 0;

    while (current_child != NULL)
    {
        lv_obj_t* btn = lv_btn_create(screen);

        lv_obj_remove_style_all(btn); // Remove default style

        lv_obj_set_pos(btn, positions[current_child->position].x, ARC_Y - positions[current_child->position].y);
        lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE);

        lv_obj_add_style(btn, &default_btn_style, LV_STATE_DEFAULT);
        lv_obj_add_style(btn, &focused_btn_style, LV_STATE_FOCUSED);
        lv_obj_add_style(btn, &default_btn_style, LV_STATE_PRESSED);

        lv_obj_t* label = lv_label_create(btn);
        lv_label_set_text(label, current_child->symbol);
        lv_obj_center(label);

        lv_obj_add_event_cb(btn, btn_focus_event, LV_EVENT_FOCUSED, current_child);
        lv_obj_add_event_cb(btn, btn_clicked_event, LV_EVENT_PRESSED, current_child);

        if (i == 0) lv_obj_add_state(btn, LV_STATE_FOCUSED);

        buttons[i] = btn;
        labels[i] = label;

        i++;

        current_child = current_child->next_sibling;

    }

    return;
}

void dial_menu_set_label_text(const char* value) {
    lv_label_set_text(menu_lbl, value);
}

void dial_menu_set_label_text_fml(const char* format, uint16_t value) {
    lv_label_set_text_fmt(menu_lbl, format, value);
}

