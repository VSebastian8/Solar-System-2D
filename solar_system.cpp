//
// =========================
// | Grafica pe calculator |
// =========================
// 	    | Proiect 2D |
// =========================
//
//	Sistem Solar

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

// Bibloteci utilizate pentru transformari grafice;
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "shaders/loadShaders.h"

#include <vector>
#include <iostream>

// Fisierele in care avem codul pentru soare si planete
#include "sun.h"
#include "planets.h"

//  Identificatorii obiectelor de tip OpenGL;
GLuint VaoId, VboId, ColorBufferId, ProgramId, myMatrixLocation,
    matrRotlLocation, codColLocation;
//	Dimensiunile ferestrei de afisare;
GLfloat winWidth = 1000, winHeight = 1000;
//	Variabile catre matricile de transformare;
glm::mat4 myMatrix, resizeMatrix;

//	Variabila ce determina schimbarea culorii pixelilor in shader;
int codCol;
//	Variabile pentru proiectia ortogonala;
float xMin = -500, xMax = 500, yMin = -500, yMax = 500;

void CreateShaders(void) {
  ProgramId =
      LoadShaders("shaders/solar_system_shader.vert", "shaders/solar_system_shader.frag");
  glUseProgram(ProgramId);
}

void CreateVBO(void) {
  //  Coordonatele varfurilor;
  GLfloat Vertices[] = {
      // Cele 4 puncte din colturi;
      xMin, yMin, 0.0f, 1.0f, 
      xMax, yMin, 0.0f, 1.0f, 
      xMax, yMax, 0.0f, 1.0f,
      xMin, yMax, 0.0f, 1.0f,
      // Varfuri pentru axe;
      xMin, 0.0f, 0.0f, 1.0f, 
      xMax, 0.0f, 0.0f, 1.0f, 
      0.0f, yMin, 0.0f, 1.0f,
      0.0f, yMax, 0.0f, 1.0f,
      // Varfuri Octagon
      50.0f, 0.0f, 0.0f, 1.0f,
      35.0f, 35.0f, 0.0f, 1.0f,
      0.0f, 50.0f, 0.0f, 1.0f,
      -35.0f, 35.0f, 0.0f, 1.0f,
      -50.0f, 0.0f, 0.0f, 1.0f,
      -35.0f, -35.0f, 0.0f, 1.0f,
      0.0f, -50.0f, 0.0f, 1.0f,
      35.0f, -35.0f, 0.0f, 1.0f,
  };

  //	Culori
  GLfloat Colors[] = {
      // Culori Gradient
      0.0f, 0.0f, 0.1f, 1.0f,
      0.1f, 0.0f, 0.05f, 1.0f,
      0.0f, 0.0f, 0.1f, 1.0f,
      0.1f, 0.0f, 0.05f, 1.0f,
  };

  glGenVertexArrays(1, &VaoId);
  glBindVertexArray(VaoId);

  // Buffer pentru VARFURI;
  glGenBuffers(1, &VboId);
  glBindBuffer(GL_ARRAY_BUFFER, VboId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

  glGenBuffers(1, &ColorBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

//  Elimina obiectele de tip shader dupa rulare;
void DestroyShaders(void) { glDeleteProgram(ProgramId); }

//  Eliminarea obiectelor de tip VBO dupa rulare;
void DestroyVBO(void) {
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &ColorBufferId);
  glDeleteBuffers(1, &VboId);

  glBindVertexArray(0);
  glDeleteVertexArrays(1, &VaoId);
}

//  Functia de eliberare a resurselor alocate de program;
void Cleanup(void) {
  DestroyShaders();
  DestroyVBO();
}

//  Setarea parametrilor necesari pentru fereastra de vizualizare;
void Initialize(void) {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  CreateVBO();
  CreateShaders();

  codColLocation = glGetUniformLocation(ProgramId, "codCol");
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");

  // Coordonate ([xMin - xMax], [yMin - yMax]) -> ([-1.0, 1.0], [-1.0, 1.0])
  resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);
}

//  Functia de desenarea a graficii pe ecran;
void RenderFunction(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glPointSize(15.0);
  glEnable(GL_POINT_SMOOTH);

  myMatrix = resizeMatrix;
  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
  codCol = 0;
  glUniform1i(codColLocation, codCol);

  // Gradient pentru fundal
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

  // Desenarea axelor;
  codCol = 1;
  glUniform1i(codColLocation, codCol);
  glLineWidth(2.0);
  // glDrawArrays(GL_LINES, 4, 4);

  glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_FILL);

  // Desenarea soarelui
  drawSun(resizeMatrix, myMatrixLocation, codColLocation);

  // Desenarea Planetelor
  drawPlanets(resizeMatrix, sunPositionMatrix, myMatrixLocation, codColLocation);
 
  //  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
  glFlush();
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char *argv[]) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(winWidth, winHeight);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Proiect 2D - Sistem Solar");
  glewInit();

  Initialize();

  glutDisplayFunc(RenderFunction);
  glutCloseFunc(Cleanup);
  glutIdleFunc(RotatePlanets);
  glutSpecialFunc(MoveSun);
  
  glutMainLoop();

  return 0;
}
