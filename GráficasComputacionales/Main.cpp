#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include "InputFile.h"


GLuint vao;
GLuint shaderProgram;


void Initialize() {

	double angulo = 18;
	std::vector<glm::vec2> positions;
	positions.push_back(glm::vec2(glm::cos(glm::radians(90.0f)), glm::sin(glm::radians(90.0f))));
	for (double i = 0; i <= 4; i++) {
		positions.push_back(glm::vec2(0.5*glm::cos(glm::radians(angulo)), 0.5 * glm::sin(glm::radians(angulo))));
		positions.push_back(glm::vec2(glm::cos(glm::radians(angulo)), glm::sin(glm::radians(angulo))));
		angulo -= 72;
		if (angulo < 0) {
			angulo += 360;
		}
	}
	positions.push_back(glm::vec2(0.5*glm::cos(glm::radians(18.0f)), 0.5*glm::sin(glm::radians(18.0f))));






	/*
	positions.push_back(glm::vec2(0.0f, 0.0f));
	for (double i = 0; i < 361; i++) {
	positions.push_back(glm::vec2(glm::cos(glm::radians(i)),glm::sin(glm::radians(i))));
	}
	*/

	std::vector<glm::vec3> colors;
	for (double i = 0; i <= 11; i++) {
		colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	/*
	colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	for (double i = 0; i < 361; i++) {
	colors.push_back(glm::vec3(glm::sin(glm::radians(i)), glm::cos(glm::radians(i)), i));
	}
	*/

	//Generamos un manager
	glGenVertexArrays(1, &vao);
	//Utilizar el vao. A partir de este momento, todos los VBOs creados y
	//configurados se van a asociar a este manager
	glBindVertexArray(vao);


	//Identificador del VBO de posiciones
	GLuint positionsVBO;
	//Creación del VBO posiciones
	glGenBuffers(1, &positionsVBO);
	//Activamos el buffer de posiciones para poder utilizarlo
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	//Creamos la memoria y la inicializamos con los datos del atributo de posiciones
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*positions.size(), positions.data(), GL_STATIC_DRAW);
	//Activamos el atributo en la tarjeta de video
	glEnableVertexAttribArray(0); //Posición
								  //Configuraos los datos del atributo en la tarjeta de video
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	//Ya no se utiliza este VBO, así que lo removemos
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Identificador del VBO de colores
	GLuint colorsVBO;
	//Creación del VBO de colores
	glGenBuffers(1, &colorsVBO);
	//Activamos para poder utilizar
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*colors.size(), colors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);//Colores
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//Desactivamos el manager
	glBindVertexArray(0);

	//Creamos un objeto para leer archivos

	InputFile ifile;

	//VERTEX SHADER
	ifile.Read("Default.vert");
	std::cout << ifile.GetContents();
	std::string vertexSource = ifile.GetContents();
	//Creamos un shader de tipo vertex shader
	GLuint vertexShaderHandler = glCreateShader(GL_VERTEX_SHADER);
	//Obtener los datos en el formato correcto
	const GLchar * vertexSource_c = (const GLchar *)vertexSource.c_str();
	//Le estamos dando el código fuente a OpenGL para que se lo asigne a shader
	glShaderSource(vertexShaderHandler, 1, &vertexSource_c, nullptr);
	//Compilamos el shader en busca de errores
	//Asumimos que no hay errores
	glCompileShader(vertexShaderHandler);


	InputFile ifile2;
	ifile2.Read("Default.frag");
	std::cout << ifile2.GetContents() << "\n";
	std::string fragmentSource = ifile2.GetContents();
	GLuint fragmentShaderHandler = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar *fragmentSource_c = (const GLchar*)fragmentSource.c_str();
	glShaderSource(fragmentShaderHandler, 1, &fragmentSource_c, nullptr);
	glCompileShader(fragmentShaderHandler);


	//Creamos el identificador para el manager de los shaders
	shaderProgram = glCreateProgram();
	//Adjuntamos el vertex shader al manager
	glAttachShader(shaderProgram, vertexShaderHandler);
	//Adjuntamos el fragment shader al manager
	glAttachShader(shaderProgram, fragmentShaderHandler);
	//Asociamos un buffer con índice 0 (posiciones) a la variable VertexPosition
	glBindAttribLocation(shaderProgram, 0, "VertexPosition");
	//Asociamos un buffer con índice 1 (Colores) a la variable VertexColor
	glBindAttribLocation(shaderProgram, 1, "VertexColor");
	//Ejecutamos el proceso de linker (aseguramos que el vertex y fragment son compatibles)
	glLinkProgram(shaderProgram);

	//Para configurar un uniform, tenemos que decirle a OpenGL, que vamos a utilizar el
	//shader program (manager)

	/*
	glUseProgram(shaderProgram);

	GLint uniformLocation = glGetUniformLocation(shaderProgram, "Resolution");

	glUniform2f(uniformLocation, 400.0f, 400.0f);
	glUseProgram(0);
	*/

}

void GameLoop() {

	//Limpiamos el buffer de color y el buffer de profundidad
	//Siempre hacerlo al inicio del frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Activamos el vertex shader y el fragment shader utilizando el manager
	glUseProgram(shaderProgram);
	//Activamos el manager, en este momento se activan todos los VBO
	//asociados automáticamente
	glBindVertexArray(vao);
	//Función de dibujado sin índices
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 12);
	//Terminamos de utilizar el manager
	glBindVertexArray(0);
	//Desactivamos el manager
	glUseProgram(0);

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
	/*
	//Para configurar un uniform, tenemos que decirle a OpenGL, que vamos a utilizar el
	//shader program (manager)
	glUseProgram(shaderProgram);
	GLint uniformLocation = glGetUniformLocation(shaderProgram, "Resolution");
	glUniform2f(uniformLocation, width, height);
	glUseProgram(0);
	*/
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
