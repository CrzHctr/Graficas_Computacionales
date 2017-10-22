#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <math.h>
#include <vector>
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Camera.h"


ShaderProgram _shaderProgram;
Mesh geometría1;
Transform _transform;
Transform _transform2;
Camera _camera;
float radianes = 0.0f;
float cambio = 0.0001;
float escala = 0.5f;

double color = 0;

void Initialize()
{
	// Creando toda la memoria que el programa va a utilizar.

	// Creación del atributo de posiciones de los vértices.
	// Lista de vec2
	// Claramente en el CPU y RAM
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> colors;

	//Delantera
	positions.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	positions.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));


	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));


	std::vector<unsigned int> indices;
	//Delantera
	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(0); indices.push_back(2); indices.push_back(4);

	indices.push_back(0); indices.push_back(4); indices.push_back(3);
	indices.push_back(0); indices.push_back(3); indices.push_back(1);

	indices.push_back(4); indices.push_back(2); indices.push_back(1);
	indices.push_back(4); indices.push_back(1); indices.push_back(3);



	geometría1.CreateMesh(positions.size());
	geometría1.SetIndices(indices, GL_STATIC_DRAW);
	geometría1.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	geometría1.SetColorAttribute(colors, GL_STATIC_DRAW, 1);

	_shaderProgram.CreateProgram();
	_shaderProgram.AttachShader("Default.vert", GL_VERTEX_SHADER);
	_shaderProgram.AttachShader("Default.frag", GL_FRAGMENT_SHADER);

	_shaderProgram.SetAttribute(0, "VertexPosition");
	_shaderProgram.SetAttribute(1, "VertexColor");
	_shaderProgram.LinkProgram();

	//_transform.SetScale(20.0f, 1.0f, 20.0f);

	_transform2.SetPosition(-20.0f, 6.0f, -50.0f);

	_camera.MoveForward(10);
	//_camera.SetPosition(0.0f, 8.0f, 0.0f);
}

void GameLoop()
{
	//Aquí adentro pasa todo lo que queramos que se siga repitiendo
	// Limpiamos el buffer de color y el buffer de profunidad.
	// Siempre hacerlo al inicio del frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//_camera.MoveRight(0.0001f);
	//_camera.Rotate(0.0f, 0.01f, 0.0f, false);

	//True gira en los vectores globales
	//False gira en los vectores locales
	_transform.Rotate(0.005f, 0.005f, 0.005f, false);
	_transform.SetPosition(5.0f*glm::cos(glm::radians(radianes)), 5.0f*glm::sin(glm::radians(radianes)), 0.0f);
	radianes += 0.005f;

	while (escala >= 1.0f) {
		cambio *= -1;
	}

	while (escala <= 0.25f) {
		cambio *= -1;
	}

	escala += cambio;


	_transform2.Rotate(-0.005f, -0.005f, -0.005f, false);
	_transform2.SetScale(escala, escala, escala);

	_shaderProgram.Activate();
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix());
	geometría1.Draw(GL_TRIANGLES);
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform2.GetModelMatrix());
	geometría1.Draw(GL_TRIANGLES);

	// Cuando terminamos de renderear, cambiamos los buffers.
	glutSwapBuffers();

	color += .01;

	glClearColor(glm::cos(glm::radians(color)), glm::sin(glm::radians(color)), glm::cos(glm::radians(color)), glm::sin(glm::radians(color)));
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
	glutIdleFunc(Idle);

	// Inicializar GLEW. Esta librería se encarga de obtener el API de OpenGL de
	// nuestra tarjeta de video. SHAME ON YOU MICROSOFT.
	glewInit();

	// Configurar OpenGL. Este es el color por default del buffer de color
	// en el framebuffer.
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);


	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	std::cout << glGetString(GL_VERSION) << std::endl;

	// Configuración inicial de nuestro programa.
	Initialize();

	// Iniciar la aplicación. El main se pausará en esta línea hasta que se cierre
	// la venta de OpenGL.
	glutMainLoop();

	return 0;
}