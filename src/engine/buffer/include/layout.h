#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

typedef enum GardenAttributeType {
  GARDEN_ATTRIBUTE_FLOAT,
  GARDEN_ATTRIBUTE_INT,
} GardenAttributeType;

static inline GLenum garden_attribute_type_to_gl(GardenAttributeType type) {
  switch (type) {
  case GARDEN_ATTRIBUTE_FLOAT:
    return GL_FLOAT;
  case GARDEN_ATTRIBUTE_INT:
    return GL_INT;
  default:
    return GL_FLOAT;
  }
}

typedef struct GardenAttribute GardenAttribute;

struct GardenAttribute {
  GLint size;
  GardenAttributeType type;
  GLboolean normalized;
  size_t offset;
};

GardenAttribute garden_attribute_create(GLint size, GardenAttributeType type,
                                        bool normalized);

typedef struct GardenLayout GardenLayout;

struct GardenLayout {
  GardenAttribute *attributes;
  size_t attribute_count;
  size_t stride;
};

GardenLayout garden_layout_create(GardenAttribute *attributes,
                                  size_t attribute_count);
