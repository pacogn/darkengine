#include "CRenderer.h"
//-------------------------------------
#include <Core/memory/memory.h>
//-------------------------------------
#include <memory.h>

using namespace MindShake;

//-------------------------------------
CRenderer::CRenderer(uint32_t width, uint32_t height) {
    mWidth       = width;
    mHeight      = height;

    mColorBuffer = (uint32_t *) AlignedMalloc(width * height * sizeof(uint32_t), 64);
}

//-------------------------------------
CRenderer::~CRenderer() {
    if(mColorBuffer != nullptr) {
        AlignedFree(mColorBuffer);
    }
}

//-------------------------------------
void
CRenderer::Clear(uint8_t i) {
    memset(mColorBuffer, i, mWidth * mHeight * 4);
}
