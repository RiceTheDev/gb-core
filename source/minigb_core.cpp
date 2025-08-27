#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <raylib.h>
#include "third_party/gb/MiniGB.h"
#include "core/engine_renderer.hpp"
#include "core/engine_input.hpp"
#include "core/engine_settings.hpp"

core_settings settings;

const int GB_WIDTH = 160;
const int GB_HEIGHT = 144;
const int SCALE = 1; // TODO: LOAD THIS FROM THE SETTINGS, DUMBASS

GB_core_t *gbCore = nullptr;

void core_update_keys() {
    if (!gbCore) return;
    
    gbCore->button_b = is_key_down(settings.button_b);
    gbCore->button_a = is_key_down(settings.button_a);
    gbCore->button_select = is_key_down(settings.button_select);
    gbCore->button_start = is_key_down(settings.button_start);
    gbCore->button_up = is_key_down(settings.button_up);
    gbCore->button_down = is_key_down(settings.button_down);
    gbCore->button_left = is_key_down(settings.button_left);
    gbCore->button_right = is_key_down(settings.button_right);
}

static void color_to_hex(uint32_t color, char* hex) {
    sprintf(hex, "#%02X%02X%02X",
        (color >> 16) & 0xFF,
        (color >> 8) & 0xFF,
        color & 0xFF);
}

extern "C" void core_start() {
    gbCore = (GB_core_t*)calloc(1, sizeof(GB_core_t));
    GB_init(gbCore);
    load_settings(&settings);
    log("MiniGB Started\n", LOG);
    save_settings(&settings);
}

extern "C" void core_update() {
    if (!gbCore) return;

    core_update_keys();

    GB_run_to_next_frame(gbCore);

    const uint32_t* fb = GBPPU_get_display_screen_buffer(gbCore);

    clear_screen((char*)"#000000");

    char hex[16];
    for (int y = 0; y < GB_HEIGHT; y++) {
        for (int x = 0; x < GB_WIDTH; x++) {
            uint32_t color = fb[y * GB_WIDTH + x];
            color_to_hex(color, hex);

            draw_rect(((atoi(default_settings[0].c_str()) - (GB_WIDTH * SCALE)) / 2) + x * SCALE, ((atoi(default_settings[1].c_str()) - (GB_HEIGHT * SCALE)) / 2) + y * SCALE, SCALE, SCALE, hex);
        }
    }
}

extern "C" void core_stop() {
    if (gbCore) {
        free(gbCore);
        gbCore = nullptr;
    }
    log("MiniGB Stopped\n", LOG);
    
}

extern "C" void core_load_rom(const char* filepath) {
    std::ifstream file(filepath, std::ios::binary | std::ios::ate);
    if (!file) {
        char buf[512];
        snprintf(buf, sizeof(buf), "Failed to open ROM %s\n", filepath);
        log(buf, ERROR);
        
        return;
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    if (size > sizeof(gbCore->rom)) {
        log("ROM is too big for buffer!\n", ERROR);
        return;
    }

    if (!file.read((char*)gbCore->rom, size)) {
        log("Failed to read ROM data\n", ERROR);
        return;
    }
}
