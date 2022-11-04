#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct akD_WinPos {
  int x, y;
} akD_WinPos;

static const akD_WinPos DEFAULT_WINPOS = {SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED};

typedef struct akD_WinSize {
  int w, h;
} akD_WinSize;

static const akD_WinSize DEFAULT_WINSIZE = {1280, 720};

/// Creates a window.
SDL_Window *akD_createWindow(const char *win_name, akD_WinPos win_pos,
                             akD_WinSize win_size, uint32_t sdl_window_flags);
/// Creates a renderer.
SDL_Renderer *akD_createRenderer(SDL_Window *win, uint32_t sdl_renderer_flags);

typedef struct akD_App {
  uint32_t sdl_init_flags;

  SDL_Window *window;
  SDL_Renderer *renderer;
} akD_App;

/// Initializes the application.
void akD_appInit(akD_App *app);

typedef struct akD_Rgba {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t alpha;
} akD_Rgba;

/// Sets the clear color for the application.
void akD_appSetClearColor(akD_App *app, akD_Rgba color);

#define LOOP(break_flag, expr)                                                 \
  while (!break_flag) {                                                        \
    expr                                                                       \
  }
