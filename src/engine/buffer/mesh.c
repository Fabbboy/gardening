#include "include/mesh.h"

GardenMesh *garden_mesh_create(GardenBuffer *vertex_buffer,
                               GardenBuffer *index_buffer, uint index_count,
                               GLenum mode) {
  GardenMesh *mesh = malloc(sizeof(GardenMesh));
  mesh->vertex_buffer = vertex_buffer;
  mesh->index_buffer = index_buffer;
  mesh->index_count = index_count;
  mesh->mode = mode;

  glGenVertexArrays(1, &mesh->vao);
  glBindVertexArray(mesh->vao);

  garden_buffer_apply_layout(vertex_buffer);

  if (index_buffer) {
    garden_buffer_bind(index_buffer);
  }

  glBindVertexArray(0);
  return mesh;
};

void garden_mesh_draw(GardenMesh *mesh) {
  garden_buffer_bind(mesh->vertex_buffer);
  garden_buffer_bind(mesh->index_buffer);
  glDrawElements(mesh->mode, mesh->index_count, GL_UNSIGNED_INT, 0);
  garden_buffer_unbind(mesh->vertex_buffer);
  garden_buffer_unbind(mesh->index_buffer);
};

void garden_mesh_destroy(GardenMesh *mesh) {
  garden_buffer_destroy(mesh->vertex_buffer);
  garden_buffer_destroy(mesh->index_buffer);
  free(mesh);
};
