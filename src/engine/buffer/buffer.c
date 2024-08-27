#include "include/buffer.h"
#include "utils/include/error.h"
#include "utils/include/result.h"

Result garden_buffer_create_dyn(GardenLayout layout, size_t size) {
  GardenBuffer *buffer = malloc(sizeof(GardenBuffer));
  if (!buffer) {
    return result_error(
        error_create("Failed to allocate memory for GardenBuffer"));
  }

  buffer->layout = layout;
  glCreateBuffers(1, &buffer->bufferId);
  glNamedBufferData(buffer->bufferId, size, NULL, GL_DYNAMIC_DRAW);
  if (glGetError() != GL_NO_ERROR) {
    return result_error(error_create("Failed to create buffer")); // TODO format
  }

  return result_ok(buffer);
};
Result garden_buffer_create(GardenLayout layout, float *data, size_t size) {
  GardenBuffer *buffer = malloc(sizeof(GardenBuffer));
  if (!buffer) {
    return result_error(
        error_create("Failed to allocate memory for GardenBuffer"));
  }
  buffer->layout = layout;
  glCreateBuffers(1, &buffer->bufferId);
  glNamedBufferData(buffer->bufferId, size, data, GL_STATIC_DRAW);
  if (glGetError() != GL_NO_ERROR) {
    return result_error(error_create("Failed to create buffer")); // TODO format
  }

  return result_ok(buffer);
};

void garden_buffer_bind(GardenBuffer *buffer) {
  glBindBuffer(GL_ARRAY_BUFFER, buffer->bufferId);
}

void garden_buffer_unbind(GardenBuffer *buffer) {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
};

void garden_buffer_destroy(GardenBuffer *buffer) {
  glDeleteBuffers(1, &buffer->bufferId);
  free(buffer);
};
void garden_buffer_set(GardenBuffer *buffer, size_t size, void *data) {
  glBindBuffer(GL_ARRAY_BUFFER, buffer->bufferId);
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
};
GardenLayout garden_buffer_get_layout(GardenBuffer *buffer) {
  return buffer->layout;
};

Result garden_index_buffer_create(GardenLayout layout, uint *data,
                                  size_t size) {
  GardenIndexBuffer *buffer = malloc(sizeof(GardenIndexBuffer));
  if (!buffer) {
    return result_error(
        error_create("Failed to allocate memory for GardenIndexBuffer"));
  }
  buffer->layout = layout;
  glGenBuffers(1, &buffer->bufferId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->bufferId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  buffer->count = size / sizeof(uint);
  if (glGetError() != GL_NO_ERROR) {
    return result_error(error_create("Failed to create buffer")); // TODO format
  }

  return result_ok(buffer);
}

void garden_index_buffer_bind(GardenIndexBuffer *buffer) {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->bufferId);
};
void garden_index_buffer_unbind(GardenIndexBuffer *buffer) {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
};

void garden_index_buffer_destroy(GardenIndexBuffer *buffer) {
  glDeleteBuffers(1, &buffer->bufferId);
  free(buffer);
};
void garden_index_buffer_set(GardenIndexBuffer *buffer, size_t size,
                             void *data) {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->bufferId);
};
uint garden_index_buffer_get_count(GardenIndexBuffer *buffer) {
  return buffer->count;
};