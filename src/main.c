#include "engine/include/window.h"
#include "engine/rendering/include/renderer.h"
#include "engine/rendering/include/shader.h"
#include "utils/include/result.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

int main() {
  if (!glfwInit()) {
    printf("Failed to initialize GLFW\n");
    return 1;
  }

  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  if (monitor == NULL) {
    printf("Failed to get primary monitor\n");
    glfwTerminate();
    return 1;
  }

  Result win_res = garden_window_create(monitor);
  if (result_is_error(&win_res)) {
    Error *error = result_unwrap_error(&win_res);
    printf("Failed to create window: %s\n", error->message);
    error_destroy(error);
    return 1;
  }
  GardenWindow *window = (GardenWindow *)result_unwrap(&win_res);
  GardenRenderer *renderer = garden_renderer_create(
      window, garden_color_create(0.2f, 0.3f, 0.3f, 1.0f), GL_COLOR_BUFFER_BIT);

  Result shader = garden_shader_create("../res/shaders/basic.vert",
                                       "../res/shaders/basic.frag");
  if (result_is_error(&shader)) {
    Error *error = result_unwrap_error(&shader);
    printf("Failed to create shader: %s\n", error->message);
    error_destroy(error);
    return 1;
  }
  GardenShader *garden_shader = (GardenShader *)result_unwrap(&shader);

  GLfloat vertices[] = {
      -0.5f, -0.5f, 0.0f, /* Lower left */ 0.5f, -0.5f, 0.0f, /* Lower right */
      0.0f,  0.5f,  0.0f                                      /* Upper center */
  };

  GLuint vao, vbo;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (GLvoid *)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  printf("Program ID: %u, VAO: %u, VBO: %u\n", garden_shader->programId, vao,
         vbo);

  while (!glfwWindowShouldClose(window->window)) {
    glfwPollEvents();

    garden_shader_use(garden_shader);

    // Render the scene
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
      printf("OpenGL error: %d\n", error);
    }

    renderer->swap(renderer);
  }

  garden_shader_destroy(garden_shader);
  garden_renderer_destroy(renderer);
  garden_window_destroy(window);
  return 0;
}
