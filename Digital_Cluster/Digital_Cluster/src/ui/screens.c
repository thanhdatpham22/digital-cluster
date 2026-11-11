#include "screens.h"
#include "fonts.h"
#include "ui.h"
#include <stdio.h>

objects_t objects;
screen_main_state_t screen_main_state;

/* Theme state: true = Dark Theme, false = Light Theme */
bool g_is_dark_theme = true;

/* Screen 1: Dashboard Handles */
lv_obj_t *cluster_speed_label = NULL;
lv_obj_t *cluster_rpm_label   = NULL;
lv_obj_t *cluster_gear_label  = NULL;
lv_obj_t *cluster_fuel_label  = NULL;
lv_obj_t *cluster_temp_label  = NULL;
lv_obj_t *cluster_time_label  = NULL;
lv_obj_t *cluster_rpm_arc     = NULL;
lv_obj_t *cluster_fuel_bar    = NULL;
lv_obj_t *cluster_btn_theme   = NULL;
static lv_obj_t *cluster_theme_lbl = NULL;

/* Screen 2: Vehicle & DTC Handles */
lv_obj_t *cluster_batt_label       = NULL;
lv_obj_t *cluster_coolant_label    = NULL;
lv_obj_t *cluster_dtc_badge_label  = NULL;
lv_obj_t *cluster_dtc_item1_label  = NULL;
lv_obj_t *cluster_dtc_item2_label  = NULL;

/* Screen 3: Navigation Handles */
lv_obj_t *cluster_nav_dist_label    = NULL;
lv_obj_t *cluster_nav_street_label  = NULL;
lv_obj_t *cluster_nav_action_label  = NULL;
lv_obj_t *cluster_nav_eta_label     = NULL;

/* Screen 4: Controls Handles */
lv_obj_t *cluster_btn_ac     = NULL;
lv_obj_t *cluster_btn_fan    = NULL;
lv_obj_t *cluster_btn_light  = NULL;
lv_obj_t *cluster_btn_hazard = NULL;
lv_obj_t *cluster_btn_lock   = NULL;

/* =========================================================================
 * COMMON HELPERS
 * ========================================================================= */
static lv_obj_t *make_label(lv_obj_t *parent, const char *text, lv_coord_t x,
                            lv_coord_t y, lv_coord_t w, lv_coord_t h,
                            const lv_font_t *font, uint32_t color,
                            lv_text_align_t align)
{
    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, text);
    lv_obj_set_pos(label, x, y);
    lv_obj_set_size(label, w, h);
    lv_obj_set_style_text_font(label, font, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(color), LV_PART_MAIN);
    lv_obj_set_style_text_align(label, align, LV_PART_MAIN);
    lv_label_set_long_mode(label, LV_LABEL_LONG_CLIP);
    return label;
}

static lv_obj_t *make_panel(lv_obj_t *parent, lv_coord_t x, lv_coord_t y,
                            lv_coord_t w, lv_coord_t h)
{
    lv_obj_t *panel = lv_obj_create(parent);
    lv_obj_set_pos(panel, x, y);
    lv_obj_set_size(panel, w, h);
    lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);

    if (g_is_dark_theme) {
        lv_obj_set_style_bg_color(panel, lv_color_hex(0x101B29), LV_PART_MAIN);
        lv_obj_set_style_border_color(panel, lv_color_hex(0x24364A), LV_PART_MAIN);
    } else {
        lv_obj_set_style_bg_color(panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
        lv_obj_set_style_border_color(panel, lv_color_hex(0xCBD5E1), LV_PART_MAIN);
    }

    lv_obj_set_style_bg_opa(panel, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(panel, 1, LV_PART_MAIN);
    lv_obj_set_style_radius(panel, 8, LV_PART_MAIN);
    lv_obj_set_style_pad_all(panel, 0, LV_PART_MAIN);
    return panel;
}

static void make_page_indicator(lv_obj_t *parent, uint8_t active_page)
{
    lv_coord_t start_x = 92;
    lv_coord_t y = 308;

    for (uint8_t i = 0; i < 4; i++) {
        lv_obj_t *dot = lv_obj_create(parent);
        lv_obj_set_style_radius(dot, 2, LV_PART_MAIN);
        lv_obj_set_style_border_width(dot, 0, LV_PART_MAIN);
        lv_obj_set_style_pad_all(dot, 0, LV_PART_MAIN);
        lv_obj_clear_flag(dot, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);

        if (i == active_page) {
            lv_obj_set_pos(dot, start_x, y);
            lv_obj_set_size(dot, 16, 4);
            lv_obj_set_style_bg_color(dot, lv_color_hex(0x43D9C5), LV_PART_MAIN);
            start_x += 20;
        } else {
            lv_obj_set_pos(dot, start_x, y);
            lv_obj_set_size(dot, 6, 4);
            lv_obj_set_style_bg_color(dot, lv_color_hex(g_is_dark_theme ? 0x24364A : 0xCBD5E1), LV_PART_MAIN);
            start_x += 10;
        }
    }
}

/* Thêm hiệu ứng co lõm (Press Tactile Animation) cho nút bấm */
static void add_button_press_animation(lv_obj_t * btn)
{
    lv_obj_set_style_transform_width(btn, -4, LV_STATE_PRESSED);
    lv_obj_set_style_transform_height(btn, -4, LV_STATE_PRESSED);

    static const lv_style_prop_t trans_props[] = {
        LV_STYLE_TRANSFORM_WIDTH,
        LV_STYLE_TRANSFORM_HEIGHT,
        LV_STYLE_BG_COLOR,
        LV_STYLE_BORDER_COLOR,
        0
    };
    static lv_style_transition_dsc_t trans_dsc;
    lv_style_transition_dsc_init(&trans_dsc, trans_props, lv_anim_path_ease_out, 150, 0, NULL);
    lv_obj_set_style_transition(btn, &trans_dsc, LV_PART_MAIN);
}

/* Global Gesture Handler for Swipe Left / Right */
void cluster_screen_gesture_cb(lv_event_t * e)
{
    if (lv_event_get_code(e) == LV_EVENT_GESTURE) {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        if (dir == LV_DIR_LEFT) {
            cluster_switch_next();
        } else if (dir == LV_DIR_RIGHT) {
            cluster_switch_prev();
        }
    }
}

/* =========================================================================
 * THEME SWITCHING SYSTEM (DARK <-> LIGHT)
 * ========================================================================= */
void cluster_apply_theme(bool is_dark)
{
    g_is_dark_theme = is_dark;
    uint32_t bg_col   = is_dark ? 0x08111D : 0xEFF3F8;
    uint32_t text_col = is_dark ? 0xF4F8FC : 0x0F172A;

    if (objects.main) {
        lv_obj_set_style_bg_color(objects.main, lv_color_hex(bg_col), LV_PART_MAIN);
        if (cluster_speed_label) {
            lv_obj_set_style_text_color(cluster_speed_label, lv_color_hex(text_col), LV_PART_MAIN);
        }
        if (cluster_rpm_label) {
            lv_obj_set_style_text_color(cluster_rpm_label, lv_color_hex(text_col), LV_PART_MAIN);
        }
    }
    if (objects.vehicle_dtc) {
        lv_obj_set_style_bg_color(objects.vehicle_dtc, lv_color_hex(bg_col), LV_PART_MAIN);
    }
    if (objects.map) {
        lv_obj_set_style_bg_color(objects.map, lv_color_hex(bg_col), LV_PART_MAIN);
    }
    if (objects.control) {
        lv_obj_set_style_bg_color(objects.control, lv_color_hex(bg_col), LV_PART_MAIN);
    }

    if (cluster_theme_lbl) {
        lv_label_set_text(cluster_theme_lbl, is_dark ? LV_SYMBOL_EYE_OPEN : LV_SYMBOL_EYE_CLOSE);
    }
    printf("Theme switched to: %s\r\n", is_dark ? "DARK" : "LIGHT");
}

void cluster_toggle_theme(void)
{
    cluster_apply_theme(!g_is_dark_theme);
}

static void theme_btn_click_cb(lv_event_t * e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        cluster_toggle_theme();
    }
}

/* =========================================================================
 * SCREEN 1: TAPLO CHÍNH (PORTRAIT 240 x 320)
 * ========================================================================= */
void create_screen_main(void)
{
    lv_obj_t *screen = lv_obj_create(NULL);
    objects.main = screen;
    lv_obj_set_size(screen, 240, 320);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x08111D), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(screen, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(screen, 0, LV_PART_MAIN);

    /* Cử chỉ vuốt */
    lv_obj_add_event_cb(screen, cluster_screen_gesture_cb, LV_EVENT_GESTURE, NULL);

    /* Top strip: DRIVE | D | 24 C | 12:48 | [Theme Button] */
    make_label(screen, "DRIVE", 8, 7, 45, 18, &lv_font_montserrat_14, 0x43D9C5, LV_TEXT_ALIGN_LEFT);
    cluster_gear_label = make_label(screen, "D", 60, 6, 24, 20, &lv_font_montserrat_16, 0x43D9C5, LV_TEXT_ALIGN_CENTER);
    cluster_temp_label = make_label(screen, "24 C", 90, 7, 44, 18, &lv_font_montserrat_14, 0x9FB1C5, LV_TEXT_ALIGN_CENTER);
    cluster_time_label = make_label(screen, "12:48", 140, 7, 44, 18, &lv_font_montserrat_14, 0x9FB1C5, LV_TEXT_ALIGN_CENTER);

    /* Nút nhỏ đổi theme Dark / Light ở góc trên cùng bên phải */
    cluster_btn_theme = lv_btn_create(screen);
    lv_obj_set_pos(cluster_btn_theme, 198, 4);
    lv_obj_set_size(cluster_btn_theme, 34, 22);
    lv_obj_set_style_radius(cluster_btn_theme, 6, LV_PART_MAIN);
    lv_obj_set_style_bg_color(cluster_btn_theme, lv_color_hex(0x1B2C3E), LV_PART_MAIN);
    lv_obj_set_style_border_color(cluster_btn_theme, lv_color_hex(0x43D9C5), LV_PART_MAIN);
    lv_obj_set_style_border_width(cluster_btn_theme, 1, LV_PART_MAIN);
    lv_obj_set_style_pad_all(cluster_btn_theme, 0, LV_PART_MAIN);
    add_button_press_animation(cluster_btn_theme);
    lv_obj_add_event_cb(cluster_btn_theme, theme_btn_click_cb, LV_EVENT_CLICKED, NULL);

    cluster_theme_lbl = lv_label_create(cluster_btn_theme);
    lv_label_set_text(cluster_theme_lbl, LV_SYMBOL_EYE_OPEN);
    lv_obj_set_style_text_font(cluster_theme_lbl, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_set_style_text_color(cluster_theme_lbl, lv_color_hex(0x43D9C5), LV_PART_MAIN);
    lv_obj_center(cluster_theme_lbl);

    /* Divider line */
    lv_obj_t *status = lv_obj_create(screen);
    lv_obj_set_pos(status, 8, 28);
    lv_obj_set_size(status, 224, 1);
    lv_obj_set_style_bg_color(status, lv_color_hex(0x24364A), LV_PART_MAIN);
    lv_obj_set_style_border_width(status, 0, LV_PART_MAIN);

    /* SPEED (Căn chính giữa hoàn hảo x=0, w=240) */
    make_label(screen, "SPEED", 0, 34, 240, 16, &lv_font_montserrat_14, 0x8498AD, LV_TEXT_ALIGN_CENTER);
    cluster_speed_label = make_label(screen, "064", 0, 48, 240, 50, &lv_font_montserrat_48, 0xF4F8FC, LV_TEXT_ALIGN_CENTER);
    make_label(screen, "km/h", 0, 98, 240, 16, &lv_font_montserrat_14, 0x43D9C5, LV_TEXT_ALIGN_CENTER);

    /* TACHOMETER ARC: Hình tròn 170x170, tâm chính xác tại X=120 */
    lv_obj_t *rpm_arc = lv_arc_create(screen);
    cluster_rpm_arc = rpm_arc;
    lv_obj_set_pos(rpm_arc, 35, 114);
    lv_obj_set_size(rpm_arc, 170, 170);
    lv_arc_set_rotation(rpm_arc, 180);
    lv_arc_set_bg_angles(rpm_arc, 0, 180);
    lv_arc_set_range(rpm_arc, 0, 8000);
    lv_arc_set_value(rpm_arc, 2400);
    lv_obj_remove_style(rpm_arc, NULL, LV_PART_KNOB);
    lv_obj_clear_flag(rpm_arc, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_arc_width(rpm_arc, 6, LV_PART_MAIN);
    lv_obj_set_style_arc_color(rpm_arc, lv_color_hex(0x1D2C3C), LV_PART_MAIN);
    lv_obj_set_style_arc_width(rpm_arc, 6, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(rpm_arc, lv_color_hex(0x43D9C5), LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(rpm_arc, LV_OPA_TRANSP, LV_PART_MAIN);

    /* TEXT RPM: Căn giữa tuyệt đối cùng tâm X=120 với Arc */
    make_label(screen, "RPM", 0, 134, 240, 16, &lv_font_montserrat_14, 0x8498AD, LV_TEXT_ALIGN_CENTER);
    cluster_rpm_label = make_label(screen, "2.4", 0, 150, 240, 36, &lv_font_montserrat_32, 0xF4F8FC, LV_TEXT_ALIGN_CENTER);
    make_label(screen, "x1000", 0, 184, 240, 16, &lv_font_montserrat_14, 0x8498AD, LV_TEXT_ALIGN_CENTER);

    /* FUEL PANEL: Căn lề trái 10, phải 10 (Rộng 220px) */
    lv_obj_t *p_fuel = make_panel(screen, 10, 214, 220, 30);
    make_label(p_fuel, "FUEL", 8, 6, 45, 18, &lv_font_montserrat_14, 0x8498AD, LV_TEXT_ALIGN_LEFT);
    lv_obj_t *fuel_bar = lv_bar_create(p_fuel);
    cluster_fuel_bar = fuel_bar;
    lv_obj_set_pos(fuel_bar, 58, 11);
    lv_obj_set_size(fuel_bar, 114, 8);
    lv_bar_set_range(fuel_bar, 0, 100);
    lv_bar_set_value(fuel_bar, 72, LV_ANIM_OFF);
    lv_obj_set_style_bg_color(fuel_bar, lv_color_hex(0x26384A), LV_PART_MAIN);
    lv_obj_set_style_radius(fuel_bar, 4, LV_PART_MAIN);
    lv_obj_set_style_bg_color(fuel_bar, lv_color_hex(0x43D9C5), LV_PART_INDICATOR);
    lv_obj_set_style_radius(fuel_bar, 4, LV_PART_INDICATOR);
    cluster_fuel_label = make_label(p_fuel, "72%", 176, 6, 38, 18, &lv_font_montserrat_14, 0xF4F8FC, LV_TEXT_ALIGN_RIGHT);

    /* ODO & TRIP (2 thẻ đối xứng cân đối) */
    lv_obj_t *p_odo = make_panel(screen, 10, 250, 106, 50);
    make_label(p_odo, "ODO", 8, 4, 90, 16, &lv_font_montserrat_14, 0x8498AD, LV_TEXT_ALIGN_LEFT);
    make_label(p_odo, "12,840 km", 8, 22, 90, 22, &lv_font_montserrat_14, 0xF4F8FC, LV_TEXT_ALIGN_LEFT);

    lv_obj_t *p_trip = make_panel(screen, 124, 250, 106, 50);
    make_label(p_trip, "TRIP", 8, 4, 90, 16, &lv_font_montserrat_14, 0x8498AD, LV_TEXT_ALIGN_LEFT);
    make_label(p_trip, "128.4 km", 8, 22, 90, 22, &lv_font_montserrat_14, 0xF4F8FC, LV_TEXT_ALIGN_LEFT);

    /* Page Indicator */
    make_page_indicator(screen, 0);

    tick_screen_main();
}

/* =========================================================================
 * SCREEN 2: THÔNG TIN XE & MÃ LỖI UDS DTC (PORTRAIT 240 x 320)
 * ========================================================================= */
static void btn_clear_dtc_cb(lv_event_t * e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        printf("Touch Event: Clear DTC requested!\r\n");
        if (cluster_dtc_badge_label) {
            lv_label_set_text(cluster_dtc_badge_label, "ALL CLEAR");
            lv_obj_set_style_text_color(cluster_dtc_badge_label, lv_color_hex(0x43D9C5), LV_PART_MAIN);
        }
        if (cluster_dtc_item1_label) {
            lv_label_set_text(cluster_dtc_item1_label, "No active fault detected.");
        }
        if (cluster_dtc_item2_label) {
            lv_label_set_text(cluster_dtc_item2_label, "ECU System: Healthy");
        }
    }
}

void create_screen_vehicle_dtc(void)
{
    lv_obj_t *screen = lv_obj_create(NULL);
    objects.vehicle_dtc = screen;
    lv_obj_set_size(screen, 240, 320);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x08111D), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(screen, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(screen, 0, LV_PART_MAIN);

    /* Cử chỉ vuốt */
    lv_obj_add_event_cb(screen, cluster_screen_gesture_cb, LV_EVENT_GESTURE, NULL);

    /* Top strip */
    make_label(screen, "VEHICLE HEALTH", 10, 7, 140, 20, &lv_font_montserrat_14, 0x43D9C5, LV_TEXT_ALIGN_LEFT);
    cluster_batt_label = make_label(screen, "12.6V", 160, 7, 70, 20, &lv_font_montserrat_14, 0xF4F8FC, LV_TEXT_ALIGN_RIGHT);

    lv_obj_t *line = lv_obj_create(screen);
    lv_obj_set_pos(line, 10, 28);
    lv_obj_set_size(line, 220, 1);
    lv_obj_set_style_bg_color(line, lv_color_hex(0x24364A), LV_PART_MAIN);
    lv_obj_set_style_border_width(line, 0, LV_PART_MAIN);

    /* Card 1: Battery */
    lv_obj_t *p_batt = make_panel(screen, 10, 34, 220, 52);
    make_label(p_batt, "BATTERY STATUS", 8, 4, 204, 16, &lv_font_montserrat_14, 0x8498AD, LV_TEXT_ALIGN_LEFT);
    make_label(p_batt, "12.6 V", 8, 24, 80, 22, &lv_font_montserrat_16, 0x43D9C5, LV_TEXT_ALIGN_LEFT);
    make_label(p_batt, "Normal (Charging)", 90, 26, 122, 18, &lv_font_montserrat_14, 0x9FB1C5, LV_TEXT_ALIGN_RIGHT);

    /* Card 2: Engine & Oil */
    lv_obj_t *p_coolant = make_panel(screen, 10, 92, 220, 52);
    make_label(p_coolant, "ENGINE & OIL", 8, 4, 204, 16, &lv_font_montserrat_14, 0x8498AD, LV_TEXT_ALIGN_LEFT);
    cluster_coolant_label = make_label(p_coolant, "88 C", 8, 24, 80, 22, &lv_font_montserrat_16, 0xF4F8FC, LV_TEXT_ALIGN_LEFT);
    make_label(p_coolant, "Oil: 2.8 Bar", 90, 26, 122, 18, &lv_font_montserrat_14, 0x9FB1C5, LV_TEXT_ALIGN_RIGHT);

    /* Card 3: UDS Diagnostics */
    lv_obj_t *p_dtc = make_panel(screen, 10, 150, 220, 150);
    make_label(p_dtc, "UDS DIAGNOSTICS", 8, 4, 120, 16, &lv_font_montserrat_14, 0x8498AD, LV_TEXT_ALIGN_LEFT);
    cluster_dtc_badge_label = make_label(p_dtc, "2 FAULTS", 130, 4, 82, 16, &lv_font_montserrat_14, 0xF5A623, LV_TEXT_ALIGN_RIGHT);

    /* DTC Box 1 */
    lv_obj_t *box1 = lv_obj_create(p_dtc);
    lv_obj_set_pos(box1, 8, 24);
    lv_obj_set_size(box1, 204, 30);
    lv_obj_set_style_bg_color(box1, lv_color_hex(0x182434), LV_PART_MAIN);
    lv_obj_set_style_border_color(box1, lv_color_hex(0xF5A623), LV_PART_MAIN);
    lv_obj_set_style_border_width(box1, 1, LV_PART_MAIN);
    lv_obj_set_style_radius(box1, 4, LV_PART_MAIN);
    cluster_dtc_item1_label = make_label(box1, "P0100: MAF Circuit", 4, 4, 194, 20, &lv_font_montserrat_14, 0xF4F8FC, LV_TEXT_ALIGN_LEFT);

    /* DTC Box 2 */
    lv_obj_t *box2 = lv_obj_create(p_dtc);
    lv_obj_set_pos(box2, 8, 58);
    lv_obj_set_size(box2, 204, 30);
    lv_obj_set_style_bg_color(box2, lv_color_hex(0x182434), LV_PART_MAIN);
    lv_obj_set_style_border_color(box2, lv_color_hex(0xF5A623), LV_PART_MAIN);
    lv_obj_set_style_border_width(box2, 1, LV_PART_MAIN);
    lv_obj_set_style_radius(box2, 4, LV_PART_MAIN);
    cluster_dtc_item2_label = make_label(box2, "P0113: IAT High In", 4, 4, 194, 20, &lv_font_montserrat_14, 0xF4F8FC, LV_TEXT_ALIGN_LEFT);

    /* Nút Clear DTC có animation */
    lv_obj_t *btn_clear = lv_btn_create(p_dtc);
    lv_obj_set_pos(btn_clear, 35, 102);
    lv_obj_set_size(btn_clear, 150, 34);
    lv_obj_set_style_bg_color(btn_clear, lv_color_hex(0x24364A), LV_PART_MAIN);
    lv_obj_set_style_border_color(btn_clear, lv_color_hex(0x43D9C5), LV_PART_MAIN);
    lv_obj_set_style_border_width(btn_clear, 1, LV_PART_MAIN);
    lv_obj_set_style_radius(btn_clear, 6, LV_PART_MAIN);
    add_button_press_animation(btn_clear);
    lv_obj_add_event_cb(btn_clear, btn_clear_dtc_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *btn_lbl = lv_label_create(btn_clear);
    lv_label_set_text(btn_lbl, LV_SYMBOL_TRASH " Clear DTC");
    lv_obj_set_style_text_font(btn_lbl, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_center(btn_lbl);

    /* Page Indicator */
    make_page_indicator(screen, 1);

    tick_screen_vehicle_dtc();
}

/* =========================================================================
 * SCREEN 3: BẢN ĐỒ / NAVIGATION CHỈ ĐƯỜNG MINI (PORTRAIT 240 x 320)
 * ========================================================================= */
void create_screen_map(void)
{
    lv_obj_t *screen = lv_obj_create(NULL);
    objects.map = screen;
    lv_obj_set_size(screen, 240, 320);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x08111D), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(screen, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(screen, 0, LV_PART_MAIN);

    /* Cử chỉ vuốt */
    lv_obj_add_event_cb(screen, cluster_screen_gesture_cb, LV_EVENT_GESTURE, NULL);

    /* Top strip */
    make_label(screen, "NAVIGATION", 10, 7, 120, 20, &lv_font_montserrat_14, 0x43D9C5, LV_TEXT_ALIGN_LEFT);
    make_label(screen, LV_SYMBOL_GPS " 3D FIX", 140, 7, 90, 20, &lv_font_montserrat_14, 0x43D9C5, LV_TEXT_ALIGN_RIGHT);

    lv_obj_t *line = lv_obj_create(screen);
    lv_obj_set_pos(line, 10, 28);
    lv_obj_set_size(line, 220, 1);
    lv_obj_set_style_bg_color(line, lv_color_hex(0x24364A), LV_PART_MAIN);
    lv_obj_set_style_border_width(line, 0, LV_PART_MAIN);

    /* Card 1: Hướng rẽ lớn (Căn giữa hoàn hảo) */
    lv_obj_t *turn_card = make_panel(screen, 10, 34, 220, 134);

    lv_obj_t *circle_arrow = lv_obj_create(turn_card);
    lv_obj_set_pos(circle_arrow, 78, 10);
    lv_obj_set_size(circle_arrow, 64, 64);
    lv_obj_set_style_radius(circle_arrow, LV_RADIUS_CIRCLE, LV_PART_MAIN);
    lv_obj_set_style_bg_color(circle_arrow, lv_color_hex(0x182C3F), LV_PART_MAIN);
    lv_obj_set_style_border_color(circle_arrow, lv_color_hex(0x43D9C5), LV_PART_MAIN);
    lv_obj_set_style_border_width(circle_arrow, 2, LV_PART_MAIN);
    lv_obj_clear_flag(circle_arrow, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t *arrow_lbl = lv_label_create(circle_arrow);
    lv_label_set_text(arrow_lbl, LV_SYMBOL_LEFT);
    lv_obj_set_style_text_font(arrow_lbl, &lv_font_montserrat_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(arrow_lbl, lv_color_hex(0x43D9C5), LV_PART_MAIN);
    lv_obj_center(arrow_lbl);

    cluster_nav_dist_label = make_label(turn_card, "250 m", 0, 80, 220, 34, &lv_font_montserrat_32, 0xF4F8FC, LV_TEXT_ALIGN_CENTER);
    cluster_nav_action_label = make_label(turn_card, "Turn Left Ahead", 0, 112, 220, 18, &lv_font_montserrat_14, 0x43D9C5, LV_TEXT_ALIGN_CENTER);

    /* Card 2: Tuyến đường kế tiếp */
    lv_obj_t *street_card = make_panel(screen, 10, 174, 220, 52);
    make_label(street_card, "NEXT STREET", 8, 4, 204, 16, &lv_font_montserrat_14, 0x8498AD, LV_TEXT_ALIGN_LEFT);
    cluster_nav_street_label = make_label(street_card, "Nguyen Trai St.", 8, 24, 204, 22, &lv_font_montserrat_16, 0xF4F8FC, LV_TEXT_ALIGN_LEFT);

    /* Card 3: ETA & Tốc độ giới hạn */
    lv_obj_t *info_card = make_panel(screen, 10, 232, 220, 68);

    /* Biển báo giới hạn tốc độ tròn 60 */
    lv_obj_t *speed_sign = lv_obj_create(info_card);
    lv_obj_set_pos(speed_sign, 10, 16);
    lv_obj_set_size(speed_sign, 36, 36);
    lv_obj_set_style_radius(speed_sign, LV_RADIUS_CIRCLE, LV_PART_MAIN);
    lv_obj_set_style_border_color(speed_sign, lv_color_hex(0xFF5C66), LV_PART_MAIN);
    lv_obj_set_style_border_width(speed_sign, 3, LV_PART_MAIN);
    lv_obj_set_style_bg_color(speed_sign, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_clear_flag(speed_sign, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t *speed_limit = lv_label_create(speed_sign);
    lv_label_set_text(speed_limit, "60");
    lv_obj_set_style_text_font(speed_limit, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_set_style_text_color(speed_limit, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_center(speed_limit);

    cluster_nav_dist_label = make_label(info_card, "14.2 km", 58, 12, 152, 22, &lv_font_montserrat_16, 0xF4F8FC, LV_TEXT_ALIGN_LEFT);
    cluster_nav_eta_label = make_label(info_card, "ETA: 18 min", 58, 36, 152, 20, &lv_font_montserrat_14, 0x43D9C5, LV_TEXT_ALIGN_LEFT);

    /* Page Indicator */
    make_page_indicator(screen, 2);

    tick_screen_map();
}

/* =========================================================================
 * SCREEN 4: BẢNG NÚT BẤM CẢM ỨNG CÓ ANIMATION TRẠNG THÁI (PORTRAIT 240 x 320)
 * ========================================================================= */
static void control_button_toggle_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        bool is_checked = lv_obj_has_state(btn, LV_STATE_CHECKED);
        lv_obj_t *led_dot = (lv_obj_t *)lv_event_get_user_data(e);

        if (is_checked) {
            lv_obj_set_style_bg_color(btn, lv_color_hex(0x133E47), LV_PART_MAIN);
            lv_obj_set_style_border_color(btn, lv_color_hex(0x43D9C5), LV_PART_MAIN);
            lv_obj_set_style_border_width(btn, 2, LV_PART_MAIN);
            if (led_dot) {
                lv_obj_set_style_bg_color(led_dot, lv_color_hex(0x43D9C5), LV_PART_MAIN);
            }
        } else {
            lv_obj_set_style_bg_color(btn, lv_color_hex(0x101B29), LV_PART_MAIN);
            lv_obj_set_style_border_color(btn, lv_color_hex(0x24364A), LV_PART_MAIN);
            lv_obj_set_style_border_width(btn, 1, LV_PART_MAIN);
            if (led_dot) {
                lv_obj_set_style_bg_color(led_dot, lv_color_hex(0x24364A), LV_PART_MAIN);
            }
        }
        printf("Control Button Toggled: State = %d\r\n", is_checked);
    }
}

static lv_obj_t *make_control_button(lv_obj_t *parent, lv_coord_t x, lv_coord_t y,
                                    lv_coord_t w, lv_coord_t h,
                                    const char *icon, const char *title, const char *sub,
                                    bool default_on)
{
    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_set_pos(btn, x, y);
    lv_obj_set_size(btn, w, h);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_style_radius(btn, 8, LV_PART_MAIN);
    lv_obj_set_style_pad_all(btn, 8, LV_PART_MAIN);

    /* Thêm hiệu ứng co lõm (Press tactile animation) */
    add_button_press_animation(btn);

    /* Đèn LED indicator trạng thái ở góc trên bên phải */
    lv_obj_t *led = lv_obj_create(btn);
    lv_obj_set_pos(led, w - 24, 6);
    lv_obj_set_size(led, 10, 10);
    lv_obj_set_style_radius(led, LV_RADIUS_CIRCLE, LV_PART_MAIN);
    lv_obj_set_style_border_width(led, 0, LV_PART_MAIN);
    lv_obj_clear_flag(led, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);

    /* Biểu tượng Icon (Font 32) */
    lv_obj_t *lbl_icon = lv_label_create(btn);
    lv_label_set_text(lbl_icon, icon);
    lv_obj_set_style_text_font(lbl_icon, &lv_font_montserrat_32, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_icon, lv_color_hex(0x43D9C5), LV_PART_MAIN);
    lv_obj_set_pos(lbl_icon, 4, 8);

    /* Tiêu đề */
    lv_obj_t *lbl_title = lv_label_create(btn);
    lv_label_set_text(lbl_title, title);
    lv_obj_set_style_text_font(lbl_title, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_title, lv_color_hex(0xF4F8FC), LV_PART_MAIN);
    lv_obj_set_pos(lbl_title, 4, 56);

    /* Trạng thái phụ */
    lv_obj_t *lbl_sub = lv_label_create(btn);
    lv_label_set_text(lbl_sub, sub);
    lv_obj_set_style_text_font(lbl_sub, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_set_style_text_color(lbl_sub, lv_color_hex(0x8498AD), LV_PART_MAIN);
    lv_obj_set_pos(lbl_sub, 4, 78);

    /* Khởi tạo trạng thái ban đầu */
    if (default_on) {
        lv_obj_add_state(btn, LV_STATE_CHECKED);
        lv_obj_set_style_bg_color(btn, lv_color_hex(0x133E47), LV_PART_MAIN);
        lv_obj_set_style_border_color(btn, lv_color_hex(0x43D9C5), LV_PART_MAIN);
        lv_obj_set_style_border_width(btn, 2, LV_PART_MAIN);
        lv_obj_set_style_bg_color(led, lv_color_hex(0x43D9C5), LV_PART_MAIN);
    } else {
        lv_obj_set_style_bg_color(btn, lv_color_hex(0x101B29), LV_PART_MAIN);
        lv_obj_set_style_border_color(btn, lv_color_hex(0x24364A), LV_PART_MAIN);
        lv_obj_set_style_border_width(btn, 1, LV_PART_MAIN);
        lv_obj_set_style_bg_color(led, lv_color_hex(0x24364A), LV_PART_MAIN);
    }

    lv_obj_add_event_cb(btn, control_button_toggle_cb, LV_EVENT_VALUE_CHANGED, (void *)led);
    return btn;
}

void create_screen_control(void)
{
    lv_obj_t *screen = lv_obj_create(NULL);
    objects.control = screen;
    lv_obj_set_size(screen, 240, 320);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x08111D), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(screen, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(screen, 0, LV_PART_MAIN);

    /* Cử chỉ vuốt */
    lv_obj_add_event_cb(screen, cluster_screen_gesture_cb, LV_EVENT_GESTURE, NULL);

    /* Top strip */
    make_label(screen, "CABIN CONTROLS", 10, 7, 140, 20, &lv_font_montserrat_14, 0x43D9C5, LV_TEXT_ALIGN_LEFT);
    make_label(screen, "TOUCH", 160, 7, 70, 20, &lv_font_montserrat_14, 0x9FB1C5, LV_TEXT_ALIGN_RIGHT);

    lv_obj_t *line = lv_obj_create(screen);
    lv_obj_set_pos(line, 10, 28);
    lv_obj_set_size(line, 220, 1);
    lv_obj_set_style_bg_color(line, lv_color_hex(0x24364A), LV_PART_MAIN);
    lv_obj_set_style_border_width(line, 0, LV_PART_MAIN);

    /* 4 Nút điều khiển cảm ứng kích thước lớn cân xứng (106 x 126) */
    /* Hàng 1 (y = 36) */
    cluster_btn_ac = make_control_button(screen, 10, 36, 106, 126,
                                         LV_SYMBOL_POWER, "A/C AIR", "21.5 C", true);

    cluster_btn_fan = make_control_button(screen, 124, 36, 106, 126,
                                          LV_SYMBOL_REFRESH, "BLOWER", "Fan: 3", false);

    /* Hàng 2 (y = 168) */
    cluster_btn_light = make_control_button(screen, 10, 168, 106, 126,
                                           LV_SYMBOL_EYE_OPEN, "LIGHTS", "AUTO", false);

    cluster_btn_hazard = make_control_button(screen, 124, 168, 106, 126,
                                            LV_SYMBOL_WARNING, "HAZARD", "Flasher", false);

    /* Page Indicator */
    make_page_indicator(screen, 3);

    tick_screen_control();
}

/* =========================================================================
 * TICK DISPATCHER & CREATION ENTRY POINT
 * ========================================================================= */
void tick_screen_main(void) { }
void tick_screen_vehicle_dtc(void) { }
void tick_screen_map(void) { }
void tick_screen_control(void) { }

typedef void (*tick_screen_func_t)(void);
static tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_vehicle_dtc,
    tick_screen_map,
    tick_screen_control
};

void tick_screen(int screen_index)
{
    if (screen_index >= 0 && screen_index < _SCREEN_ID_LAST) {
        tick_screen_funcs[screen_index]();
    }
}

void tick_screen_by_id(enum ScreensEnum screenId)
{
    tick_screen(screenId - 1);
}

ext_font_desc_t fonts[] = {
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

uint32_t active_theme_index = 0;

void create_screens(void)
{
    lv_disp_t *display = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(display,
        lv_color_hex(0x43D9C5), lv_color_hex(0xFF5C66), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(display, theme);

    /* Khởi tạo tuần tự cả 4 màn hình chuẩn Portrait 240x320 */
    create_screen_main();
    create_screen_vehicle_dtc();
    create_screen_map();
    create_screen_control();
}
