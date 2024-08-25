#pragma once

#include "utils/include/result.h"

#include <GLFW/glfw3.h>
typedef struct GardenWindow GardenWindow;
struct GardenWindow {
  int width;
  int height;
  const char *title;
  GLFWwindow *window;
};

Result garden_window_create(GLFWmonitor *monitor);

void garden_window_destroy(GardenWindow *window);