#include "Transform.h"

Transform::Transform() {
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);

	_modelMatrix = glm::mat4(1.0f);

	_forward = WORLD_FORWARD_VECTOR;
	_up = WORLD_UP_VECTOR;
	_right = WORLD_RIGHT_VECTOR;

}

glm::mat4 Transform::GetModelMatrix() {
	return _modelMatrix;
}

glm::vec3 Transform::GetPosition() {
	return _position;
}

glm::quat Transform::GetRotation() {
	return _rotation;
}

glm::vec3 Transform::GetScale() {
	return _scale;
}

void Transform::SetPosition(float x, float y, float z) {
	_position = glm::vec3(x, y, z);
	//Cuando nuestra posicion cambia, nuestra matriz de modelo cambia
	UpdateModelMatrixPosition();
}

void Transform::SetRotation(float x, float y, float z) {
	_rotation = glm::quat(glm::radians(glm::vec3(x, y, z)));
	//Cuando rotamos nuestra matriz de rotacion cambia, este metodo se llama cada que la rotacion cambie
	UpdateModelMatrixRotationScale();
}

void Transform::SetScale(float x, float y, float z) {
	_scale = glm::vec3(x, y, z);
	//Como cambio la escala tenemos que actualizar la matriz de rotacion
	UpdateModelMatrixRotationScale();
}

void Transform::MoveForward(float delta, bool world) {
	//Si world es true usamos los vectores globales, si no usamos los vectores locales
	if (world) {
		//
		_position += WORLD_FORWARD_VECTOR * delta;
	}
	else {
		_position += _forward * delta;
	}
	UpdateModelMatrixPosition();
}

void Transform::MoveUp(float delta, bool world) {
	if (world) {
		_position += WORLD_UP_VECTOR * delta;
	}
	else {
		_position += _up * delta;
	}
	UpdateModelMatrixPosition();
}

void Transform::MoveRight(float delta, bool world) {
	if (world) {
		_position += WORLD_RIGHT_VECTOR *delta;
	}
	else {
		_position += _right * delta;
	}
	UpdateModelMatrixPosition();
}

void Transform::Translate(float x, float y, float z, bool world) {
	if (world) {
		_position += glm::vec3(x, y, z);
	}
	else {
		_position += _forward * z;
		_position += _up * y;
		_position += _right * x;
	}
	UpdateModelMatrixPosition();
}

void Transform::Rotate(float x, float y, float z, bool world) {
	//True gira en los vectores globales
	//False gira en los vectores locales
	//Primero crearemos un cuaternion con la rotacion que nos pidan 
	//(un cuaternion que represente lo deseado)
	glm::quat newRotation = glm::quat(glm::radians(glm::vec3(x, y, z)));

	if (world) {
		// Crea una rotacion a partir de la roatcion que me estan pidieno usando como base los ejes 
		// coordenados normales
		_rotation = newRotation * _rotation;
	}
	else {
		_rotation = _rotation * newRotation;
	}
	UpdateModelMatrixRotationScale();
}

void Transform::UpdateModelMatrixPosition() {
	//En la matriz de modelo, en la columna 3 estan los valores de rotacion
	_modelMatrix[3][0] = _position.x;
	_modelMatrix[3][1] = _position.y;
	_modelMatrix[3][2] = _position.z;
}

void Transform::UpdateModelMatrixRotationScale() {
	_modelMatrix = glm::mat4_cast(_rotation);
	//En la matriz de modelo, en diagonal estan los valores de escala
	// (0,0)
	_modelMatrix[0] = _modelMatrix[0] * _scale.x;
	// (1,1)
	_modelMatrix[1] = _modelMatrix[1] * _scale.y;
	// (2,2)
	_modelMatrix[2] = _modelMatrix[2] * _scale.z;
	UpdateModelMatrixPosition();
	//Hacia donde apunta mi adelante, derecha, arriba. Se llama cada que cambia la rotacion
	UpdateLocalVectors();
}

void Transform::UpdateLocalVectors() {
	// La matriz de modelo tiene posicion y escala, la posicion no afecta pero la escala sí, si es muy 
	// grande afecta al vector.
	// Calculamos una matriz de rotacion solamente con la rotacion, sin escala y posición.
	// al hacerle el cast nos quedamos son con la rotacion y usamos eso para cambiar _forward y _up
	glm::mat4 rotationMaxtrix = glm::mat4_cast(_rotation);
	_forward = glm::vec3(rotationMaxtrix * glm::vec4(WORLD_FORWARD_VECTOR, 0.0f));
	_up = glm::vec3(rotationMaxtrix * glm::vec4(WORLD_UP_VECTOR, 0.0f));
	_right = glm::cross(_up, _forward);
}