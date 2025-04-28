#pragma once

#include "Vector2.h"
#include "Vector3.h"

struct Vertex {
    Vector3f position;
    Vector3f normal;
    Vector2f texcoord;

    bool operator==(const Vertex& other) const 
    {
        return (position == other.position) && (normal == other.normal) && (texcoord == other.texcoord);
    }
};

// We need a hash so that the unordered map in FileLoader::LoadMeshFromOBJ
// can check if the current vertex already has an instance stored in the unordered map
template<> struct std::hash<Vertex>
{
    size_t operator()(const Vertex& v) const
    {
        return hash<float>()(v.position.x) ^ hash<float>()(v.position.y) ^
            hash<float>()(v.position.z) ^ hash<float>()(v.normal.x) ^
            hash<float>()(v.normal.y) ^ hash<float>()(v.normal.z) ^
            hash<float>()(v.texcoord.x) ^ hash<float>()(v.texcoord.y);
    }
};