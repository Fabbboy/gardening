#include "include/color.h"

GardenColor garden_color_create(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
  GardenColor color;
  color.r = r;
  color.g = g;
  color.b = b;
  color.a = a;
  return color;
};
