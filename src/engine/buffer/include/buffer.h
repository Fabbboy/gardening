#pragma once

#include "layout.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

typedef struct GardenBuffer GardenBuffer;

struct GardenBuffer {
  GardenLayout layout;
  uint bufferId;
};

GardenBuffer *garden_buffer_create(GardenLayout layout, uint bufferId);
void garden_buffer_bind(GardenBuffer *buffer);
void garden_buffer_unbind(GardenBuffer *buffer);
void garden_buffer_set_data(GardenBuffer *buffer, size_t size, void *data);
GardenLayout garden_buffer_get_layout(GardenBuffer *buffer);
void garden_buffer_destroy(GardenBuffer *buffer);
