#pragma once

#include "CSceneNode.h"
//-------------------------------------
#include <vector>

//-------------------------------------
class CCamera;

using std::vector;

//-------------------------------------
struct Edge {
    uint32_t v1, v2;
};

//-------------------------------------
class CMesh : public CSceneNode {
public:
    void    Transform(CCamera &camera);

    vector<vec3>        mVertexPos;
    vector<vec3>        mVertexPosTrans;
    vector<vec3>        mVertexNormal;
    vector<vec2>        mVertexTextCoord;
    vector<uint32_t>    mVertexColor;

    vector<int32_t>     mIndices;
    vector<Edge>        mEdges;
};