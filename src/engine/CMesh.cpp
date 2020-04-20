#include "CMesh.h"
//-------------------------------------
#include <engine/CCamera.h>
//-------------------------------------
#include <Common/Math/constants.h>

using namespace MindShake;

//-------------------------------------
void
CMesh::Transform(CCamera &camera) {
    size_t  i, size;
    float   viewX, viewY, viewHalfWidth, viewHalfHeight;

    viewX          = float(camera.GetViewportX());
    viewY          = float(camera.GetViewportY());
    viewHalfWidth  = float(camera.GetViewportWidth()  >> 1);
    viewHalfHeight = float(camera.GetViewportHeight() >> 1);

    size = mVertexPos.size();
    if(mVertexPosTrans.size() != size)
        mVertexPosTrans.resize(size);

    vec4    aux(1), tmp;
    mat4    mvp = camera.GetViewProjectionMatrix() * GetMatrixWorld();
    for(i=0; i<size; ++i) {
        const vec3 &pos = mVertexPos[i];
        vec3 &trans = mVertexPosTrans[i];

        aux.x = pos.x;
        aux.y = pos.y;
        aux.z = pos.z;
        // Clip coordinates
        tmp = mvp * aux;
        if (tmp.w != 0) {
            float invW = 1.0f / tmp.w;

            // Normalized Device Coordinates (NDC)
            trans = vec3(tmp.x * invW, tmp.y * invW, tmp.z * invW);

            // Window Coordinates (Screen Coordinates)
            trans.x = (trans.x + 1) * viewHalfWidth  + viewX;
            trans.y = (trans.y + 1) * viewHalfHeight + viewY;
            // let Z as z/w
        }
        else {
            trans.z = Float32::POS_INFINITY;
        }
    }
}