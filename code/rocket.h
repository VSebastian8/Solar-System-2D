#ifndef ROCKET_H
#define ROCKET_H

#include <GL/freeglut.h>
#include "glm/glm.hpp"

extern GLuint rocket_texture;
void updateTarget(int x, int y, int w, int h);
void drawRocket(GLuint& myMatrixLocation, GLuint& codColLocation, GLuint ProgramId);
void MoveRocket(double delta_time);

#endif