// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "jpe230.h"

__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_timer_reset();
        set_keylog(keycode, record);

        switch (keycode) {
            case QK_BOOT:
                rgb_matrix_set_color_all(30, 0, 0);
                rgb_matrix_driver.flush();
                oled_off();
                return true;
        }
    }
    return process_record_secrets(keycode, record);;
}
