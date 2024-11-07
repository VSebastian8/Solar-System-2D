//
// =========================================
// | Grafica pe calculator                 |
// =========================================
// | Proiect 2D - solar_system_shader.vert |
// =========================================
// 
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei; 
//

#version 330 core

//  Variabile de intrare (dinspre programul principal);
layout (location = 0) in vec4 in_Position; 
layout (location = 1) in vec4 in_Color;
layout (location = 2) in vec2 texCoord; 

//  Variabile de iesire;
// out vec4 gl_Position;   
out vec4 ex_Color;
out vec2 tex_Coord; 

//  Variabile uniforme;
uniform mat4 myMatrix;

void main(void)
{
    gl_Position = myMatrix*in_Position;
    ex_Color = in_Color;
    tex_Coord = vec2(texCoord.x, 1-texCoord.y);
} 
 