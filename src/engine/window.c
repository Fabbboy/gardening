#include "include/window.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static inline Result tryinit_glfw() {
  if (!glfwInit()) {
    return result_error(error_create("Failed to initialize GLFW"));
  }
  return result_ok(NULL);
}

static inline void callback_fb_resize(GLFWwindow *window, int width,
                                      int height) {
  GardenWindowData *data = glfwGetWindowUserPointer(window);
  data->width = width;
  data->height = height;

  glViewport(0, 0, width, height);
}

Result garden_window_create(GLFWmonitor *monitor) {
  Result init_res = tryinit_glfw();
  if (result_is_error(&init_res)) {
    return init_res;
  }
  GardenWindow *window = malloc(sizeof(GardenWindow));
  if (window == NULL) {
    return result_error(error_create("Failed to allocate memory for window"));
  }

  if (monitor == NULL) {
    free(window);
    return result_error(error_create("Monitor is NULL"));
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

  glfwMakeContextCurrent(window->window);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    garden_window_destroy(window);
    return result_error(error_create("Failed to initialize GLEW"));
  }

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
