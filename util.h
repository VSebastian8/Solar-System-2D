#ifndef UTIL_H
#define UTIL_H

#include <GL/freeglut.h>
#include "glm/glm.hpp"

extern glm::mat4 resizeMatrix;
extern float xMin, xMax, yMin, yMax;
void drawOptions();
void drawBackground(GLuint& myMatrixLocation, GLuint& codColLocation);
void drawAxes(GLuint& codColLocation);
void createWindow();
void Zoom(unsigned char key, int xx, int y);

#endif