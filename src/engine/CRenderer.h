#pragma once

#include <cstdint>

class CMesh;

//-------------------------------------
class CRenderer {
friend class CWindow;
public:
    void        Clear(uint8_t i = 0);
    uint32_t *  GetColorBuffer() const      { return mColorBuffer; }

    uint32_t    GetWidth() const            { return mWidth;       }
    uint32_t    GetHalfWidth() const        { return mWidth >> 1;  }
    uint32_t    GetHeight() const           { return mHeight;      }
    uint32_t    GetHalfHeight() const       { return mHeight >> 1; }

    float       GetAspectRatio() const      { return (mHeight > 0) ? float(mWidth)  / float(mHeight) : 1.0f; }
    float       GetAspectRatioInv() const   { return (mWidth  > 0) ? float(mHeight) / float(mWidth)  : 1.0f; }

private:
                CRenderer(uint32_t width, uint32_t height);
                CRenderer(const CRenderer &)    = delete;
                CRenderer(CRenderer &&)         = delete;
                ~CRenderer();

    CRenderer & operator = (const CRenderer &)  = delete;
    CRenderer & operator = (CRenderer &&)       = delete;

protected:
    uint32_t        *mColorBuffer { nullptr };
    uint32_t        mWidth        { 0 };
    uint32_t        mHeight       { 0 };

};
