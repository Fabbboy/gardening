#include "include/shader.h"
#include "utils/include/error.h"
#include "utils/include/result.h"
#include <stdio.h>
#include <stdlib.h>

static Result read_shader_file(const char *path) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    return result_error(error_create("Failed to open shader file"));
  }

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = malloc(size + 1);
  if (buffer == NULL) {
    fclose(file);
    return result_error(error_create("Failed to allocate memory for shader"));
  }

  size_t read = fread(buffer, 1, size, file);
  if (read != size) {
    fclose(file);
    free(buffer);
    return result_error(error_create("Failed to read shader file"));
  }

  buffer[size] = '\0';
  fclose(file);
  return result_ok(buffer);
}

static Result compile_shader(const char *source, GLenum type) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetShaderInfoLog(shader, 512, NULL, info_log);
    return result_error(error_create(info_log));
  }

  Result res = {.is_ok = true, .uidata = shader};
  return res;
}

static Result combine_shader_program(GLuint vertex_shader,
                                     GLuint fragment_shader) {
  GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  GLint success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetProgramInfoLog(program, 512, NULL, info_log);
    return result_error(error_create(info_log));
  }

  Result res = {.is_ok = true, .uidata = program};
  return res;
}

Result garden_shader_create(const char *vertex_shader_path,
                            const char *fragment_shader_path) {
  Result vertex_res = read_shader_file(vertex_shader_path);
  if (result_is_error(&vertex_res)) {
    return vertex_res;
  }
  const char *vertex_shader_source = (const char *)result_unwrap(&vertex_res);

  Result fragment_res = read_shader_file(fragment_shader_path);
  if (result_is_error(&fragment_res)) {
    free((void *)vertex_shader_source);
    return fragment_res;
  }
  const char *fragment_shader_source =
      (const char *)result_unwrap(&fragment_res);

  Result vertex_compiled =
      compile_shader(vertex_shader_source, GL_VERTEX_SHADER);
  free((void *)vertex_shader_source);
  if (result_is_error(&vertex_compiled)) {
    free((void *)vertex_shader_source);
    free((void *)fragment_shader_source);
    return vertex_compiled;
  }
  GLuint vertex_shader = vertex_compiled.uidata;

  Result fragment_compiled =
      compile_shader(fragment_shader_source, GL_FRAGMENT_SHADER);
  free((void *)fragment_shader_source);
  if (result_is_error(&fragment_compiled)) {
    glDeleteShader(vertex_shader);
    return fragment_compiled;
  };
  GLuint fragment_shader = fragment_compiled.uidata;

  Result program_res = combine_shader_program(vertex_shader, fragment_shader);
  if (result_is_error(&program_res)) {
    free((void *)vertex_shader_source);
    free((void *)fragment_shader_source);
    return program_res;
  }

  GardenShader *shader = malloc(sizeof(GardenShader));
  shader->programId = program_res.uidata;

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return result_ok(shader);
}
Result garden_shader_create_from_source(const char *vertex_shader_source,
                                        const char *fragment_shader_source) {
  Result vertex_compiled =
      compile_shader(vertex_shader_source, GL_VERTEX_SHADER);

  if (result_is_error(&vertex_compiled)) {
    return vertex_compiled;
  };
  GLuint vertex_shader = vertex_compiled.uidata;

  Result fragment_compiled =
      compile_shader(fragment_shader_source, GL_FRAGMENT_SHADER);
  if (result_is_error(&fragment_compiled)) {
    glDeleteShader(vertex_shader);
    return fragment_compiled;
  };

  GLuint fragment_shader = fragment_compiled.uidata;

  Result program_res = combine_shader_program(vertex_shader, fragment_shader);
  if (result_is_error(&program_res)) {
    return program_res;
  }

  GardenShader *shader = malloc(sizeof(GardenShader));
  shader->programId = program_res.uidata;

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return result_ok(shader);
}
void garden_shader_use(GardenShader *shader) {
  glUseProgram(shader->programId);
};
void garden_shader_destroy(GardenShader *shader) {
  glDeleteProgram(shader->programId);
  free(shader);
};
