#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <math.h>
#include <vector>
#include "Input.h"
#include "Mesh.h"
#include "Shader.h"
#include "ShaderProgram.h"

GLuint vao;
//GLuint _shaderProgram;
ShaderProgram shaderProgram;
Mesh _mesh;

void Initialize()
{
	// Creando toda la memoria que el programa va a utilizar.

	// Creación del atributo de posiciones de los vértices.
	// Lista de vec2
	// Claramente en el CPU y RAM

	std::vector<glm::vec2> positions;
	std::vector<glm::vec3> colors;
	int radio = 1;
	double i, j;
	positions.push_back(glm::vec2(0.0f, 0.5f));
	i = 0;
	while (i < 6) {
		float angle = (378.0f - (72.0f * i));
		double radianes = angle * 0.01745329252f; //Pi / 180
		float x = 0;
		positions.push_back(glm::vec2(
			glm::cos((radianes)),
			glm::sin(radianes)));

		positions.push_back(glm::vec2(
			glm::cos(radianes) * 0.5f,
			glm::sin(radianes) * 0.5f));
		i++;
	}

	j = 0;
	while (j < 13) {
		float par = j * 78.0f;
		colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		j++;
	}




	// GEOMETRIA CON LA CLASE MESH

	//Creamos un objeto para leer archivos

	// cARGAR sHADERS

	//////////////////////////////////////////////////////////////

	_mesh.CreateMesh(positions.size());
	_mesh.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	_mesh.SetColorAttribute(colors, GL_STATIC_DRAW, 1);

	//_shaderProgram = glCreateProgram();
	shaderProgram.CreateProgram();
	shaderProgram.SetAttribute(0, "VertexPosition");
	shaderProgram.SetAttribute(1, "VertexColor");
	//glBindAttribLocation(_shaderProgram, 0, "VertexPosition");
	//glBindAttribLocation(_shaderProgram, 1, "VertexColor");

	//glAttachShader("Default.verg", GL_VERTEX_SHADER);
	//glAttachShader("Default.frag", GL_FRAGMENT_SHADER);
	shaderProgram.AttachShader("Default.verg", GL_VERTEX_SHADER);
	shaderProgram.AttachShader("Default.frag", GL_FRAGMENT_SHADER);

	//glLinkProgram(_shaderProgram);
	shaderProgram.LinkProgram();
}

void GameLoop()
{
	// Limpiamos el buffer de color y el buffer de profunidad.
	// Siempre hacerlo al inicio del frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	shaderProgram.Activate();
	_mesh.Draw(GL_TRIANGLE_STRIP);
	shaderProgram.Deactivate();

	// Cuando terminamos de renderear, cambiamos los buffers.
	glutSwapBuffers();
}

void Idle() {
	//Cuando OpenGL entra en modo reposo (para ahorrar bateria, por ejemplo)
	//le decimos que vuelva a dibujar
	//Vuelve a mandar a llamar GameLoop
	glutPostRedisplay();
}

void ReshapeWindow(int width, int height) {

	glViewport(0, 0, width, height);
	/*
	//Para configurar un uniform, tenemos que decirle a OpenGL, que vamos a utilizar el
	//shader program (manager)
	glUseProgram(shaderProgram);
	GLint uniformLocation = glGetUniformLocation(shaderProgram, "Resolution");
	glUniform2f(uniformLocation, width, height);
	glUseProgram(0);
	*/
}

int main(int argc, char* argv[])
{
	// Inicializar freeglut
	// Freeglut se encarga de crear una ventana
	// en donde podemos dibujar
	glutInit(&argc, argv);
	// Solicitando una versión específica de OpenGL.
	//glutInitContextVersion(4, 4);
	// Iniciar el contexto de OpenGL. El contexto se refiere
	// a las capacidades que va a tener nuestra aplicación
	// gráfica.
	// En este caso estamos trabajando con el pipeline programable.
	glutInitContextProfile(GLUT_CORE_PROFILE);
	// Freeglut nos permite configurar eventos que ocurren en la ventana.
	// Un evento que nos interesa es cuando alguien cierra la ventana.
	// En este caso, simplemente dejamos de renderear la esscena y terminamos el programa.
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	// Configuramos el framebuffer. En este caso estamos solicitando un buffer
	// true color RGBA, un buffer de profundidad y un segundo buffer para renderear.
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	// Iniciar las dimensiones de la ventana (en pixeles)
	glutInitWindowSize(400, 400);
	// Creamos la ventana y le damos un título.
	glutCreateWindow("Hello World GL");
	// Asociamos una función de render. Esta función se mandará a llamar para dibujar un frame.
	glutDisplayFunc(GameLoop);

	// Inicializar GLEW. Esta librería se encarga de obtener el API de OpenGL de
	// nuestra tarjeta de video. SHAME ON YOU MICROSOFT.
	glewInit();

	// Configurar OpenGL. Este es el color por default del buffer de color
	// en el framebuffer.
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);

	std::cout << glGetString(GL_VERSION) << std::endl;

	// Configuración inicial de nuestro programa.
	Initialize();

	// Iniciar la aplicación. El main se pausará en esta línea hasta que se cierre
	// la venta de OpenGL.
	glutMainLoop();

	return 0;
}