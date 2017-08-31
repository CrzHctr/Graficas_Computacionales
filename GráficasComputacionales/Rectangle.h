#pragma once
#include <string>

class Rectangle {

public:
	Rectangle();
	Rectangle(float w, float h);

	float GetWidth();
	float GetHeight();
	float GetArea();
	float GetPerimeter();

	void SetWidth(float w);
	void SetHeight(float h);


private:


	float _width;
	float _height;

};
