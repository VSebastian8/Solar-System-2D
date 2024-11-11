//
// =========================================
// | Grafica pe calculator                  |
// =========================================
// | Proiect 2D - solar_system_shader.frag |
// =========================================
// 
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//

#version 330 core

//	Variabile de intrare (dinspre Shader.vert);
in vec4 ex_Color;
in vec2 tex_Coord;	

//	Variabile de iesire	(spre programul principal);
out vec4 out_Color;		//	Culoarea actualizata;

//	Variabilele uniforme;
uniform int codCol;
uniform float starOpacity;
uniform sampler2D myTexture;

//	Actualizeaza culoarea in functie de codCol;
void main(void)
{
  switch (codCol)
  {
	case 0: // Background
		out_Color = ex_Color;
		break;
	case 1: // Stars
		out_Color = vec4 (1.0, 1.0, 1.0, starOpacity);
		break;
	case 2: // Textures
		out_Color = texture(myTexture, tex_Coord);
		break;
  };
}
 