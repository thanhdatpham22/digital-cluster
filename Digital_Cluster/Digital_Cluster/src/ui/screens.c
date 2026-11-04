#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;

screen_main_state_t screen_main_state;
// Khai báo biến toàn cục ở đầu file
lv_obj_t * my_meter_obj = NULL;
//
// Event handlers
//

lv_obj_t *tick_value_change_obj;
// 1. Khai báo 2 con trỏ toàn cục để timer có thể truy cập
lv_obj_t * my_signal_chart = NULL;
lv_chart_series_t * my_signal_series = NULL;
lv_obj_t * signal_label_obj = NULL;
//
// Screens
//
static void switch_led_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * sw = lv_event_get_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        // Kiểm tra xem Switch đang BẬT (ON) hay TẮT (OFF)
        if (lv_obj_has_state(sw, LV_STATE_CHECKED)) {
            // Khi Bật: Đổi LED obj0 sang màu Đỏ
            lv_led_set_color(objects.obj0, lv_color_hex(0xff0000));
        } else {
            // Khi Tắt: Đổi LED obj0 về lại màu Xanh dương gốc
            lv_led_set_color(objects.obj0, lv_color_hex(0x0000ff));
        }
    }
}
static void switch_led2_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * sw = lv_event_get_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        // Kiểm tra xem Switch đang BẬT (ON) hay TẮT (OFF)
        if (lv_obj_has_state(sw, LV_STATE_CHECKED)) {
            // Khi Bật: Đổi LED obj0 sang màu Đỏ
            lv_led_set_color(objects.obj1, lv_color_hex(0x00ff00));
        } else {
            // Khi Tắt: Đổi LED obj0 về lại màu Xanh dương gốc
            lv_led_set_color(objects.obj1, lv_color_hex(0x0000ff));
        }
    }
}
void create_screen_main() {
    screen_main_state_t *state = &screen_main_state;
    (void)state;
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            lv_obj_set_pos(obj, 0, 283);
            lv_obj_set_size(obj, 50, 25);
            lv_obj_add_event_cb(obj, switch_led_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            lv_obj_set_pos(obj, -2, 251);
            lv_obj_set_size(obj, 50, 25);
            lv_obj_add_event_cb(obj, switch_led2_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
        }
        {
            lv_obj_t *obj = lv_chart_create(parent_obj);
            my_signal_chart = obj;
            lv_obj_set_pos(obj, 109, 4);
            lv_obj_set_size(obj, 121, 94);
            // Cấu hình kiểu biểu đồ và chế độ cuộn sóng
			lv_chart_set_type(obj, LV_CHART_TYPE_LINE);                  // Vẽ dạng đường line
			lv_chart_set_point_count(obj, 20);                          // Hiển thị 20 điểm trên trục hoành
			lv_chart_set_range(obj, LV_CHART_AXIS_PRIMARY_Y, 0, 100);   // Thang đo biên độ tín hiệu từ 0 - 100
			lv_chart_set_update_mode(obj, LV_CHART_UPDATE_MODE_SHIFT);  // Dữ liệu mới đẩy vào bên phải, cuộn sóng sang trái

			// Thêm 1 đường Series màu xanh lá (hoặc xanh dương tùy bạn chọn)
			my_signal_series = lv_chart_add_series(obj, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);
        }
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 104, 267);
            lv_obj_set_size(obj, 32, 32);
            lv_led_set_color(obj, lv_color_hex(0x0000ff));
            lv_led_set_brightness(obj, 255);
        }
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 202, 267);
            lv_obj_set_size(obj, 32, 32);
            lv_led_set_color(obj, lv_color_hex(0x0000ff));
            lv_led_set_brightness(obj, 255);
        }
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 153, 267);
            lv_obj_set_size(obj, 32, 32);
            lv_led_set_color(obj, lv_color_hex(0x0000ff));
            lv_led_set_brightness(obj, 255);
        }
        {
            lv_obj_t *obj = lv_arc_create(parent_obj);
            lv_obj_set_pos(obj, 7, 4);
            lv_obj_set_size(obj, 97, 94);
            lv_arc_set_value(obj, 25);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 25, 43);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Ennergy");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            signal_label_obj = obj;
            lv_obj_set_pos(obj, 147, 99);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Signal: --%");
        }
        {
            lv_obj_t *obj = lv_meter_create(parent_obj);
            my_meter_obj = obj;
            lv_obj_set_pos(obj, 7, 107);
            lv_obj_set_size(obj, 134, 134);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                state->scale = scale;
                lv_meter_set_scale_ticks(obj, scale, 41, 1, 5, lv_color_hex(0xa0a0a0));
                lv_meter_set_scale_major_ticks(obj, scale, 8, 3, 10, lv_color_hex(0x000000), 10);
                lv_meter_set_scale_range(obj, scale, 0, 200, 300, 120);
                {
                    lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 3, lv_color_hex(0x0000ff), -28);
                    state->indicator = indicator;
                    lv_meter_set_indicator_value(obj, indicator, 30);
                }
            }
        }
        {
            lv_obj_t *obj = lv_line_create(parent_obj);
            lv_obj_set_pos(obj, 137, 200);
            lv_obj_set_size(obj, LV_PCT(40), LV_SIZE_CONTENT);
            static lv_point_t line_points[] = {
                { 0, 0 },
                { 50, 50 },
                { 100, 0 },
                { 150, 50 },
                { 200, 0 }
            };
            lv_line_set_points(obj, line_points, 5);
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    screen_main_state_t *state = &screen_main_state;
    (void)state;
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 1) {
        tick_screen_funcs[screen_index]();
    }
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen(screenId - 1);
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
// Color themes
//

uint32_t active_theme_index = 0;

//
//
//

void create_screens() {

// Set default LVGL theme
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    // Initialize screens
    // Create screens
    create_screen_main();
}
