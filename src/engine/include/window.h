#pragma once

#include "utils/include/result.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct GardenWindowData GardenWindowData;
struct GardenWindowData {
  int width;
  int height;
};

typedef struct GardenWindow GardenWindow;
struct GardenWindow {
  GardenWindowData data;
  const char *title;
  GLFWwindow *window;
};

Result garden_window_create(GLFWmonitor *monitor);
void garden_window_callbacks(GardenWindow *window);
static inline GLFWwindow *garden_window_get_window(GardenWindow *window) {
  return window->window;
};
void garden_window_destroy(GardenWindow *window);