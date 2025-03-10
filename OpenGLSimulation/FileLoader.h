#pragma once

#include <iostream>

#include <fstream>
#include <sstream>
#include <string>

#include "Mesh.h"

class FileLoader
{
public:
	static int LoadMeshFromOBJ(const char* filepath, Mesh& mesh);
};

