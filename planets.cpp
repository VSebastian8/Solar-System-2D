#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

float PI = 3.141592;

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
  void rotate_planet(){
    angle += speed;
    if (angle > PI * 2)
      angle -= PI * 2;
    rotationTransform = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));
  }
};

std::vector<Planet> planets = {
  Planet(0.05, 100, PI/2, 0.002, 3), 
  Planet(0.1, 130, PI/6, 0.001, 4), 
  Planet(0.2, 200, -PI, 0.0004, 5),
  Planet(0.18, 230, -PI/8, 0.001, 6),
  Planet(0.7, 320, PI, 0.0002, 7),
  Planet(0.5, 400, PI*1.8f, 0.0003, 8),
  Planet(0.18, 450, -PI/3, 0.0006, 9),
  Planet(0.18, 472, PI/1.3f, 0.0007, 10),
};

void RotatePlanets() {
  for (auto& planet: planets) {
    planet.rotate_planet();
  }
  glutPostRedisplay();
}

void drawPlanets(glm::mat4& resizeMatrix, glm::mat4& sunPositionMatrix, GLuint& myMatrixLocation, GLuint& codColLocation) {
    for(auto& planet: planets){
        glUniform1i(codColLocation, planet.color_code);
        glm::mat4 myMatrix = resizeMatrix * sunPositionMatrix * planet.rotationTransform * planet.translateTransform * planet.scaleTransform;
        glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
        
        glDrawArrays(GL_POLYGON, 8, 8);
  }
}