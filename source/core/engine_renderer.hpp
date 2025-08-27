#include <raylib.h>
#include "utils/colors.h"

inline void draw_rect(int x, int y, int h, int w, const char* tint = "#ffffff") {
    DrawRectangle(x, y, w, h, color_to_raylib(hex_to_color(tint)));
}

inline void draw_pixel(int x, int y, const char* tint = "#ffffff") {
    DrawPixel(x, y, color_to_raylib(hex_to_color(tint)));
}

inline void clear_screen(const char* bg_color = "#ffffff") {
    ClearBackground(color_to_raylib(hex_to_color(bg_color)));
}

inline void draw_line(int sX, int sY, int eX, int eY, const char* tint = "#FFFFFF") {
    DrawLine(sX, sY, eX, eY, color_to_raylib(hex_to_color(tint)));
}