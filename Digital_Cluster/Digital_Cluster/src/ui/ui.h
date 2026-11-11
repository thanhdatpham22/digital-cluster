#ifndef EEZ_LVGL_UI_GUI_H
#define EEZ_LVGL_UI_GUI_H

#include <lvgl.h>
#include "screens.h"

#ifdef __cplusplus
extern "C" {
#endif

void ui_init(void);
void ui_tick(void);

void loadScreen(enum ScreensEnum screenId);
void loadScreenAnim(enum ScreensEnum screenId, lv_scr_load_anim_t anim_type, uint32_t time);
void cluster_switch_next(void);
void cluster_switch_prev(void);
enum ScreensEnum cluster_get_current_screen(void);

#ifdef __cplusplus
}
#endif

#endif // EEZ_LVGL_UI_GUI_H
