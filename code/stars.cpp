#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>
#include <random>
#include <iostream>

std::vector<glm::mat4> stars;
float detail = 1000;
std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> dist(0, detail);

void createStars(int n){
    for(int i = 0; i < n; i++){
        float x =  dist(rng) * 2 / detail - 1.0f, y =  dist(rng) * 2 / detail - 1.0f;
        std::cout << x << " " << y << "\n";
        stars.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0)));
    }
}

void drawStars(GLuint& myMatrixLocation, GLuint& codColLocation){
  int codCol = 1;
  glUniform1i(codColLocation, codCol);
  for(auto& star: stars){
        glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &star[0][0]);
        glDrawArrays(GL_POINTS, 0, 1);
  }
}