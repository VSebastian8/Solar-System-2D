#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <cmath>
#include <iostream>

GLuint rocket_texture;

struct Rocket{
    float target_x, target_y;
    float current_x, current_y;
    float angle, speed;
    glm::mat4 translationMatrix, rotationMatrix;
    Rocket(): target_x(0.0f), target_y(0.0f), current_x(-1.0f), current_y(0.0f), angle(0.0f), speed(10.0f), 
        translationMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 1.0))),
        rotationMatrix(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0))){}
} rocket;
  
float PI_ = 3.141592;

void updateTarget(int x, int y, int w, int h){
    rocket.target_x = float(x) * 2.0f / w - 1.0f;
    rocket.target_y = float(h - y) * 2.0f / h - 1.0f;
}

void MoveRocket(double delta_time){
    rocket.angle = atan2(rocket.target_y - rocket.current_y, rocket.target_x - rocket.current_x);
    rocket.angle += 3 * PI_ / 2.0f;
 
    if(abs(rocket.target_x - rocket.current_x) > 0.05f)
        rocket.current_x += cos(rocket.angle + PI_ / 2.0f) * rocket.speed * delta_time;
    if(abs(rocket.target_y - rocket.current_y) > 0.05f)
        rocket.current_y += sin(rocket.angle + PI_ / 2.0f) * rocket.speed * delta_time;

    rocket.rotationMatrix = glm::rotate(glm::mat4(1.0f), rocket.angle, glm::vec3(0.0, 0.0, 1.0));
    rocket.translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(rocket.current_x, rocket.current_y, 1.0));
}

void drawRocket(GLuint& myMatrixLocation, GLuint& codColLocation, GLuint ProgramId){
    // std::cout << "rocket go to " << rocket.target_x << "  "  << rocket.target_y << "\n";
    glUniform1i(codColLocation, 2);
    glBindTexture(GL_TEXTURE_2D, rocket_texture);
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);

    glm::mat4 myMatrix = rocket.translationMatrix * rocket.rotationMatrix;
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
    glDrawArrays(GL_POLYGON, 17, 4);

}
