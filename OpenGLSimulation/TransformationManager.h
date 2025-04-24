#pragma once

#include <iostream>

#include "Object.h"
#include "Input.h"

class TransformationManager
{
public:
	TransformationManager();
	~TransformationManager();

	void Update(Object* object);

	void SetTransformMode(const unsigned char mode);
	void RotateTransformAxis(int direction);

private:
	enum TransformMode
	{
		TRANSLATE,
		SCALE,
		ROTATE,
		TEXTURE
	};

	enum TransformAxis
	{
		X, Y, Z
	};

	TransformMode transformationMode = TransformMode::TRANSLATE;
	TransformAxis transformationAxis = TransformAxis::X;

	void Translate(Object* object);
	void Scale(Object* object);
	void Rotate(Object* object);
	void Texture(Object* object);

	const unsigned char increaseAxisKeybind = 'n';
	const unsigned char decreaseAxisKeybind = 'm';

	const unsigned char translateKeybind = 't';
	const unsigned char scaleKeybind = 's';
	const unsigned char rotateKeybind = 'r';

	const float transformationSpeed = 0.01;
};