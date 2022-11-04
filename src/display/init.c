#include "init.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

/// Initializes SDL with the given flags.
static inline void akD_init(uint32_t sdl_flags) {
  int err = SDL_Init(sdl_flags);

  if (err < 0) {
    fprintf(stderr, "[ERROR] Couldn't initialize SDL: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

/// Deinitializes SDL.
static inline void akD_deinit(void) { SDL_Quit(); }

SDL_Window *akD_createWindow(const char *win_name, akD_WinPos win_pos,
                             akD_WinSize win_size, uint32_t sdl_window_flags) {
  SDL_Window *win = SDL_CreateWindow(win_name, win_pos.x, win_pos.y, win_size.w,
                                     win_size.h, sdl_window_flags);

  if (!win) {
    fprintf(stderr, "[ERROR] Failed to open %d x %d window: %s\n", win_size.w,
            win_size.h, SDL_GetError());
    exit(EXIT_FAILURE);
  }

  return win;
}

SDL_Renderer *akD_createRenderer(SDL_Window *win, uint32_t sdl_renderer_flags) {
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, sdl_renderer_flags);

  if (!renderer) {
    fprintf(stderr, "[ERROR] Failed to create renderer: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  return renderer;
}

/// Handles events.
void akD_handleEvent(SDL_Event event, bool *break_loop) {
  SDL_WaitEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    *break_loop = true;
    break;
  }
}

void akD_appInit(akD_App *app) {
  akD_init(app->sdl_init_flags);

  SDL_Event event = {0};
  bool quit = false;

  LOOP(quit,

       SDL_RenderClear(app->renderer);

       akD_handleEvent(event, &quit);

       SDL_RenderPresent(app->renderer);

       SDL_Delay(16););

  SDL_DestroyWindow(app->window);
  SDL_DestroyRenderer(app->renderer);
  akD_deinit();
}

void akD_appSetClearColor(akD_App *app, akD_Rgba color) {
  SDL_SetRenderDrawColor(app->renderer, color.red, color.green, color.blue,
                         color.alpha);
}
