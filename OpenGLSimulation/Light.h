#pragma once

#include "Vector4.h"

struct Light
{
	Vector4f position;
	Vector4f ambient, diffuse, specular;
};