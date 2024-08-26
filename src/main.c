#include "engine/include/renderer.h"
#include "engine/include/window.h"
#include "utils/include/result.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

int main() {
  if (!glfwInit()) {
    printf("Failed to initialize GLFW\n");
    return 1;
  }

  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  if (monitor == NULL) {
    printf("Failed to get primary monitor\n");
    glfwTerminate();
    return 1;
  }

  Result win_res = garden_window_create(monitor);
  if (result_is_error(&win_res)) {
    Error *error = result_unwrap_error(&win_res);
    printf("Failed to create window: %s\n", error->message);
    error_destroy(error);
    return 1;
  }
  GardenWindow *window = (GardenWindow *)result_unwrap(&win_res);
  GardenRenderer *renderer = garden_renderer_create(
      window, garden_color_create(0.0f, 0.0f, 0.0f, 1.0f), GL_COLOR_BUFFER_BIT);

  while (!glfwWindowShouldClose(window->window)) {
    glfwPollEvents();

    renderer->swap(renderer);
  }

  garden_renderer_destroy(renderer);
  garden_window_destroy(window);
  return 0;
}
