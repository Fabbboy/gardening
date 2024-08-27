#include "include/layout.h"
#include <stdbool.h>

GardenAttribute garden_attribute_create(GLint size, GardenAttributeType type,
                                        bool normalized) {
  GardenAttribute attribute;
  attribute.size = size;
  attribute.type = type;
  attribute.normalized = normalized;
  attribute.offset = 0;
  return attribute;
};

GardenLayout garden_layout_create(GardenAttribute *attributes,
                                  size_t attribute_count) {
  GardenLayout layout;
  layout.attributes = attributes;
  layout.attribute_count = attribute_count;

  size_t stride = 0;
  size_t offset = 0;

  for (size_t i = 0; i < attribute_count; i++) {
    GardenAttribute attribute = attributes[i];
    attribute.offset = offset;
    offset += attribute.size * sizeof(attribute.type);
    stride += attribute.size * sizeof(attribute.type);
  }

  layout.stride = stride;
  return layout;
};