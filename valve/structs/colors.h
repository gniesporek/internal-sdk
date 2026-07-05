#include <cstdint>
#include <d3dx9.h>

#include "../../ext/imgui/imgui.h"

class Colors {
public:
    int r = 255, g = 255, b = 255, a = 255;

    Colors() = default;
    Colors(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}

    Colors(uint32_t color) {
        a = (color >> 24) & 0xFF;
        r = (color >> 16) & 0xFF;
        g = (color >> 8) & 0xFF;
        b = (color) & 0xFF;
    }

    static Colors FromUint(uint32_t color) {
        return Colors(color);
    }

    uint32_t ToD3DColor() const {
        return D3DCOLOR_ARGB(a, r, g, b);
    }

    ImColor ToImColor() const {
        return ImColor(r, g, b, a);
    }

    static Colors White(int alpha = 255) { return { 255, 255, 255, alpha }; }
    static Colors Black(int alpha = 255) { return { 0, 0, 0, alpha }; }

    static Colors HSVtoRGB(float h, float s, float v, int a = 255)
    {
        float c = v * s;
        float x = c * (1 - fabsf(fmodf(h / 60.f, 2) - 1));
        float m = v - c;

        float r1, g1, b1;

        if (h < 60) { r1 = c; g1 = x; b1 = 0; }
        else if (h < 120) { r1 = x; g1 = c; b1 = 0; }
        else if (h < 180) { r1 = 0; g1 = c; b1 = x; }
        else if (h < 240) { r1 = 0; g1 = x; b1 = c; }
        else if (h < 300) { r1 = x; g1 = 0; b1 = c; }
        else { r1 = c; g1 = 0; b1 = x; }

        return Colors(int((r1 + m) * 255), int((g1 + m) * 255), int((b1 + m) * 255), a);
    }

    static void RGBtoHSV(const Colors& c, float& h, float& s, float& v)
    {
        float r = c.r / 255.f;
        float g = c.g / 255.f;
        float b = c.b / 255.f;

        float max = r;
        if (g > max) max = g;
        if (b > max) max = b;

        float min = r;
        if (g < min) min = g;
        if (b < min) min = b;

        float delta = max - min;

        v = max;

        if (max == 0.f)
            s = 0.f;
        else
            s = delta / max;

        if (delta == 0.f)
        {
            h = 0.f;
        }
        else if (max == r)
        {
            h = 60.f * fmodf((g - b) / delta, 6.f);
        }
        else if (max == g)
        {
            h = 60.f * ((b - r) / delta + 2.f);
        }
        else
        {
            h = 60.f * ((r - g) / delta + 4.f);
        }

        if (h < 0.f)
            h += 360.f;
    }

};