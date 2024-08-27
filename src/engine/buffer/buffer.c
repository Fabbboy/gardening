#include "include/buffer.h"

void garden_buffer_apply_layout(GardenBuffer *buffer) {
  garden_buffer_bind(buffer);

  const GardenLayout *layout = &buffer->layout;
  size_t offset = 0;

  for (size_t i = 0; i < layout->attribute_count; i++) {
    GardenAttribute attribute = layout->attributes[i];
    GLenum type = garden_attribute_type_to_gl(attribute.type);

    glVertexAttribPointer(i, attribute.size, type, attribute.normalized,
                          layout->stride, (const void *)offset);
    glEnableVertexAttribArray(i);

    offset += attribute.size * garden_get_size_of_type(type);
  }

  garden_buffer_unbind(buffer);
}

GardenBuffer *garden_buffer_create_dyn(GardenLayout layout, size_t size) {
  GardenBuffer *buffer = malloc(sizeof(GardenBuffer));
  buffer->layout = layout;
  buffer->isIndex = false;
  glCreateBuffers(1, &buffer->bufferId);
  glNamedBufferData(buffer->bufferId, size, NULL, GL_DYNAMIC_DRAW);

  return buffer;
};
GardenBuffer *garden_buffer_create(GardenLayout layout, float *data,
                                   size_t size) {
  GardenBuffer *buffer = malloc(sizeof(GardenBuffer));
  buffer->layout = layout;
  buffer->isIndex = false;
  glCreateBuffers(1, &buffer->bufferId);
  glNamedBufferData(buffer->bufferId, size, data, GL_STATIC_DRAW);
  return buffer;
};

GardenBuffer *garden_buffer_create_index(GardenLayout layout, uint *data,
                                         size_t size) {
  GardenBuffer *buffer = malloc(sizeof(GardenBuffer));
  buffer->layout = layout;
  buffer->isIndex = true;
  glCreateBuffers(1, &buffer->bufferId);
  glNamedBufferData(buffer->bufferId, size, data, GL_STATIC_DRAW);
  return buffer;
};

void garden_buffer_bind(GardenBuffer *buffer) {
  if (buffer->isIndex) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->bufferId);
  } else {
    glBindBuffer(GL_ARRAY_BUFFER, buffer->bufferId);
  }
}

void garden_buffer_unbind(GardenBuffer *buffer) {
  if (buffer->isIndex) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  } else {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
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
