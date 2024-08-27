#include "include/mesh.h"
#include "engine/buffer/include/buffer.h"
#include "engine/buffer/include/layout.h"

GardenMesh *garden_mesh_create(GardenBuffer *vertex_buffer,
                               GardenIndexBuffer *index_buffer,
                               uint index_count, GLenum mode) {
  GardenMesh *mesh = malloc(sizeof(GardenMesh));
  if (!mesh) {
    printf("Failed to allocate memory for GardenMesh\n");
    return NULL;
  }
  mesh->vertex_buffer = vertex_buffer;
  mesh->index_buffer = index_buffer;
  mesh->mode = mode;

  glGenVertexArrays(1, &mesh->vao);
  glBindVertexArray(mesh->vao);

  garden_buffer_bind(vertex_buffer);
  garden_index_buffer_bind(index_buffer);

  GardenLayout layout = garden_buffer_get_layout(vertex_buffer);
  for (size_t i = 0; i < layout.attribute_count; i++) {
    GardenAttribute attribute = layout.attributes[i];
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(
        i, attribute.size, garden_attribute_type_to_gl(attribute.type),
        attribute.normalized, layout.stride, (void *)attribute.offset);
  }

  glBindVertexArray(0); // Unbind the VAO to prevent accidental changes
  return mesh;
}

void garden_mesh_draw(GardenMesh *mesh) {
  glBindVertexArray(mesh->vao);
  garden_index_buffer_bind(mesh->index_buffer);
  glDrawElements(mesh->mode, mesh->index_buffer->count, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  garden_index_buffer_unbind(mesh->index_buffer);
};

void garden_mesh_destroy(GardenMesh *mesh) {
  garden_buffer_destroy(mesh->vertex_buffer);
  garden_index_buffer_destroy(mesh->index_buffer);
  free(mesh);
};
