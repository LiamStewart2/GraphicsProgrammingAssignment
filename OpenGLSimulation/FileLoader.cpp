#include "FileLoader.h"

/// LoadMeshFromOBJ
/// will load a mesh from an obj file, using string streams to read each line
/// and push the data to the mesh class

std::vector<int> getIntegersFromStringStream(std::string input, const char division)
{
    std::vector<int> integers;

    int value = 0; int digit = 0;

    for (int i = input.size() - 1; i >= 0; i--)
    {
        if (input[i] != division)
        {
            int digitValue = (int)(input[i] - '0');
            if (digit != 0)
                digitValue *= std::pow(10, digit);
            value += digitValue;
            digit += 1;
        }
        else
        {
            integers.push_back(value);
            value = 0; digit = 0;
        }
    }
    integers.push_back(value);
    return integers;
}

int FileLoader::LoadMeshFromOBJ(const char* filepath, Mesh& mesh)
{
    std::string line; std::ifstream meshFile(filepath);
    if (!meshFile.is_open())
    {
        std::cerr << "Issue with OBJ file " << filepath << std::endl;
        return -1;
    }

    Vector3f vertexPosition; Vector3f vertexNormal; Vector2f vertexTextureCoordinate;

    std::vector<Vector3f> vertexPositions;
    std::vector<Vector3f> vertexNormals;
    std::vector<Vector2f> vertexTextureCoordinates;

    // use an unordered map to make sure vertexes arent duplicated
    std::unordered_map<Vertex, unsigned int> vertices;

    while (getline(meshFile, line))
    {
        std::istringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "f")
        {
            for (int i = 0; i < 3; i++)
            {
                // Subtract 1 because OBJ indices start from 1, not 0
                
                std::string vertexString;
                ss >> vertexString;
                std::vector<int> indexes = getIntegersFromStringStream(vertexString, '/');

                Vertex vertex = {vertexPositions[indexes[2] - 1], vertexNormals[indexes[0] - 1], vertexTextureCoordinates[indexes[1] - 1]};

                if (vertices.count(vertex) == 0) 
                {
                    vertices[vertex] = mesh.vertexPositions.size();

                    mesh.vertexPositions.push_back(vertex.position);
                    mesh.vertexNormals.push_back(vertex.normal);
                    mesh.vertexTextureCoordinates.push_back(vertex.texcoord);
                }

                mesh.faces.push_back(vertices[vertex]);
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


/// LoadTextureFromRAW
/// loads the image texture from a RAW file
/// width and height are required as the only data in a raw file is the colour

int FileLoader::LoadTextureFromRAW(const char* filepath, int width, int height, Texture& texture)
{
    char* tempTextureData; int filesize; std::ifstream textureFile;
    texture.width = width; texture.height = height;

    textureFile.open(filepath, std::ios::binary);
    if (!textureFile.is_open())
    {
        std::cerr << "Issue with texture file " << filepath << std::endl;
        return -1;
    }

    textureFile.seekg(0, std::ios::end);
    filesize = (int)textureFile.tellg();
    tempTextureData = new char[filesize];

    textureFile.seekg(0, std::ios::beg);
    textureFile.read(tempTextureData, filesize);
    textureFile.close();

    texture.BindDataToTexture(tempTextureData);
    
    delete[] tempTextureData;

    return 0;
}

/// LoadTextureFromBMP
/// loads the image texture from a BMP file

struct BitmapFileFt
{
    unsigned char magic[2];
};

struct BitmapFileHeader
{
    uint32_t filesz;
    uint16_t creator1;
    uint16_t creator2;
    uint32_t bmp_offset;
};

struct BitmapInfoHeader
{
    uint32_t header_sz;
    int32_t width;
    int32_t height;
    uint16_t nplanes;
    uint16_t bitspp;
    uint32_t compress_type;
    uint32_t bmp_bytesz;
    int32_t hres;
    int32_t vres;
    uint32_t ncolors;
    uint32_t nimpcolors;
};

struct BitmapColor
{
    unsigned char b, g, r;
};

int FileLoader::LoadTextureFromBMP(const char* filepath, Texture& texture)
{
    BitmapInfoHeader bitmapInfo;
    BitmapFileFt magic;
    BitmapFileHeader head;

    unsigned char* textureImageBuffer;

    FILE* file; fopen_s(&file, filepath, "rb");

    if (file == NULL)
    {
        std::cerr << "Issue with texture file " << filepath << std::endl;
        return -1;
    }

    //reads in the bitmap file foot
    fread(&magic, sizeof(BitmapFileFt), 1, file);
    //the bitmap file header
    fread(&head, sizeof(BitmapFileHeader), 1, file);
    //the bitmap info header,  which contains information such as width and height
    fread(&bitmapInfo, sizeof(BitmapInfoHeader), 1, file);

    if (bitmapInfo.width != bitmapInfo.height)
    {
        std::cerr << "Invalid texture file " << filepath << " - not square" << std::endl;
        return -1;
    }

    // allocate enough memory to load the entire colour buffer in
    textureImageBuffer = new unsigned char[bitmapInfo.width * bitmapInfo.height * 3];

    texture.width = bitmapInfo.width; texture.height = bitmapInfo.height;

    fread(textureImageBuffer, 1, bitmapInfo.width * bitmapInfo.height * 3, file);

    // bind the data of the texture to the OpenGL instance of the texture
    texture.BindDataToTexture(textureImageBuffer);

    delete[] textureImageBuffer;
    fclose(file);

    return 0;
}
