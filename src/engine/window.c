#include "include/window.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>

Result garden_window_create(GLFWmonitor *monitor) {

  GardenWindow *window = malloc(sizeof(GardenWindow));
  if (window == NULL) {
    return result_error(error_create("Failed to allocate memory for window"));
  }

  const GLFWvidmode *mode = glfwGetVideoMode(monitor);
  if (mode == NULL) {
    free(window);
    return result_error(error_create("Failed to get video mode"));
  }

  window->width = mode->width;
  window->height = mode->height;
  window->title = "Garden Simulator";

  // For debugging, switch to windowed mode by using NULL for monitor
  window->window = glfwCreateWindow(window->width, window->height,
                                    window->title, monitor, NULL);

  if (window->window == NULL) {
    garden_window_destroy(window);
    return result_error(error_create("Failed to create window"));
  }

  return result_ok(window);
}

void garden_window_destroy(GardenWindow *window) {
  if (window->window != NULL) {
    glfwDestroyWindow(window->window);
  }
  glfwTerminate();
  free(window);
}
