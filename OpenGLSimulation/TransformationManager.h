#pragma once

#include <iostream>
#include <vector>

#include "Object.h"
#include "Input.h"

class TransformationManager
{
public:
	TransformationManager();
	~TransformationManager();

	void Update(Object* object);

	void SetMaterials(std::vector<Material*>* _materials) {materials = _materials;}

	void SetTransformMode(const unsigned char mode);
	void RotateTransformAxis(int direction);

	const char* getTransformModeText();
	const char* getTransformAxisText();

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

	std::vector<Material*>* materials;

	TransformMode transformationMode = TransformMode::TRANSLATE;
	TransformAxis transformationAxis = TransformAxis::X;

	void Translate(Object* object);
	void Scale(Object* object);
	void Rotate(Object* object);
	void Texture(Object* object);

	int FindMaterialIndex(Object* object);

	const unsigned char increaseAxisKeybind = 'n';
	const unsigned char decreaseAxisKeybind = 'm';

	const unsigned char translateKeybind = 'g';
	const unsigned char scaleKeybind = 'o';
	const unsigned char rotateKeybind = 'r';
	const unsigned char textureKeybind = 't';

	const float transformationSpeed = 0.05f;
	
	bool TextureKeybindhasBeenPressed = false;
};