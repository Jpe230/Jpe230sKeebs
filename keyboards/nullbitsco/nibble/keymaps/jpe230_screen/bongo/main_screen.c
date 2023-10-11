#include "main_screen.h"
#include "assets/assets.h"
#include "styles/styles.h"
#include "ui_conf.h"

lv_obj_t *main_screen;
lv_obj_t *obj_paw_l_down;
lv_obj_t *obj_paw_l_up;
lv_obj_t *obj_paw_r_down;
lv_obj_t *obj_paw_r_up;

static bool bongo_tap = false;

void make_bongo_dance() {
  bongo_tap = !bongo_tap;

  if (bongo_tap) {
    lv_obj_add_flag(obj_paw_l_down, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(obj_paw_r_up, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(obj_paw_l_up, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(obj_paw_r_down, LV_OBJ_FLAG_HIDDEN);
  }else{
    lv_obj_add_flag(obj_paw_l_up, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(obj_paw_r_down, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(obj_paw_l_down, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(obj_paw_r_up, LV_OBJ_FLAG_HIDDEN);
  }
}

/**
 * Init main elements
 */
void init_display(void) {
  // Load background (#dddddd)
  lv_disp_t *dispp = lv_disp_get_default();
  // lv_disp_set_rotation(dispp, LV_DISP_ROT_90);
  lv_theme_t *theme = lv_theme_default_init(
      dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
      true, LV_FONT_DEFAULT);
  lv_disp_set_theme(dispp, theme);

  main_screen = lv_obj_create(NULL);
  lv_obj_clear_flag(main_screen, LV_OBJ_FLAG_SCROLLABLE); // Disable scrolling

  lv_obj_t *background = lv_obj_create(main_screen);
  lv_obj_clear_flag(background, LV_OBJ_FLAG_SCROLLABLE); // Disable scrolling

  lv_obj_set_size(background, 320, 170);
  lv_obj_set_style_pad_all(background, 0, 0);
  lv_obj_center(background);
  lv_obj_add_style(background, &style_main_screen, 0);

  // Load table
  lv_obj_t *obj_table = lv_img_create(background);
  lv_img_set_src(obj_table, &table);
  lv_obj_align(obj_table, LV_ALIGN_TOP_LEFT, 0, 53);

  // Load bongo body
  lv_obj_t *obj_cat = lv_img_create(background);
  lv_img_set_src(obj_cat, &cat);
  lv_obj_align(obj_cat, LV_ALIGN_TOP_LEFT, 127, 32);

  // // Load left paw up
  obj_paw_l_up = lv_img_create(background);
  lv_img_set_src(obj_paw_l_up, &paw_l_up);
  lv_obj_align(obj_paw_l_up, LV_ALIGN_TOP_LEFT, 102, 46);

  // Load left paw down
  obj_paw_l_down = lv_img_create(background);
  lv_img_set_src(obj_paw_l_down, &paw_l_down);
  lv_obj_align(obj_paw_l_down, LV_ALIGN_TOP_LEFT, 92, 46);
  lv_obj_add_flag(obj_paw_l_down, LV_OBJ_FLAG_HIDDEN);

  // // Load right paw up
  obj_paw_r_up = lv_img_create(background);
  lv_img_set_src(obj_paw_r_up, &paw_r_up);
  lv_obj_align(obj_paw_r_up, LV_ALIGN_TOP_LEFT, 191, 75);

  // Load right paw down
  obj_paw_r_down = lv_img_create(background);
  lv_img_set_src(obj_paw_r_down, &paw_r_down);
  lv_obj_align(obj_paw_r_down, LV_ALIGN_TOP_LEFT, 170, 90);
  lv_obj_add_flag(obj_paw_r_down, LV_OBJ_FLAG_HIDDEN);

  lv_disp_load_scr(main_screen);
}
