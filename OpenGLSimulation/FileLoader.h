#pragma once

#include <iostream>

#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <unordered_map>

#include "Vertex.h"
#include "Mesh.h"
#include "Texture.h"
#include "Vector3.h"

class FileLoader
{
public:
	static int LoadMeshFromOBJ(const char* filepath, Mesh& mesh);

	static int LoadTextureFromRAW(const char* filepath, int width, int height, Texture& texture);
	static int LoadTextureFromBMP(const char* filepath, Texture& texture);
};

