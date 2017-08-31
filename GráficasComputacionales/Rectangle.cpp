#include "Rectangle.h"

Rectangle::Rectangle()
{
	_width = 1.0f;
	_height = 1.0f;

}

Rectangle::Rectangle(float w, float h)
{
	_width = w;
	_height = h;
}

float Rectangle::GetWidth()
{
	return _width;

}

float Rectangle::GetHeight()
{
	return _height;
}

float Rectangle::GetArea()
{
	return _height *_width;
}

float Rectangle::GetPerimeter()
{
	return 2 * _height + 2 * _width;
}

void Rectangle::SetWidth(float w)
{
	_width = w;
}

void Rectangle::SetHeight(float h)
{
	_height = h;
}
