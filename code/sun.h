#ifndef SUN_H
#define SUN_H

#include <GL/freeglut.h>
#include "glm/glm.hpp"

extern glm::mat4 sunPositionMatrix;
extern GLuint sun_texture;
void MoveSun(int key, int xx, int y);
void drawSun(glm::mat4& resizeMatrix, GLuint& myMatrixLocation, GLuint& codColLocation, GLuint& ProgramId);

#endif