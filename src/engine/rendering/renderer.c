#include "include/renderer.h"
#include "engine/include/window.h"
#include <stdlib.h>

static void swap_buffer(GardenRenderer *renderer) {
  glfwSwapBuffers(garden_window_get_window(renderer->window));
  glClearColor(renderer->clear_color.r, renderer->clear_color.g,
               renderer->clear_color.b, renderer->clear_color.a);
  glClear(renderer->clear_mask);
}
GardenRenderer *garden_renderer_create(GardenWindow *window,
                                       GardenColor clear_color,
                                       GLbitfield clear_mask) {
  GardenRenderer *renderer = malloc(sizeof(GardenRenderer));
  renderer->window = window;
  renderer->clear_color = clear_color;
  renderer->clear_mask = clear_mask;

  renderer->swap = swap_buffer;
  return renderer;
};

void garden_renderer_destroy(GardenRenderer *renderer) { free(renderer); };