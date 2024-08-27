#include "engine/buffer/include/buffer.h"
#include "engine/buffer/include/layout.h"
#include "engine/buffer/include/mesh.h"
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
  GLuint indecies[] = {0, 1, 2};

  GardenAttribute attributes[] = {
      garden_attribute_create(/*size=*/3, /*type=*/GARDEN_ATTRIBUTE_FLOAT,
                              /*normalized=*/GL_FALSE)};

  GardenLayout layout = garden_layout_create(attributes, 1);

  Result res_vertex_buffer =
      garden_buffer_create(layout, vertices, sizeof(vertices));

  if (result_is_error(&res_vertex_buffer)) {
    Error *error = result_unwrap_error(&res_vertex_buffer);
    printf("Failed to create vertex buffer: %s\n", error->message);
    error_destroy(error);
    return 1;
  }

  GardenBuffer *vertex_buffer =
      (GardenBuffer *)result_unwrap(&res_vertex_buffer);

  Result res_index_buffer =
      garden_index_buffer_create(layout, indecies, sizeof(indecies));

  if (result_is_error(&res_index_buffer)) {
    Error *error = result_unwrap_error(&res_index_buffer);
    printf("Failed to create index buffer: %s\n", error->message);
    error_destroy(error);
    return 1;
  }

  GardenIndexBuffer *index_buffer =
      (GardenIndexBuffer *)result_unwrap(&res_index_buffer);

  Result res_mesh =
      garden_mesh_create(vertex_buffer, index_buffer,
                         sizeof(indecies) / sizeof(GLuint), GL_TRIANGLES);

  if (result_is_error(&res_mesh)) {
    Error *error = result_unwrap_error(&res_mesh);
    printf("Failed to create mesh: %s\n", error->message);
    error_destroy(error);
    return 1;
  }

  GardenMesh *mesh = (GardenMesh *)result_unwrap(&res_mesh);

  while (!glfwWindowShouldClose(window->window)) {
    glfwPollEvents();

    garden_shader_use(garden_shader);

    garden_mesh_draw(mesh);

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
