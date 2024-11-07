#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

float sunX = 0.0f, sunY = 0.0f;
glm::mat4 sunPositionMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(sunX, sunY, 1.0));
int sun_color_code = 2;

void MoveSun(int key, int xx, int yy) {
	switch (key) {		
  	case GLUT_KEY_LEFT:
      sunX -= 10;
      break;
    case GLUT_KEY_RIGHT:
      sunX += 10;
      break;
    case GLUT_KEY_UP:
      sunY += 10;
      break;
    case GLUT_KEY_DOWN:
      sunY -= 10;
      break;
    default:
      return;
	}
  sunPositionMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(sunX, sunY, 1.0));
}

void drawSun(glm::mat4& resizeMatrix, GLuint& myMatrixLocation, GLuint& codColLocation){
    glUniform1i(codColLocation, sun_color_code);

    glm::mat4 myMatrix = resizeMatrix * sunPositionMatrix;
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
    glDrawArrays(GL_POLYGON, 9, 8);
}