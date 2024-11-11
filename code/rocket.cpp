#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

struct Rocket{
    float target_x, target_y;
    float current_x, current_y;
    float angle;
    glm::mat4 translationMatrix, rotationMatrix;
    Rocket(): target_x(0.0f), target_y(0.0f), current_x(-1.0f), current_y(0.0f), angle(0.0f), 
        translationMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 1.0))),
        rotationMatrix(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0))){}
} rocket;
  
void updateTarget(int x, int y, int w, int h){
    rocket.target_x = float(x) * 2.0f / w - 1.0f;
    rocket.target_y = float(h - y) * 2.0f / h - 1.0f;
}

void MoveRocket(double delta_time){
    rocket.translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(rocket.target_x, rocket.target_y, 1.0));
}

void drawRocket(GLuint& myMatrixLocation, GLuint& codColLocation){
    // std::cout << "rocket go to " << rocket.target_x << "  "  << rocket.target_y << "\n";
    glUniform1i(codColLocation, 2);

    glm::mat4 myMatrix = rocket.translationMatrix * rocket.rotationMatrix;
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
    glDrawArrays(GL_POLYGON, 17, 4);

}
