// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "logic/jpe230.h"
#include "bongo/main_screen.h"

static painter_device_t display;

void print_screen(void)
{
  uint16_t panel_width, panel_height, offset_x, offset_y;
  painter_rotation_t rotation;

  qp_get_geometry(display, &panel_width, &panel_height, &rotation, &offset_x, &offset_y);

  dprintf("Width: %d, Height: %d, Rotation: %d, offset_x: %d, offset_y: %d\n", panel_width, panel_height, rotation, offset_x, offset_y);
}

void keyboard_post_init_user(void) {

  setPinOutput(LCD_BLK_PIN);

  display = qp_st7789_make_spi_device(205, 320, LCD_CS_PIN, LCD_DC_PIN,
                                      LCD_RST_PIN, 8, 2);
  qp_init(display, QP_ROTATION_90);
  qp_set_viewport_offsets(display, 0, 35);

  qp_power(display, true);

  qp_rect(display, 0, 0, 319, 204, 100, 100, 100, true); // Clear display Just in case

  if (qp_lvgl_attach(display)) { // Attach LVGL to the display
    init_display();
  }

  qp_flush(display);
}