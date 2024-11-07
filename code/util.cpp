#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

//	Dimensiunile ferestrei de afisare;
GLfloat winWidth = 1000, winHeight = 1000;
//	Variabile pentru proiectia ortogonala;
float xMin = -500, xMax = 500, yMin = -500, yMax = 500;
// Coordonate ([xMin - xMax], [yMin - yMax]) -> ([-1.0, 1.0], [-1.0, 1.0])
glm::mat4 resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax), identityMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 1.0));

void drawOptions(){
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glEnable(GL_POINT_SMOOTH);
  glPointSize(15.0);
  glLineWidth(2.0);
  glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_FILL);
}

void drawBackground(GLuint& myMatrixLocation, GLuint& codColLocation){
  int codCol = 0;
  glUniform1i(codColLocation, codCol);
  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &identityMatrix[0][0]);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void drawAxes(GLuint& codColLocation){
  int codCol = 1;
  glUniform1i(codColLocation, codCol);
  glDrawArrays(GL_LINES, 4, 4);
}

void createWindow(){
  glutInitWindowSize(winWidth, winHeight);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Proiect 2D - Sistem Solar");
}

void Zoom(unsigned char key, int x, int y){
	switch (key){ 
        case '=':
            xMin *= 0.9;
            xMax *= 0.9;
            yMin *= 0.9;
            yMax *= 0.9;
            break;
	    case '-':
            xMin *= 1.1;
            xMax *= 1.1;
            yMin *= 1.1;
            yMax *= 1.1;
            break;
        case 'q':
	    	exit(0);
	}
   resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);
}