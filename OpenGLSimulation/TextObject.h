#pragma once

#include <string>

#include "Vector3.h"

struct TextObject
{
	TextObject(float x, float y, void* _font, const char* string, Vector3f textFillColor) : screenX(x), screenY(y), font(_font), text(string), color(textFillColor) {}
	TextObject() {screenX = 0; screenY = 0;}
	float screenX, screenY;
	void* font = nullptr;
	std::string text;
	Vector3f color;
};