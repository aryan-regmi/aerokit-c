#include "src/application/asen3111_ca1_p1.h"
#include "src/core/allocator.h"
#include "src/core/numerical_integration.h"
#include "src/display/init.h"
#include <stdio.h>

#define PROJECT_NAME "aerokit"

double tstfn(double x) { return x * x; }

int main(void) {
  akD_App app = {
      .sdl_init_flags = SDL_INIT_VIDEO,
      .window = akD_createWindow("MY APP", DEFAULT_WINPOS, DEFAULT_WINSIZE, 0),
      .renderer = akD_createRenderer(app.window, SDL_RENDERER_ACCELERATED),
  };

  akD_appSetClearColor(&app, (akD_Rgba){
                                 .red = 80,
                                 .green = 80,
                                 .blue = 100,
                                 .alpha = 255,
                             });

  akD_appInit(&app);

  return 0;
}
