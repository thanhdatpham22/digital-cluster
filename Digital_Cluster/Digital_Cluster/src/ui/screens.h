#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Screen Identifiers */
enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MAIN = 1,          /* Màn 1: Taplo chính (Speed, RPM, Fuel, Trip) */
    SCREEN_ID_VEHICLE_DTC = 2,   /* Màn 2: Thông tin xe & Mã lỗi UDS DTC */
    SCREEN_ID_MAP = 3,           /* Màn 3: Mini Navigation & Bản đồ chỉ đường */
    SCREEN_ID_CONTROL = 4,       /* Màn 4: Bảng điều khiển cảm ứng (A/C, Đèn, Khóa) */
    _SCREEN_ID_LAST = 4
};

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *vehicle_dtc;
    lv_obj_t *map;
    lv_obj_t *control;
} objects_t;

extern objects_t objects;

typedef struct {
    lv_meter_scale_t *scale;
    lv_meter_indicator_t *indicator;
} screen_main_state_t;

extern screen_main_state_t screen_main_state;

/* Theme status */
extern bool g_is_dark_theme;
void cluster_toggle_theme(void);
void cluster_apply_theme(bool is_dark);

/* Display fields reserved for the vehicle data/CAN update layer (Screen 1) */
extern lv_obj_t *cluster_speed_label;
extern lv_obj_t *cluster_rpm_label;
extern lv_obj_t *cluster_gear_label;
extern lv_obj_t *cluster_fuel_label;
extern lv_obj_t *cluster_temp_label;
extern lv_obj_t *cluster_time_label;
extern lv_obj_t *cluster_rpm_arc;
extern lv_obj_t *cluster_fuel_bar;
extern lv_obj_t *cluster_btn_theme;

/* Public widgets for Screen 2 (Vehicle & DTCs) */
extern lv_obj_t *cluster_batt_label;
extern lv_obj_t *cluster_coolant_label;
extern lv_obj_t *cluster_dtc_badge_label;
extern lv_obj_t *cluster_dtc_item1_label;
extern lv_obj_t *cluster_dtc_item2_label;

/* Public widgets for Screen 3 (Navigation / Mini-Map) */
extern lv_obj_t *cluster_nav_dist_label;
extern lv_obj_t *cluster_nav_street_label;
extern lv_obj_t *cluster_nav_action_label;
extern lv_obj_t *cluster_nav_eta_label;

/* Public widgets for Screen 4 (Control Panel) */
extern lv_obj_t *cluster_btn_ac;
extern lv_obj_t *cluster_btn_fan;
extern lv_obj_t *cluster_btn_light;
extern lv_obj_t *cluster_btn_hazard;
extern lv_obj_t *cluster_btn_lock;

/* Screen creation functions */
void create_screen_main(void);
void create_screen_vehicle_dtc(void);
void create_screen_map(void);
void create_screen_control(void);
void create_screens(void);

/* Screen tick functions */
void tick_screen_main(void);
void tick_screen_vehicle_dtc(void);
void tick_screen_map(void);
void tick_screen_control(void);

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

/* Navigation / Gesture callback */
void cluster_screen_gesture_cb(lv_event_t * e);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/
