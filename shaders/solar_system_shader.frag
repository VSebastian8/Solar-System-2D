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
uniform sampler2D myTexture;

//	Actualizeaza culoarea in functie de codCol;
void main(void)
{
  switch (codCol)
  {
	case 0: 
		out_Color = ex_Color;
		break;
	case 1: 
		out_Color = vec4 (1.0, 1.0, 1.0, 0.2);
		break;
	case 2: // Sun
		//out_Color=vec4 (0.8, 0.8, 0.2, 1.0);
		out_Color = texture(myTexture, tex_Coord);
		break;
	case 3: // Mercury
		out_Color = vec4 (0.9, 0.7, 0.2, 1.0);
		break;
	case 4: // Venus
		out_Color = vec4 (0.4, 0.6, 0.4, 1.0);
		break;
	case 5: // Earth
		out_Color = vec4 (0.2, 0.3, 0.8, 1.0);
		break;
	case 6: // Mars
		out_Color = vec4 (0.9, 0.1, 0.3, 1.0);
		break;
	case 7: // Jupiter
		out_Color = vec4 (0.6, 0.4, 0.1, 1.0);
		break;
	case 8: // Saturn
		out_Color = vec4 (0.8, 0.7, 0.3, 1.0);
		break;
	case 9: // Uranus
		out_Color = vec4 (0.3, 0.6, 0.8, 1.0);
		break;
	case 10: // Neptune
		out_Color = vec4 (0.5, 0.0, 1.0, 1.0);
		break;
	default:
		break;
  };
}
 