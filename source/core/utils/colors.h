#include <stdio.h>
#include <raylib.h>

struct color {
    int r;
    int g;
    int b;
    int a = 255;
};

inline color hex_to_color(const char* hex) {
    color out;

    sscanf(hex, "#%02x%02x%02x", &out.r, &out.g, &out.b);

    return out;
}

inline Color color_to_raylib(color in) {
    Color out;
    out.r = in.r;
    out.g = in.g;
    out.b = in.b;
    out.a = in.a;
    return out;
}