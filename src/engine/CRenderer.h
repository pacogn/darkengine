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

    virtual void Draw(int32_t x, int32_t y, uint32_t color);
    bool        SetPixel(int32_t x, int32_t y, uint32_t color);
    void        DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color = 0xFFFFFFFF, uint32_t pattern = 0xFFFFFFFF);
    void        DrawRectangle(int32_t x, int32_t y, int32_t width, int32_t height, uint32_t color = 0xFFFFFFFF, uint32_t pattern = 0xFFFFFFFF);

    //TODO: move somewhere else... but where?! CRenderer is going to bee way too crowded
    void WrapCoordinates(float ix, float iy, float &ox, float &oy);

private:
    CRenderer(uint32_t width, uint32_t height);
    CRenderer(const CRenderer &) = delete;
    CRenderer(CRenderer &&) = delete;
    ~CRenderer();

    CRenderer & operator = (const CRenderer &)  = delete;
    CRenderer & operator = (CRenderer &&)       = delete;

protected:
    uint32_t        *mColorBuffer { nullptr };
    uint32_t        mWidth        { 0 };
    uint32_t        mHeight       { 0 };
};
