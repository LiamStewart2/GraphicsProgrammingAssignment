#include "TransformationManager.h"

TransformationManager::TransformationManager()
{
}

TransformationManager::~TransformationManager()
{
}

void TransformationManager::Update(Object* object)
{
	if(object == nullptr)
		return;

	switch (transformationMode)
	{
		case TransformMode::TRANSLATE:
			Translate(object);
			break;
		case TransformMode::SCALE:
			Scale(object);
			break;
		case TransformMode::ROTATE:
			Rotate(object);
			break;
		case TransformMode::TEXTURE:
			Texture(object);
			break;
		default:
			std::cerr << "Invalid Transform mode" << std::endl;
			break;
	}
}

void TransformationManager::SetTransformMode(const unsigned char mode)
{
	if(mode == translateKeybind)
		transformationMode = TransformMode::TRANSLATE;
	else if(mode == scaleKeybind)
		transformationMode = TransformMode::SCALE;
	else if(mode == rotateKeybind)
		transformationMode = TransformMode::ROTATE;
	else if(mode == textureKeybind)
		transformationMode = TransformMode::TEXTURE;
}

void TransformationManager::RotateTransformAxis(int direction)
{
	if (direction > 0)
	{
		switch (transformationAxis)
		{
		case TransformAxis::X:
			transformationAxis = TransformAxis::Y;
			break;
		case TransformAxis::Y:
			transformationAxis = TransformAxis::Z;
			break;
		case TransformAxis::Z:
			transformationAxis = TransformAxis::X;
			break;
		default:
			std::cerr << "Invalid Transform Axis" << std::endl;
			break;
		}
	}
	else
	{
		switch (transformationAxis)
		{
		case TransformAxis::X:
			transformationAxis = TransformAxis::Z;
			break;
		case TransformAxis::Y:
			transformationAxis = TransformAxis::X;
			break;
		case TransformAxis::Z:
			transformationAxis = TransformAxis::Y;
			break;
		default:
			std::cerr << "Invalid Transform Axis" << std::endl;
			break;
		}
	}
}

const char* TransformationManager::getTransformModeText()
{
	switch (transformationMode)
	{
	case TransformMode::TRANSLATE:
		return "Translate";
	case TransformMode::SCALE:
		return "Scale";
	case TransformMode::ROTATE:
		return "Rotate";
	case TransformMode::TEXTURE:
		return "Texture";
	}
	return "-";
}

const char* TransformationManager::getTransformAxisText()
{
	switch (transformationAxis)
	{
	case TransformAxis::X:
		return "x";
	case TransformAxis::Y:
		return "y";
	case TransformAxis::Z:
		return "z";
	}
	return "-";
}

void TransformationManager::Translate(Object* object)
{
	if(Keyboard::GetButtonState(increaseAxisKeybind))
	{ 
		switch (transformationAxis)
		{
		case TransformAxis::X:
			object->transform.Position.x += transformationSpeed;
			break;
		case TransformAxis::Y:
			object->transform.Position.y += transformationSpeed;
			break;
		case TransformAxis::Z:
			object->transform.Position.z += transformationSpeed;
			break;
		}
	}
	else if (Keyboard::GetButtonState(decreaseAxisKeybind))
	{
		switch (transformationAxis)
		{
		case TransformAxis::X:
			object->transform.Position.x -= transformationSpeed;
			break;
		case TransformAxis::Y:
			object->transform.Position.y -= transformationSpeed;
			break;
		case TransformAxis::Z:
			object->transform.Position.z -= transformationSpeed;
			break;
		}
	}
}

void TransformationManager::Scale(Object* object)
{
	if (Keyboard::GetButtonState(increaseAxisKeybind))
	{
		switch (transformationAxis)
		{
		case TransformAxis::X:
			object->transform.Scale.x += transformationSpeed;
			break;
		case TransformAxis::Y:
			object->transform.Scale.y += transformationSpeed;
			break;
		case TransformAxis::Z:
			object->transform.Scale.z += transformationSpeed;
			break;
		}
	}
	else if (Keyboard::GetButtonState(decreaseAxisKeybind))
	{
		switch (transformationAxis)
		{
		case TransformAxis::X:
			object->transform.Scale.x -= transformationSpeed;
			break;
		case TransformAxis::Y:
			object->transform.Scale.y -= transformationSpeed;
			break;
		case TransformAxis::Z:
			object->transform.Scale.z -= transformationSpeed;
			break;
		}
	}
}

void TransformationManager::Rotate(Object* object)
{
	if (Keyboard::GetButtonState(increaseAxisKeybind))
	{
		switch (transformationAxis)
		{
		case TransformAxis::X:
			object->transform.Rotation.x += transformationSpeed * 90;
			break;
		case TransformAxis::Y:
			object->transform.Rotation.y += transformationSpeed * 90;
			break;
		case TransformAxis::Z:
			object->transform.Rotation.z += transformationSpeed * 90;
			break;
		}
	}
	else if (Keyboard::GetButtonState(decreaseAxisKeybind))
	{
		switch (transformationAxis)
		{
		case TransformAxis::X:
			object->transform.Rotation.x -= transformationSpeed * 90;
			break;
		case TransformAxis::Y:
			object->transform.Rotation.y -= transformationSpeed * 90;
			break;
		case TransformAxis::Z:
			object->transform.Rotation.z -= transformationSpeed * 90;
			break;
		}
	}
}

void TransformationManager::Texture(Object* object)
{
	if(TextureKeybindhasBeenPressed == false)
	{
		if (Keyboard::GetButtonState(increaseAxisKeybind))
		{
			int materialIndex = FindMaterialIndex(object);
			if (materialIndex == -1)
				return;

			materialIndex += 1; if (materialIndex >= materials->size()) materialIndex -= materials->size();
			object->material = materials->at(materialIndex);

			TextureKeybindhasBeenPressed = true;
		}
		else if (Keyboard::GetButtonState(decreaseAxisKeybind))
		{
			int materialIndex = FindMaterialIndex(object);
			if (materialIndex == -1)
				return;

			materialIndex -= 1; if (materialIndex < 0) materialIndex += materials->size();
			object->material = materials->at(materialIndex);
			
			TextureKeybindhasBeenPressed = true;
		}
	}
	else
	{
		if (Keyboard::GetButtonState(increaseAxisKeybind) == false && Keyboard::GetButtonState(decreaseAxisKeybind) == false)
			TextureKeybindhasBeenPressed = false;
	}
}

int TransformationManager::FindMaterialIndex(Object* object)
{
	for(int i = 0; i < materials->size(); i++)
		if(materials->at(i) == object->material)
			return i;
	return -1;
}
