#include <cstdint>

union ColorI {
    ColorI() = default;
    // ColorI(const ColorF &col);
    ColorI(uint32_t col) : color(col) {}
    operator uint32_t() const { return color; }
    uint32_t color;
    struct
    {
        uint8_t b, g, r, a;
    };
};