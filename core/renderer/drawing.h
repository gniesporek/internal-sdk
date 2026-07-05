#pragma once
#include <deque>
#include <shared_mutex>
#include <string>
#include <any>

#include "../../valve/structs/colors.h"

#include "../../valve/math/math.h"

#include "renderer.h"

enum class EDrawType {
    RECT, FILLED_RECT, GRADIENT_RECT,
    LINE, GRADIENT_LINE,
    TEXT, TEXT_OUTLINED, TEXT_SHADOW,
    IMAGE,
    TRIANGLE, FILLED_TRIANGLE,
    CIRCLE, FILLED_CIRCLE
};

struct RenderObject_t {
    EDrawType type;
    ImVec2 p1{}, p2{}, p3{};
    float radius{}, thickness{ 1.0f }, offset{ 1.0f };
    Colors col1{}, col2{};
    std::string text;
    ImFont* font = nullptr;
    ImTextureID texture = 0;
    bool centered = false;
    bool vertical = false;
    bool hasOutline = false;

    RenderObject_t(EDrawType t) : type(t) {}
};


class RenderStackSystem {
public:
    struct Rect {
        static void Draw(Vector2D pos, Vector2D size, Colors col);
        static void Draw(int x, int y, int w, int h, Colors col);
        static void Outline(Vector2D pos, Vector2D size, Colors col, Colors outline);
        static void Outline(int x, int y, int w, int h, Colors col, Colors outline);
        static void Fill(Vector2D pos, Vector2D size, Colors col);
        static void Fill(int x, int y, int w, int h, Colors col);
        static void Gradient(int x, int y, int w, int h, Colors c1, Colors c2, bool vertical = true);
    };

    struct Line {
        static void Draw(Vector2D start, Vector2D end, Colors col, float thickness = 1.0f);
        static void Draw(int x1, int y1, int x2, int y2, Colors col, float thickness = 1.0f);
        static void Gradient(Vector2D start, Vector2D end, Colors colStart, Colors colEnd, float thickness = 1.0f);
        static void Gradient(int x1, int y1, int x2, int y2, Colors colStart, Colors colEnd, float thickness = 1.0f);
    };

    struct Text {
        static void Draw(ImFont* font, Vector2D pos, const char* text, Colors col, bool centered = true);
        static void Draw(ImFont* font, int x, int y, const char* text, Colors col, bool centered = true);
        static void Outline(ImFont* font, Vector2D pos, const char* text, Colors colText, Colors colOutline, bool centered = true);
        static void Outline(ImFont* font, int x, int y, const char* text, Colors colText, Colors colOutline, bool centered = true);
        static void Shadow(ImFont* font, Vector2D pos, const char* text, Colors txt, Colors shadow, float offset = 1.f, bool centered = true);
        static void Shadow(ImFont* font, int x, int y, const char* text, Colors txt, Colors shadow, float offset = 1.f, bool centered = true);
        static int GetTextWidth(ImFont* font, const char* text);
        static int GetTextHeight(ImFont* font, const char* text);
        static int GetTextDimensions(ImFont* font, const char* text, bool width);
    };

    struct Triangle {
        static void Draw(Vector2D a, Vector2D b, Vector2D c, Colors col);
        static void Draw(int x1, int y1, int x2, int y2, int x3, int y3, Colors col);
        static void Fill(Vector2D a, Vector2D b, Vector2D c, Colors col);
        static void Fill(int x1, int y1, int x2, int y2, int x3, int y3, Colors col);
        static void Outline(Vector2D a, Vector2D b, Vector2D c, Colors col, Colors outline);
    };

    struct Circle {
        static void Draw(Vector2D pos, float radius, Colors col);
        static void Draw(int x, int y, float radius, Colors col);
        static void Fill(Vector2D pos, float radius, Colors col);
        static void Fill(int x, int y, float radius, Colors col);
        static void Outline(Vector2D pos, float radius, Colors col, Colors outline);
    };

    struct Image {
        static void Draw(ImTextureID texture, Vector2D pos, Vector2D size, Colors tint = { 255,255,255,255 });
        static void Draw(ImTextureID texture, int x, int y, int w, int h, Colors tint = { 255,255,255,255 });
        static void Outline(ImTextureID texture, Vector2D pos, Vector2D size, Colors tint, Colors outline);
        static void Outline(ImTextureID texture, int x, int y, int w, int h, Colors tint, Colors outline);
    };

    static void Clear();
    static void ClearDrawData();
    static void SwapDrawData();
    static void RenderDrawData(ImDrawList* pDrawList);

private:
    static inline std::deque<RenderObject_t> vecDrawData;
    static inline std::deque<RenderObject_t> vecSafeDrawData;
    static inline std::shared_mutex drawMutex;
};


class Draw {
public:
    class Rect {
    public:
        static void Outline(int x, int y, int width, int height, Colors color, Colors outlineColor);
        static void Fill(int x, int y, int width, int height, Colors color);
        static void Draw(int x, int y, int width, int height, Colors color);
        static void Outline(Vector2D position, Vector2D size, Colors color, Colors outlineColor);
        static void Fill(Vector2D position, Vector2D size, Colors color);
        static void Draw(Vector2D position, Vector2D size, Colors color);
    };

    class Line {
    public:
        static void Draw(Vector2D start, Vector2D end, Colors color, float thickness = 1.0f);
        static void Draw(int x1, int y1, int x2, int y2, Colors color, float thickness = 1.0f);
        static void Gradient(Vector2D start, Vector2D end, Colors startColor, Colors endColor, float thickness = 1.0f);
        static void Gradient(int x1, int y1, int x2, int y2, Colors startColor, Colors endColor, float thickness = 1.0f);
    };

    class Text {
    public:
        static void Draw(ImFont* font, Vector2D position, const char* text, Colors color, bool centered = false);
        static void Draw(ImFont* font, int x, int y, const char* text, Colors color, bool centered = false);
        static void Outline(ImFont* font, Vector2D position, const char* text, Colors colText, Colors colOutline, bool centered);
        static void Outline(ImFont* font, int x, int y, const char* text, Colors colText, Colors colOutline, bool centered);
        static int GetTextWidth(ImFont* font, const char* text);
        static int GetTextHeight(ImFont* font, const char* text);
        static void Shadow(ImFont* font, Vector2D position, const char* text, Colors textColor, Colors shadowColor, float offset = 1.0f, bool centered = false);
        static void Shadow(ImFont* font, int x, int y, const char* text, Colors textColor, Colors shadowColor, float offset = 1.0f, bool centered = false);
    private:
        static int GetTextDimensions(ImFont* font, const char* text, bool width);
    };

    class Image {
    public:
        static void Draw(ID3D11ShaderResourceView* texture, Vector2D position, Vector2D size, Colors tint = { 255,255,255,255 });
        static void Draw(ID3D11ShaderResourceView* texture, int x, int y, int width, int height, Colors tint = { 255,255,255,255 });
    };


    static Vector2D GetTextureSize(ID3D11ShaderResourceView* texture);

};