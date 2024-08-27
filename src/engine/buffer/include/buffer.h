#pragma once

#include "layout.h"
#include "utils/include/result.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

typedef struct GardenBuffer GardenBuffer;

struct GardenBuffer {
  GardenLayout layout;
  uint bufferId;
};

Result garden_buffer_create_dyn(GardenLayout layout, size_t size);
Result garden_buffer_create(GardenLayout layout, float *data, size_t size);

void garden_buffer_bind(GardenBuffer *buffer);
void garden_buffer_unbind(GardenBuffer *buffer);

void garden_buffer_destroy(GardenBuffer *buffer);
void garden_buffer_set(GardenBuffer *buffer, size_t size, void *data);
GardenLayout garden_buffer_get_layout(GardenBuffer *buffer);

typedef struct GardenIndexBuffer GardenIndexBuffer;

struct GardenIndexBuffer {
  GardenLayout layout;
  uint bufferId;
  uint count;
};

Result garden_index_buffer_create(GardenLayout layout, uint *data,
                                              size_t size);

void garden_index_buffer_bind(GardenIndexBuffer *buffer);
void garden_index_buffer_unbind(GardenIndexBuffer *buffer);

void garden_index_buffer_destroy(GardenIndexBuffer *buffer);
void garden_index_buffer_set(GardenIndexBuffer *buffer, size_t size,
                             void *data);
uint garden_index_buffer_get_count(GardenIndexBuffer *buffer);