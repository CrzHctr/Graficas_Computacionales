#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Camera.h"


Mesh mesh;
ShaderProgram shProgram;
Transform _transform;
Camera _camera;

void Initialize() {

	//Creacin del atributo de posiciones de estos vertices. Lista de vec2.
	//Claramente en CPU y RAM
	std::vector<glm::vec3> positions;
	//Cara derecha
	positions.push_back(glm::vec3(3.0f, 0, 3.0f));  
	positions.push_back(glm::vec3(3.0f, 0, -3.0f)); 
	positions.push_back(glm::vec3(3.0f, 6.0f, -3.0f));
	positions.push_back(glm::vec3(3.0f, 6.0f, 3.0f)); 
													  
	positions.push_back(glm::vec3(-3.0f, 0, 3.0f)); 
	positions.push_back(glm::vec3(3.0f, 0, 3.0f)); 
	positions.push_back(glm::vec3(3.0f, 6.0f, 3.0f)); 
	positions.push_back(glm::vec3(-3.0f, 6.0f, 3.0f)); 
													   
	positions.push_back(glm::vec3(-3.0f, 0, -3.0f)); 
	positions.push_back(glm::vec3(-3.0f, 0, 3.0f)); 
	positions.push_back(glm::vec3(-3.0f, 6.0f, 3.0f)); 
	positions.push_back(glm::vec3(-3.0f, 6.0f, -3.0f)); 

	positions.push_back(glm::vec3(3.0f, 0, -3.0f));  
	positions.push_back(glm::vec3(-3.0f, 0, -3.0f)); 
	positions.push_back(glm::vec3(-3.0f, 6.0f, -3.0f));
	positions.push_back(glm::vec3(3.0f, 6.0f, -3.0f)); 

	positions.push_back(glm::vec3(3.0f, 0, 3.0f)); 
	positions.push_back(glm::vec3(-3.0f, 0, 3.0f)); 
	positions.push_back(glm::vec3(-3.0f, 0, -3.0f)); 
	positions.push_back(glm::vec3(3.0f, 0, -3.0f));  
													 
	positions.push_back(glm::vec3(3.0f, 6.0f, 3.0f)); 
	positions.push_back(glm::vec3(-3.0f, 6.0f, -3.0f)); 
	positions.push_back(glm::vec3(-3.0f, 6.0f, 3.0f)); 
	positions.push_back(glm::vec3(3.0f, 6.0f, -3.0f)); 


	std::vector<glm::vec3> colors;

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
	
	colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));

	//Se crea el vector con los indices de las posiciones
	std::vector<unsigned int> indices = {
		0, 1, 2, 0, 2, 3, 
		4, 5, 6, 4, 6, 7, 
		8, 9, 10, 8, 10, 11, 
		12, 13, 14, 12, 14, 15, 
		16, 17, 18, 16, 18, 19, 
		20, 21, 22, 20, 23, 21 
	};





	mesh.CreateMesh(positions.size());
	mesh.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	mesh.SetColorAttribute(colors, GL_STATIC_DRAW, 1);
	mesh.SetIndices(indices, GL_STATIC_DRAW);
	shProgram.CreateProgram();
	shProgram.SetAttribute(0, "VertexPosition");
	shProgram.SetAttribute(1, "VertexColor");
	shProgram.AttachShader("Default.vert", GL_VERTEX_SHADER);
	shProgram.AttachShader("Default.frag", GL_FRAGMENT_SHADER);
	shProgram.LinkProgram();

	//Se ajusta la cámara para que se vea todo el cubo
	_camera.SetPosition(0.0f, 1.0f, 20.0f);


}

void GameLoop() {

	//Limpiamos el buffer de color y el buffer de profundidad
	//Siempre hacerlo al inicio del frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_transform.Rotate(0.01f, 0.01f, 0.01f, false);
	//_camera.MoveForward(0.001f);

	shProgram.Activate();
	shProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix());
	mesh.Draw(GL_TRIANGLES);
	shProgram.Deactivate();

	//Cuando terminamos de renderear, cambiamos los buffers
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
}

int main(int argc, char * argv[]) {

	//Inicializar freeglut.
	//Freeglut se encarga de crear una ventana para dibujar.
	glutInit(&argc, argv);

	//Solicitando una versión específica de OpenGL.
	glutInitContextVersion(4, 4);

	//Inicia el contexto de OpenGL. El contexto se refiere a las capacidades que va a tener
	//nuestra aplicación gráfica. En este caso estamos trabajando con el pipeline clásico.
	glutInitContextProfile(GLUT_CORE_PROFILE);

	//Freeglut nos permite configurar eventos que ocurren en la ventana. Un evento que nos
	//interesa es cuando alguien cierra la ventana. En este caso, simplemente dejamos de 
	//renderear la escena y terminamos el programa.
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//Configuramos el framebuffer. En este caso estamos solicitando un buffer true color RGBA,
	//un bugger de profundidad y un segundo buffer para renderear.
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	//Iniciar las dimensiones de la ventana (en pixeles).
	glutInitWindowSize(400, 400);

	//Se crea la ventana con un título
	glutCreateWindow("Hello World GL");

	//Asociamos una función de render. Esta función se mandará a llamar para dibujar un 
	//frame
	glutDisplayFunc(GameLoop);

	//Asociamos una función para el cambio de resolución de la ventana. Freeglut 
	//la manda a llamar cuando alguien cambie el tamaño de la ventana.
	glutReshapeFunc(ReshapeWindow);

	//Asociamos la función que se mandará a llamar cuando OpenGL entre en modo de reposo
	glutIdleFunc(Idle);

	//Inicializamos GLEW. Esta librería se encarga de obtener el API de OpenGl de nuestra
	//tarjeta de video.
	glewInit();

	//Configurar OpenGL. Este es el color por default del buffer de color en el framebuffer.
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);

	//std::cout << glGetString(GL_VERSION) << std::endl;

	//Además de solicitar el buffer de profundidad, tenemos que decirle a OpenGL que lo queremos activo
	glEnable(GL_DEPTH_TEST);
	//Activamos el borrado de caras traseras
	//Ahora todos los triangulos que dibujemos deben estar en CCW
	glEnable(GL_CULL_FACE);
	//No dibujar las caras traseras de la geometría
	glCullFace(GL_BACK);

	//Configuración inicial de nuestro programa
	Initialize();

	//Iniciar la aplicación. El main se pausará en esta línea hasta que se cierre la ventana.
	glutMainLoop();

	std::cin.get();
	return 0;
}