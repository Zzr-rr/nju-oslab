#include <am.h>
#include <amdev.h>
#include <klib.h>
#include <klib-macros.h>
#include "img.h"

#define SIDE 1

static int w, h;  // Screen size

#define KEYNAME(key) \
  [AM_KEY_##key] = #key,
static const char *key_names[] = {AM_KEYS(KEYNAME)};

static inline void puts(const char *s) {
    for (; *s; s++) putch(*s);
}

void print_key() {
    AM_INPUT_KEYBRD_T event = {.keycode = AM_KEY_NONE};
    ioe_read(AM_INPUT_KEYBRD, &event);
    if (event.keycode != AM_KEY_NONE && event.keydown) {
        puts("Key pressed: ");
        puts(key_names[event.keycode]);
        puts("\n");

        // Keyboard ESCAPE will interrupt the system.
        if (event.keycode == AM_KEY_ESCAPE) {
            halt(1);
        }
    }
}

static void draw_tile(int x, int y, int w, int h, uint32_t color) {
    uint32_t pixels[w * h];   // WARNING: large stack-allocated memory
    AM_GPU_FBDRAW_T event = {
            .x = x, .y = y, .w = w, .h = h, .sync = 1,
            .pixels = pixels,
    };
    for (int i = 0; i < w * h; i++) {
        pixels[i] = color;
    }
    ioe_write(AM_GPU_FBDRAW, &event);
}

void splash() {
    AM_GPU_CONFIG_T info = {0};
    ioe_read(AM_GPU_CONFIG, &info);

    w = info.width;
    h = info.height;
    // w - screen width
    // h - screen height
    int w_pixel = w / SIDE;
    int h_pixel = h / SIDE;

    printf("w_pixel = %d\n", w_pixel);
    printf("h_pixel = %d\n", h_pixel);

    printf("img_width = %d\n", img_width);
    printf("img_height = %d\n", img_height);



    for (int x = 0; x * SIDE <= w; x++) {
        for (int y = 0; y * SIDE <= h; y++) {
            int mapping_x = ((float) img_width / (float) w_pixel) * x;
            int mapping_y = ((float) img_height / (float) h_pixel) * y;
            if (mapping_x * img_width + mapping_y <
                img_width * img_height) {   // assuming __0x3f_jpg has 556*556 elements
                draw_tile(x * SIDE, y * SIDE, SIDE, SIDE, __0x3f_jpg[mapping_x * img_width + mapping_y]);
            }
        }
    }
}

// Operating system is a C program!
int main(const char *args) {
    ioe_init();

    puts("mainargs = \"");
    puts(args);  // make run mainargs=xxx
    puts("\"\n");

    splash();

    puts("Press any key to see its key code...\n");
    while (1) {
        print_key();
    }
    return 0;
}
