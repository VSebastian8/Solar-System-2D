#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

float sunX = 0.0f, sunY = 0.0f;
glm::mat4 sunPositionMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(sunX, sunY, 1.0));
GLuint sun_texture;

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

void drawSun(glm::mat4& resizeMatrix, GLuint& myMatrixLocation, GLuint& codColLocation, GLuint& ProgramId){
    glUniform1i(codColLocation, 2);
    //	Transmiterea variabilei uniforme pentru texturare spre shaderul de fragmente;
    glBindTexture(GL_TEXTURE_2D, sun_texture);
    glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);

    glm::mat4 myMatrix = resizeMatrix * sunPositionMatrix;
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
    glDrawArrays(GL_POLYGON, 9, 8);
}