#include <cstdio>
#include <raylib.h>
#include <string>
#include <cstdlib>
#include "engine_logging.hpp"

static std::string default_settings[] = {
	"109", // Resolution X
	"101"  // Resolution Y
};

// TODO: set path from program

#pragma pack(push, 1)
struct core_settings {
	char core_name[64] = "A core";

	float scale = 1;

	// Joypad (keycode)
	// d-pad
	int button_up = 265;
	int button_down = 264;
	int button_left = 263;
	int button_right = 262;
	// start/select
	int button_start = 257;
	int button_select = 259;
	// buttons
	int button_b = 90;
	int button_a = 88;
	int button_y = 67;
	int button_x = 86;
	// top buttons
	int button_l = 65;
	int button_r = 83;
};
#pragma pack(pop)

static void load_settings(core_settings *settings) {
	FILE *f;

	f = fopen("core_settings.dat", "rb");

	if (f == NULL) {
		log("Failed to open settings\n", ERROR);
		log("Using default settings!\n", WARNING);
		return;
	}

	size_t read = fread(settings, sizeof(core_settings), 1, f);

	fclose(f);

	if (read != 1) {
		log("Failed to read settings\n", ERROR);
	}
}

static void save_settings(core_settings *settings) {
	FILE *f;

	f = fopen("core_settings.dat", "wb");

	if (f == NULL) {
		log("Failed to open settings file for writing\n", ERROR);
		return;
	}
	size_t written = fwrite(settings, sizeof(*settings), 1, f);
	fclose(f);

	if (written < 1) {
		log("Failed to write to file\n", ERROR);
	} else {
		log("Settings saved successfully\n", LOG);
	}
}