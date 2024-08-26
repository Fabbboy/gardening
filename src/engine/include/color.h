#pragma once

#include <GL/glew.h>
typedef struct GardenColor GardenColor;
struct GardenColor {
  GLfloat r;
  GLfloat g;
  GLfloat b;
  GLfloat a;
};

GardenColor garden_color_create(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
