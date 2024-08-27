#pragma once

#include "buffer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

typedef struct GardenMesh GardenMesh;

struct GardenMesh {
  GardenBuffer *vertex_buffer;
  GardenBuffer *index_buffer;
  uint index_count;
  GLenum mode;
};

GardenMesh *garden_mesh_create(GardenBuffer *vertex_buffer,
                         GardenBuffer *index_buffer, uint index_count,
                         GLenum mode);

void garden_mesh_draw(GardenMesh *mesh);

void garden_mesh_destroy(GardenMesh *mesh);
