#pragma once

#include "utils/include/result.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct GardenShader GardenShader;
struct GardenShader {
  GLuint programId;
};

Result garden_shader_create(const char *vertex_shader_path,
                            const char *fragment_shader_path);
Result garden_shader_create_from_source(const char *vertex_shader_source,
                                        const char *fragment_shader_source);
void garden_shader_use(GardenShader *shader);
void garden_shader_destroy(GardenShader *shader);
