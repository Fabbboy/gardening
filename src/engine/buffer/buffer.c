#include "include/buffer.h"

GardenBuffer *garden_buffer_create(GardenLayout layout, uint bufferId) {
  GardenBuffer *buffer = malloc(sizeof(GardenBuffer));
  buffer->layout = layout;
  buffer->bufferId = bufferId;
  return buffer;
};
void garden_buffer_bind(GardenBuffer *buffer) {
  glBindBuffer(GL_ARRAY_BUFFER, buffer->bufferId);
};
void garden_buffer_unbind(GardenBuffer *buffer) {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
};
void garden_buffer_set_data(GardenBuffer *buffer, size_t size, void *data) {
  garden_buffer_bind(buffer);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  garden_buffer_unbind(buffer);
};
GardenLayout garden_buffer_get_layout(GardenBuffer *buffer) {
  return buffer->layout;
};
void garden_buffer_destroy(GardenBuffer *buffer) {
  glDeleteBuffers(1, &buffer->bufferId);
  free(buffer);
};
