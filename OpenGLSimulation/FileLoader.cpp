#include "FileLoader.h"

/// LoadMeshFromOBJ
/// will load a mesh from an obj file, using string streams to read each line
/// and push the data to the mesh class

int FileLoader::LoadMeshFromOBJ(const char* filepath, Mesh& mesh)
{
    std::string line; std::ifstream meshFile(filepath);

    if(!meshFile.is_open())
        return -1;

    while (getline(meshFile, line))
    {
        std::istringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "v") {
            Vertex vertex;
            ss >> vertex.x; ss >> vertex.y; ss >> vertex.z;
            mesh.vertices.push_back(vertex);
        }

        else if (type == "f") {
            for (int i = 0; i < 3; i++)
            {
                int index = 0; ss >> index;
                mesh.indices.push_back(index);
            }
        }
    }

    meshFile.close();

    for (const auto& v : mesh.vertices)
        std::cout << "Vertex:" << v.x << ", " << v.y << ", " << v.z << std::endl;
    for(int i : mesh.indices)
        std::cout << i << ", ";

    return 0;
}
