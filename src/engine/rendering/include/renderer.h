#pragma once

#include "engine/include/color.h"
#include "engine/include/window.h"

typedef struct GardenRenderer GardenRenderer;
struct GardenRenderer {
  GardenWindow *window; // win_ref
  GardenColor clear_color;
  GLbitfield clear_mask;

  void (*swap)(GardenRenderer *renderer);
};

GardenRenderer *garden_renderer_create(GardenWindow *window,
                                       GardenColor clear_color,
                                       GLbitfield clear_mask);
void garden_renderer_destroy(GardenRenderer *renderer);
