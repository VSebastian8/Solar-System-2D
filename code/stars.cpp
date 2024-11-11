#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>
#include <random>
#include <iostream>

float detail = 1000;
std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> dist(0, detail);
std::uniform_int_distribution<std::mt19937::result_type> length(500, 1000);
float star_glow_speed = 0.001f;

struct Star{
  glm::mat4 position;
  float opacity; 
  int glow_length;
  int current_glow;

  // Constructor cu parametrii
  Star(float x, float y, float opacity, int glow_length, int current_glow): 
      opacity(opacity), glow_length(glow_length), current_glow(current_glow),
      position(glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0))){}
  // Constructori fara parametrii => valori random
  Star(){
      float x =  dist(rng) * 2 / detail - 1.0f, y =  dist(rng) * 2 / detail - 1.0f;
      position = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0));
      opacity = dist(rng) / detail; // valoarea de start a opacitatii
      glow_length = length(rng); // cat dureaza un ciclu complet de aprindere-stingere a stelei
      current_glow = int(length(rng)) % glow_length;
  }
};

std::vector<Star> stars;

void createStars(int n){
    for(int i = 0; i < n; i++){
        stars.push_back(Star());
    }
}

void drawStars(GLuint& myMatrixLocation, GLuint& codColLocation, GLuint& starOpacLocation){
  int codCol = 1;
  glUniform1i(codColLocation, codCol);
  for(auto& star: stars){
        glUniform1f(starOpacLocation, star.opacity);
        glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &star.position[0][0]);
        glDrawArrays(GL_POINTS, 0, 1);
  }
}

void GlowStars(){
  for(auto& star: stars){
    if(star.current_glow >= star.glow_length * 2)
      star.current_glow = - star.glow_length * 2;
    if((star.current_glow > - star.glow_length * 2) && (star.current_glow < - star.glow_length)){
      star.opacity = std::max(0.0f, star.opacity - star_glow_speed);
    }
    if ((star.current_glow > 0) && (star.current_glow < star.glow_length)){
      star.opacity = std::min(1.0f, star.opacity + star_glow_speed);
    }
    star.current_glow++;
  }
}
