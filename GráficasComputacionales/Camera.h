#pragma once

#include <glm/glm.hpp>
#include "Transform.h"

class Camera {
public:
	Camera();

	glm::mat4 GetViewProjection();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::vec3 GetPosition();

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	void MoveForward(float delta, bool world = false);
	void MoveUp(float delta, bool world = false);
	void MoveRight(float delta, bool world = false);

	//rota la camara en el eje y
	void Yaw(float degrees);
	//rota la camara en z
	void Roll(float degrees);
	//rota la camara en x
	void Pitch(float degrees);

	void Rotate(float x, float y, float z, bool world = false);

	//camara 3d
	void SetPerspective(float nearPlane, float farPlane, float fieldOfView, float aspectRatio);
	//camara 2d
	void SetOrthographic(float size, float aspectRatio);
private:

	Transform _transform;

	glm::mat4 _viewMatrix;
	glm::mat4 _projectionMatrix;
};