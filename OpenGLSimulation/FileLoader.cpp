#include "FileLoader.h"

/// LoadMeshFromOBJ
/// will load a mesh from an obj file, using string streams to read each line
/// and push the data to the mesh class

int getIntFromStringStream(const char* input)
{
    int integer;
    sscanf(input, "%d", &integer);
    return integer;
}

int FileLoader::LoadMeshFromOBJ(const char* filepath, Mesh& mesh)
{
    std::string line; std::ifstream meshFile(filepath);

    if (!meshFile.is_open())
        return -1;

    
    std::vector<Vector3f> vertexPositions;
    std::vector<Vector3f> vertexNormals;
    std::vector<Vector2f> vertexTextureCoordinates;

    Vector3f vertexPosition, vertexNormal;
    Vector2f vertexTextureCoordinate;

    int vertexPositionIndex = 0; int vertexNormalIndex = 0; int vertexTextureCoordinateIndex = 0;

    while (getline(meshFile, line))
    {
        std::istringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "f")
        {
            for (int i = 0; i < 3; i++)
            {
                std::cout << ss.str() << std::endl;
                // Subtract 1 because OBJ indices start from 1, not 0
                
                vertexPositionIndex = getIntFromStringStream(ss.getline();
                vertexTextureCoordinateIndex = getIntFromStringStream(ss);
                vertexNormalIndex = getIntFromStringStream(ss);

                //std::cout << vertexPositionIndex << std::endl << vertexTextureCoordinateIndex << std::endl << vertexNormalIndex << std::endl;

                Vertex vertex = Vertex(vertexPositions[vertexPositionIndex - 1], vertexNormals[vertexNormalIndex - 1], vertexTextureCoordinates[vertexTextureCoordinateIndex - 1]);
                mesh.vertexBuffer.push_back(vertex);
            }
        }

        else
        {
            if (type == "v")
            {
                ss >> vertexPosition.x; ss >> vertexPosition.y; ss >> vertexPosition.z;
                vertexPositions.push_back(vertexPosition);
            }
            else if (type == "vn")
            {
                ss >> vertexNormal.x; ss >> vertexNormal.y; ss >> vertexNormal.z;
                vertexNormals.push_back(vertexNormal);
            }
            else if (type == "vt")
            {
                ss >> vertexTextureCoordinate.x; ss >> vertexTextureCoordinate.y;
                vertexTextureCoordinates.push_back(vertexTextureCoordinate);
            }
        }
    }

    meshFile.close();
    return 0;
}
