#include "ui.h"
#include "actions.h"
#include "images.h"
#include "screens.h"
#include "vars.h"

#include <string.h>

static int16_t currentScreen = 0;

static lv_obj_t *getLvglObjectFromIndex(int32_t index) {
  if (index < 0 || index >= _SCREEN_ID_LAST) {
    return NULL;
  }
  return ((lv_obj_t **)&objects)[index];
}

void loadScreen(enum ScreensEnum screenId) {
  loadScreenAnim(screenId, LV_SCR_LOAD_ANIM_FADE_IN, 200);
}

void loadScreenAnim(enum ScreensEnum screenId, lv_scr_load_anim_t anim_type,
                    uint32_t time) {
  if (screenId < _SCREEN_ID_FIRST || screenId > _SCREEN_ID_LAST)
    return;
  currentScreen = screenId - 1;
  lv_obj_t *screen = getLvglObjectFromIndex(currentScreen);
  if (screen) {
    lv_scr_load_anim(screen, anim_type, time, 0, false);
  }
}

void cluster_switch_next(void) {
  int next = currentScreen + 1;
  if (next >= _SCREEN_ID_LAST) {
    next = 0; // Vòng lặp: Quay về Màn 1
  }
  loadScreenAnim((enum ScreensEnum)(next + 1), LV_SCR_LOAD_ANIM_MOVE_LEFT, 280);
}

void cluster_switch_prev(void) {
  int prev = currentScreen - 1;
  if (prev < 0) {
    prev = _SCREEN_ID_LAST - 1; // Vòng lặp: Lùi về Màn 4
  }
  loadScreenAnim((enum ScreensEnum)(prev + 1), LV_SCR_LOAD_ANIM_MOVE_RIGHT,
                 280);
}

enum ScreensEnum cluster_get_current_screen(void) {
  return (enum ScreensEnum)(currentScreen + 1);
}

void ui_init(void) {
  create_screens();
  loadScreen(SCREEN_ID_MAIN);
}

void ui_tick(void) { tick_screen(currentScreen); }
