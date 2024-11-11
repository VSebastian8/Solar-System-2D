#ifndef PLANETS_H
#define PLANETS_H

#include <GL/freeglut.h>
#include "glm/glm.hpp"
#include <vector>

void LoadPlanetTextures(std::vector<GLuint> planet_textures);
void RotatePlanets(double delta_time);
void drawPlanets(glm::mat4& resizeMatrix, glm::mat4& sunPositionMatrix, GLuint& myMatrixLocation, GLuint& codColLocation, GLuint& ProgramId);

#endif