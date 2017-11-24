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
#include "Texture2D.h"
#include "DepthBuffer.h"
#include <IL/il.h>


ShaderProgram _shaderProgram;
ShaderProgram _shaderProgram2;
Mesh _mesh;
Mesh _mesh2;
//Mano
Transform _transform;
//Piso
Transform _transform2;
// DEDOS
Transform _dedo1_1;
Transform _dedo1_2;
Transform _dedo2_1;
Transform _dedo2_2;
Transform _dedo3_1;
Transform _dedo3_2;
Transform _dedo4_1;
Transform _dedo4_2;

Camera _camera;
//Caja
Texture2D _texture;
//Suelo
Texture2D _texture2;
//Pueeercooo
Texture2D _texture3;
ShaderProgram _shaderDepth;
Camera _caemraLight;
DepthBuffer _depthBuffer;


////////////////////////////////////////////////////////////////
float limit = 0.0f;
float openClose = 0.3f;
///////////////////////////////////////////////////////////////
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
	std::vector<glm::vec3> positionsFingers;
	std::vector<glm::vec3> colors;
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> normales;
	std::vector<glm::vec2>Textura;
	_texture.LoadTexture("caja.jpg");
	_texture2.LoadTexture("piso.jpg");


	//Delantera
	positions.push_back(glm::vec3(-3.0f, 0.0f, 3.0f));
	positions.push_back(glm::vec3(3.0f, 0.0f, 3.0f));
	positions.push_back(glm::vec3(3.0f, 6.0f, 3.0f));
	positions.push_back(glm::vec3(-3.0f, 6.0f, 3.0f));

	//Derecha
	positions.push_back(glm::vec3(3.0f, 0.0f, 3.0f));
	positions.push_back(glm::vec3(3.0f, 0.0f, -3.0f));
	positions.push_back(glm::vec3(3.0f, 6.0f, -3.0f));
	positions.push_back(glm::vec3(3.0f, 6.0f, 3.0f));

	//Izquiera
	positions.push_back(glm::vec3(-3.0f, 0.0f, -3.0f));
	positions.push_back(glm::vec3(-3.0f, 0.0f, 3.0f));
	positions.push_back(glm::vec3(-3.0f, 6.0f, 3.0f));
	positions.push_back(glm::vec3(-3.0f, 6.0f, -3.0f));

	//Trasera
	positions.push_back(glm::vec3(3.0f, 0.0f, -3.0f));
	positions.push_back(glm::vec3(-3.0f, 0.0f, -3.0f));
	positions.push_back(glm::vec3(-3.0f, 6.0f, -3.0f));
	positions.push_back(glm::vec3(3.0f, 6.0f, -3.0f));

	//Superior
	positions.push_back(glm::vec3(-3.0f, 6.0f, 3.0f));
	positions.push_back(glm::vec3(3.0f, 6.0f, 3.0f));
	positions.push_back(glm::vec3(3.0f, 6.0f, -3.0f));
	positions.push_back(glm::vec3(-3.0f, 6.0f, -3.0f));

	//Inferior
	positions.push_back(glm::vec3(-3.0f, 0.0f, -3.0f));
	positions.push_back(glm::vec3(3.0f, 0.0f, -3.0f));
	positions.push_back(glm::vec3(3.0f, 0.0f, 3.0f));
	positions.push_back(glm::vec3(-3.0f, 0.0f, 3.0f));



	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));

	colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));

	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));

	colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));

	normales.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normales.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normales.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normales.push_back(glm::vec3(0.0f, 0.0f, 1.0f));

	normales.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normales.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normales.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normales.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	normales.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normales.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normales.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normales.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));

	normales.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normales.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normales.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normales.push_back(glm::vec3(0.0f, 0.0f, -1.0f));

	normales.push_back(glm::vec3(0.0f, 1.0f, .0f));
	normales.push_back(glm::vec3(0.0f, 1.0f, .0f));
	normales.push_back(glm::vec3(0.0f, 1.0f, .0f));
	normales.push_back(glm::vec3(0.0f, 1.0f, .0f));

	normales.push_back(glm::vec3(0.0f, -1.0f, .0f));
	normales.push_back(glm::vec3(0.0f, -1.0f, .0f));
	normales.push_back(glm::vec3(0.0f, -1.0f, .0f));
	normales.push_back(glm::vec3(0.0f, -1.0f, .0f));

	//Delantera
	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(0); indices.push_back(2); indices.push_back(3);

	//Derecha
	indices.push_back(4); indices.push_back(5); indices.push_back(6);
	indices.push_back(4); indices.push_back(6); indices.push_back(7);

	//Trasera
	indices.push_back(8); indices.push_back(9); indices.push_back(10);
	indices.push_back(8); indices.push_back(10); indices.push_back(11);

	//Izquierda
	indices.push_back(12); indices.push_back(13); indices.push_back(14);
	indices.push_back(12); indices.push_back(14); indices.push_back(15);

	//Superior
	indices.push_back(16); indices.push_back(17); indices.push_back(18);
	indices.push_back(16); indices.push_back(18); indices.push_back(19);

	//Inferior
	indices.push_back(20); indices.push_back(21); indices.push_back(22);
	indices.push_back(20); indices.push_back(22); indices.push_back(23);

	//Cara Frente 
	Textura.push_back(glm::vec2(0.0f, 0.0f));
	Textura.push_back(glm::vec2(1.0f, 0.0f));
	Textura.push_back(glm::vec2(1.0f, 1.0f));
	Textura.push_back(glm::vec2(0.0f, 1.0f));
	//Cara Derecha
	Textura.push_back(glm::vec2(0.0f, 0.0f));
	Textura.push_back(glm::vec2(1.0f, 0.0f));
	Textura.push_back(glm::vec2(1.0f, 1.0f));
	Textura.push_back(glm::vec2(0.0f, 1.0f));
	//Cara Izquierda 
	Textura.push_back(glm::vec2(0.0f, 0.0f));
	Textura.push_back(glm::vec2(1.0f, 0.0f));
	Textura.push_back(glm::vec2(1.0f, 1.0f));
	Textura.push_back(glm::vec2(0.0f, 1.0f));
	//Cara Atras
	Textura.push_back(glm::vec2(0.0f, 0.0f));
	Textura.push_back(glm::vec2(1.0f, 0.0f));
	Textura.push_back(glm::vec2(1.0f, 1.0f));
	Textura.push_back(glm::vec2(0.0f, 1.0f));
	//Cara Arriba 
	Textura.push_back(glm::vec2(0.0f, 0.0f));
	Textura.push_back(glm::vec2(1.0f, 0.0f));
	Textura.push_back(glm::vec2(1.0f, 1.0f));
	Textura.push_back(glm::vec2(0.0f, 1.0f));
	//Cara Abajo 
	Textura.push_back(glm::vec2(0.0f, 0.0f));
	Textura.push_back(glm::vec2(1.0f, 0.0f));
	Textura.push_back(glm::vec2(1.0f, 1.0f));
	Textura.push_back(glm::vec2(0.0f, 1.0f));

	_depthBuffer.Create(2048);

	_mesh.CreateMesh(positions.size());
	_mesh.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	_mesh.SetColorAttribute(colors, GL_STATIC_DRAW, 1);
	_mesh.SetNormalAttribute(normales, GL_STATIC_DRAW, 2);
	_mesh.SetTexCoordAttribute(Textura, GL_STATIC_DRAW, 3);
	_mesh.SetIndices(indices, GL_STATIC_DRAW);

	/////////////////////////////////////////////////////////////////////////
	_shaderDepth.CreateProgram();
	_shaderProgram.CreateProgram();

	_shaderDepth.AttachShader("Depth.frag", GL_FRAGMENT_SHADER);
	_shaderDepth.AttachShader("Depth.verg", GL_VERTEX_SHADER);

	_shaderProgram.AttachShader("Shadow.verg", GL_VERTEX_SHADER);
	_shaderProgram.AttachShader("Shadow.frag", GL_FRAGMENT_SHADER);
	/////////////////////////////////////////////////////////////////////////
	//_shaderProgram.AttachShader("Phong.verg", GL_VERTEX_SHADER);
	//_shaderProgram.AttachShader("Phong.frag", GL_FRAGMENT_SHADER);
	_shaderProgram.SetAttribute(0, "VertexPosition");
	_shaderDepth.SetAttribute(0, "VertexPosition");
	_shaderProgram.SetAttribute(1, "VertexColor");
	_shaderProgram.SetAttribute(2, "VertexNormal");
	_shaderProgram.SetAttribute(3, "VertexTexCoord");
	_shaderDepth.SetAttribute(0, "VertexPosition");
	_shaderProgram.LinkProgram();
	_shaderDepth.LinkProgram();
	_transform.SetScale(10, 0.5f, 10);
	_transform.MoveUp(-10, true);


	////////////////////////////////////////////////////////////////////////////
	/*
	_shaderProgram.Activate();
	_shaderProgram.SetUniformf("LightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	_shaderProgram.SetUniformf("LightPosition", glm::vec3(0.0f, 5.0f, 0.0f));
	_shaderProgram.SetUniformi("DiffuseTexture", 0);
	_shaderProgram.Deactivate();
	_shaderProgram.LinkProgram();
	_transform.SetPosition(0.0f, -12.0f, 0.0f);
	_transform.SetScale(10.0f, 2.0f, 10.0f);
	_texture3.LoadTexture("Piso.jpg");
	_shaderProgram2.CreateProgram();
	_shaderProgram2.AttachShader("Phong.verg", GL_VERTEX_SHADER);
	_shaderProgram2.AttachShader("Phong.frag", GL_FRAGMENT_SHADER);
	_shaderProgram2.SetAttribute(0, "VertexPosition");
	_shaderProgram2.SetAttribute(1, "VertexColor");
	_shaderProgram2.SetAttribute(2, "VertexNormal");
	_shaderProgram2.SetAttribute(3, "VertexTexCoord");
	_shaderProgram2.LinkProgram();
	_shaderProgram2.Activate();
	_shaderProgram2.SetUniformf("LightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	_shaderProgram2.SetUniformf("LightPosition", glm::vec3(0.0f, 0.0f, 10.0f));
	_shaderProgram2.SetUniformi("DiffuseTexture", 0);
	_shaderProgram2.Deactivate();*/
	//_camera.MoveForward(25.0f);
	//_transform2.SetScale(10, 0.5f, 10);
	//_transform2.MoveUp(-10, true);
	//_shaderProgram.SetUniformVec3("LightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	//_shaderProgram.SetUniformVec3("LightPosition", glm::vec3(0.0f, 0.0f, 10.0f));

	//_transform.SetScale(20.0f, 1.0f, 20.0f);

	//_transform.SetScale(0.3f, 0.3f, 0.3f);
	//_transform.SetPosition(0.0f, 0.0f, 0.0f);

	//_transform2.SetScale(8.0f, 0.01f, 8.0f);
	//_transform2.SetPosition(0.0f, -12.0f, 0.0f);

	//_camera.SetPosition(0.0f, 0.0f, 10.0f);
	//_camera.Rotate(-30.0f, 0.0f, 0.0f,false);

	//_transform2.SetPosition(-20.0f, 6.0f, -50.0f);

	//_camera.MoveForward(10);
	_camera.SetPosition(0.0f, 8.0f, 10.0f);
	_camera.Rotate(-20.0f, 0.0f, 0.0f, false);
	_caemraLight.SetOrthographic(15.0f, 1.0);
	_caemraLight.SetPosition(-3.0, 6.0, 0.0);
	_caemraLight.Pitch(-90);
	_caemraLight.Rotate(-50.0f, 0.0f, 0.0f, false);
}

void GameLoop()
{
	//Aquí adentro pasa todo lo que queramos que se siga repitiendo
	// Limpiamos el buffer de color y el buffer de profunidad.
	// Siempre hacerlo al inicio del frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_camera.SetPosition(0.0f, 0.0f, 25.0f);
	//_camera.MoveRight(0.0001f);
	//_camera.Rotate(0.0f, 0.01f, 0.0f, false);

	//True gira en los vectores globales
	//False gira en los vectores locales
	_transform2.Rotate(0.1f, 0.1f, 0.1f, true);
	_depthBuffer.Bind();

	_shaderDepth.Activate();

	_shaderDepth.SetUniformMatrix("mvpMatrix", _caemraLight.GetViewProjection()* _transform.GetModelMatrix());
	_mesh.Draw(GL_TRIANGLES);
	_shaderDepth.SetUniformMatrix("mvpMatrix", _caemraLight.GetViewProjection()* _transform2.GetModelMatrix());
	_mesh.Draw(GL_TRIANGLES);

	_depthBuffer.Unbind();
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	_shaderDepth.Deactivate();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shaderProgram.Activate();
	_shaderProgram.SetUniformf("LightPosition", glm::vec3(0.0f, 5.0f, 1.0f));
	_shaderProgram.SetUniformf("CameraPosition", glm::vec3(0.0f, 1.0f, 2.0f));
	_shaderProgram.SetUniformi("DiffuseTexture", 0);
	_shaderProgram.SetUniformi("ShadowMap", 1);


	//_transform.Rotate(0.005f, 0.005f, 0.005f, false);
	//_transform.SetPosition(5.0f*glm::cos(glm::radians(radianes)), 5.0f*glm::sin(glm::radians(radianes)), 0.0f);
	radianes += 0.005f;

	/*if (escala <= 0.25f) {
	cambio *= -1;
	}
	else if (escala >= 1.0f) {
	cambio *= -1;
	}
	escala += cambio;*/


	//_transform2.Rotate(-0.005f, -0.005f, -0.005f, false);
	//_transform2.SetScale(escala, escala, escala);

	//_shaderProgram2.Activate();
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform2.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("ModelMatrix", _transform.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("ModelMatrix", _transform.GetModelMatrix());
	glActiveTexture(GL_TEXTURE0);
	_texture.Bind();
	glActiveTexture(GL_TEXTURE1);
	glActiveTexture(GL_TEXTURE1);
	_mesh.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_texture.Unbind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.UnbindDepthMap();

	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("ModelMatrix", _transform2.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("LightVPMatrix", _caemraLight.GetViewProjection());
	glActiveTexture(GL_TEXTURE0);
	_texture2.Bind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.BindDepthMap();
	_mesh.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_texture2.Unbind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.UnbindDepthMap();
	_shaderProgram.Deactivate();


	//_shaderProgram.Deactivate();


	//_shaderProgram.Activate();
	//_shaderProgram2.Activate();
	//_shaderProgram2.SetUniformMatrix("normalMatrix", glm::transpose(glm::inverse(glm::mat3(_transform2.GetModelMatrix()))));
	//_shaderProgram2.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection()* _transform2.GetModelMatrix());
	//glm::vec3 newCamera = _camera.GetPosition();
	//_shaderProgram2.SetUniformf("cameraPosition", newCamera);
	//_shaderProgram2.SetUniformMatrix("ModelMatrix", _transform2.GetModelMatrix());



	//_texture.LoadTexture("caja.jpg");
	/*_shaderProgram.SetUniformMatrix("modelMatrix", _transform.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix());
	_shaderProgram.SetUniformi("DiffuseTexture", 0);
	glActiveTexture(GL_TEXTURE0);
	_texture.Bind();
	_mesh.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_texture.Unbind();
	_shaderProgram.Deactivate();
	_shaderProgram.Activate();
	//_texture2.LoadTexture("piso.jpg");
	_shaderProgram.SetUniformMatrix("modelMatrix", _transform2.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform2.GetModelMatrix());
	_shaderProgram.SetUniformi("DiffuseTexture", 0);
	glActiveTexture(GL_TEXTURE0);
	_texture2.Bind();
	_mesh.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_texture2.Unbind();
	_shaderProgram.Deactivate();*/


	// Cuando terminamos de renderear, cambiamos los buffers.
	glutSwapBuffers();

	//color += .01;

	//glClearColor(glm::cos(glm::radians(color)), glm::sin(glm::radians(color)), glm::cos(glm::radians(color)), glm::sin(glm::radians(color)));
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
	ilInit();
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
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
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