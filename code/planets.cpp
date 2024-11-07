#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>
#include <iostream> 
#include <chrono>

float PI = 3.141592;
double delta_time, ms = 60000.0f;
auto previous_time = std::chrono::steady_clock::now(), current_time = std::chrono::steady_clock::now();

struct Planet{
  float size, radius, angle, speed;
  int color_code;
  glm::mat4 scaleTransform, translateTransform, rotationTransform;

  Planet(float size, float radius, float angle, float speed, int color_code): 
          size(size), radius(radius), angle(angle), speed(speed), color_code(color_code){
    scaleTransform = glm::scale(glm::mat4(1.0f), glm::vec3(size, size, 0.0));
    translateTransform = glm::translate(glm::mat4(1.0f), glm::vec3(radius, 0, 0.0));
    rotationTransform = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));
  }
  void rotate_planet(float dt){
    angle += (PI * 2.0f * speed) * dt / ms;
    if (angle > PI * 2)
      angle -= PI * 2;
    rotationTransform = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));
  }
};
// Speed expressed in rotations per minute 
std::vector<Planet> planets = {
  Planet(0.05, 100, PI/2, 30, 3), 
  Planet(0.1, 130, PI/6, 20, 4), 
  Planet(0.2, 200, -PI, 10, 5),
  Planet(0.18, 230, -PI/8, 8, 6),
  Planet(0.7, 320, PI, 3, 7),
  Planet(0.5, 400, PI*1.8f, 4, 8),
  Planet(0.18, 450, -PI/3, 13, 9),
  Planet(0.18, 472, PI/1.3f, 15, 10),
};

void calculate_delta_time(){
  current_time = std::chrono::steady_clock::now(); 
  delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - previous_time).count();
  if (delta_time != 0) 
    previous_time = current_time;
}

void RotatePlanets() {
  calculate_delta_time();
  if (delta_time == 0)
    return;

  for (auto& planet: planets) {
    planet.rotate_planet(delta_time);
  }
  glutPostRedisplay();
}

void drawPlanets(glm::mat4& resizeMatrix, glm::mat4& sunPositionMatrix, GLuint& myMatrixLocation, GLuint& codColLocation) {
    for(auto& planet: planets){
        glUniform1i(codColLocation, planet.color_code);
        glm::mat4 myMatrix = resizeMatrix * sunPositionMatrix * planet.rotationTransform * planet.translateTransform * planet.scaleTransform;
        glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
        
        glDrawArrays(GL_POLYGON, 9, 8);
  }
}