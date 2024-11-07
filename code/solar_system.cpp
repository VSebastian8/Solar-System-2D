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
#include "../includes/SOIL.h"	
#include "../shaders/loadShaders.h"
#include "../textures/loadTextures.h"

#include <vector>
#include <iostream>

// Fisierele in care avem codul pentru soare si planete
#include "sun.h"
#include "planets.h"
#include "util.h"
#include "stars.h"

//  Identificatorii obiectelor de tip OpenGL;
GLuint VaoId, VboId, ColorBufferId, TextureBufferId, ProgramId, 
  myMatrixLocation, matrRotlLocation, codColLocation, starOpacLocation, 
  sun_texture, jupiter_texture;

void CreateShaders(void) {
  ProgramId =
      LoadShaders("../shaders/solar_system_shader.vert", "../shaders/solar_system_shader.frag");
  glUseProgram(ProgramId);
}

void CreateVBO(void) {
  //  Coordonatele varfurilor;
  GLfloat Vertices[] = {
      // Punct in origine pentru stele
       0.0f, 0.0f, 0.0f, 1.0f,
      // Cele 4 puncte din colturi;
      -1.0f, -1.0f, 0.0f, 1.0f, 
       1.0f, -1.0f, 0.0f, 1.0f, 
       1.0f,  1.0f, 0.0f, 1.0f,
      -1.0f,  1.0f, 0.0f, 1.0f,
      // Varfuri pentru axe;
      -1.0f,  0.0f, 0.0f, 1.0f, 
       1.0f,  0.0f, 0.0f, 1.0f, 
       0.0f, -1.0f, 0.0f, 1.0f,
       0.0f,  1.0f, 0.0f, 1.0f,
      // Varfuri Octagon
      50.0f,   0.0f, 0.0f, 1.0f,
      35.0f,  35.0f, 0.0f, 1.0f,
       0.0f,  50.0f, 0.0f, 1.0f,
     -35.0f,  35.0f, 0.0f, 1.0f,
     -50.0f,   0.0f, 0.0f, 1.0f,
     -35.0f, -35.0f, 0.0f, 1.0f,
       0.0f, -50.0f, 0.0f, 1.0f,
      35.0f, -35.0f, 0.0f, 1.0f,
  };

  //	Culori
  GLfloat Colors[] = {
      // Stele
      1.0f, 1.0f, 1.0f, 0.8f,
      // Culori Gradient
      0.0f, 0.0f, 0.1f, 1.0f,
      0.1f, 0.0f, 0.05f, 1.0f,
      0.0f, 0.0f, 0.1f, 1.0f,
      0.1f, 0.0f, 0.05f, 1.0f,
  };

  // Coordonate textura
  GLfloat Textures[] = {
      // Stele
      0.5f,  0.5f,
      // Puncte din colturi
      0.0f,  0.0f,
      1.0f,  0.0f,
      1.0f,  1.0f, 
      0.0f,  1.0f,
      // Axe
      0.0f,  0.5f,
      1.0f,  0.5f,
      0.5f,  0.0f,
      0.5f,  1.0f,
      // Octogon
      1.00f,  0.50f,
      0.85f,  0.85f,
      0.50f,  1.00f,
      0.15f,  0.85f,
      0.00f,  0.50f,
      0.15f,  0.15f,
      0.50f,  0.00f,
      0.85f,  0.15f,
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

  glGenBuffers(1, &TextureBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, TextureBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Textures), Textures, GL_STATIC_DRAW);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

//  Elimina obiectele de tip shader dupa rulare;
void DestroyShaders(void) { glDeleteProgram(ProgramId); }

//  Eliminarea obiectelor de tip VBO dupa rulare;
void DestroyVBO(void) {
	glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &ColorBufferId);
  glDeleteBuffers(1, &TextureBufferId);
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
  // Latimea si inaltimea imagine trebuie sa divida 100
	LoadTexture("../textures/sun.png", sun_texture);
	LoadTexture("../textures/jupiter.png", jupiter_texture);
  CreateShaders();

  codColLocation = glGetUniformLocation(ProgramId, "codCol");
  starOpacLocation = glGetUniformLocation(ProgramId, "starOpacity");
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");

  createStars(50);
}

//  Functia de desenarea a graficii pe ecran;
void RenderFunction(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  drawOptions(); 

  // Gradient pentru fundal
  drawBackground(myMatrixLocation, codColLocation);
  // Desenarea axelor;
  // drawAxes(codColLocation);
  // Stele
  drawStars(myMatrixLocation, codColLocation, starOpacLocation);

  glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sun_texture);
	//	Transmiterea variabilei uniforme pentru texturare spre shaderul de fragmente;
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);

  // Desenarea soarelui
  drawSun(resizeMatrix, myMatrixLocation, codColLocation);

  // Desenarea Planetelor
	glBindTexture(GL_TEXTURE_2D, jupiter_texture);
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);

  drawPlanets(resizeMatrix, sunPositionMatrix, myMatrixLocation, codColLocation);
 
  //  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
  glFlush();
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char *argv[]) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  createWindow();
  glewInit();

  Initialize();

  glutDisplayFunc(RenderFunction);
  glutCloseFunc(Cleanup);
  glutIdleFunc(UpdateScene);
  glutKeyboardFunc(Zoom);
  glutSpecialFunc(MoveSun);
  
  glutMainLoop();

  return 0;
}
