#include "include/window.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

static inline void callback_fb_resize(GLFWwindow *window, int width,
                                      int height) {
  GardenWindowData *data = glfwGetWindowUserPointer(window);
  data->width = width;
  data->height = height;

  glViewport(0, 0, width, height);
}

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

  window->data.width = mode->width / 2;
  window->data.height = mode->height / 2;
  window->title = "Garden Simulator";

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  window->window = glfwCreateWindow(window->data.width, window->data.height,
                                    window->title, NULL, NULL);

  if (window->window == NULL) {
    garden_window_destroy(window);
    return result_error(error_create("Failed to create window"));
  }

  garden_window_callbacks(window);

  return result_ok(window);
}

void garden_window_callbacks(GardenWindow *window) {
  glfwSetWindowUserPointer(window->window, &window->data);
  glfwSetFramebufferSizeCallback(window->window, callback_fb_resize);
};

void garden_window_destroy(GardenWindow *window) {
  if (window->window != NULL) {
    glfwDestroyWindow(window->window);
  }
  glfwTerminate();
  free(window);
}
