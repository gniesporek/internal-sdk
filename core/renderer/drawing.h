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
    class Rect {
    public:
         void draw(Vector2D pos, Vector2D size, Colors col);
         void draw(int x, int y, int w, int h, Colors col);
         void outline(Vector2D pos, Vector2D size, Colors col, Colors outline);
         void outline(int x, int y, int w, int h, Colors col, Colors outline);
         void fill(Vector2D pos, Vector2D size, Colors col);
         void fill(int x, int y, int w, int h, Colors col);
         void gradient(int x, int y, int w, int h, Colors c1, Colors c2, bool vertical = true);
    };
	Rect rect;
    class Line {
    public:
         void draw(Vector2D start, Vector2D end, Colors col, float thickness = 1.0f);
         void draw(int x1, int y1, int x2, int y2, Colors col, float thickness = 1.0f);
         void gradient(Vector2D start, Vector2D end, Colors colStart, Colors colEnd, float thickness = 1.0f);
         void gradient(int x1, int y1, int x2, int y2, Colors colStart, Colors colEnd, float thickness = 1.0f);
    };
	Line line;
    class Text {
    public:
         void draw(ImFont* font, Vector2D pos, const char* text, Colors col, bool centered = true);
         void draw(ImFont* font, int x, int y, const char* text, Colors col, bool centered = true);
         void outline(ImFont* font, Vector2D pos, const char* text, Colors colText, Colors colOutline, bool centered = true);
         void outline(ImFont* font, int x, int y, const char* text, Colors colText, Colors colOutline, bool centered = true);
         void shadow(ImFont* font, Vector2D pos, const char* text, Colors txt, Colors shadow, float offset = 1.f, bool centered = true);
         void shadow(ImFont* font, int x, int y, const char* text, Colors txt, Colors shadow, float offset = 1.f, bool centered = true);
         int getTextWidth(ImFont* font, const char* text);
         int getTextHeight(ImFont* font, const char* text);
         int getTextDimensions(ImFont* font, const char* text, bool width);
    };
	Text text;
    class Triangle {
	public:
         void draw(Vector2D a, Vector2D b, Vector2D c, Colors col);
         void draw(int x1, int y1, int x2, int y2, int x3, int y3, Colors col);
         void fill(Vector2D a, Vector2D b, Vector2D c, Colors col);
         void fill(int x1, int y1, int x2, int y2, int x3, int y3, Colors col);
         void outline(Vector2D a, Vector2D b, Vector2D c, Colors col, Colors outline);
    };
	Triangle triangle;
    class Circle {
    public:
         void draw(Vector2D pos, float radius, Colors col);
         void draw(int x, int y, float radius, Colors col);
         void fill(Vector2D pos, float radius, Colors col);
         void fill(int x, int y, float radius, Colors col);
         void outline(Vector2D pos, float radius, Colors col, Colors outline);
    };
	Circle circle;

    class Image {
    public:
         void draw(ImTextureID texture, Vector2D pos, Vector2D size, Colors tint = { 255,255,255,255 });
         void draw(ImTextureID texture, int x, int y, int w, int h, Colors tint = { 255,255,255,255 });
         void outline(ImTextureID texture, Vector2D pos, Vector2D size, Colors tint, Colors outline);
         void outline(ImTextureID texture, int x, int y, int w, int h, Colors tint, Colors outline);
    };
	Image image;

    void clear();
    void clearDrawData();
    void swapDrawData();
    void renderDrawData(ImDrawList* pDrawList);

private:
    std::deque<RenderObject_t> vecDrawData;
    std::deque<RenderObject_t> vecSafeDrawData;
    std::shared_mutex drawMutex;
};
inline RenderStackSystem renderStackSystem;


class DrawingSystem // old system used for non thread safe drawing
{
public:
    class Rect {
    public:
        void outline(int x, int y, int width, int height, Colors color, Colors outlineColor);
        void fill(int x, int y, int width, int height, Colors color);
        void draw(int x, int y, int width, int height, Colors color);
        void outline(Vector2D position, Vector2D size, Colors color, Colors outlineColor);
        void fill(Vector2D position, Vector2D size, Colors color);
        void draw(Vector2D position, Vector2D size, Colors color);
    };
    Rect rect;

    class Line {
    public:
        void draw(Vector2D start, Vector2D end, Colors color, float thickness = 1.0f);
        void draw(int x1, int y1, int x2, int y2, Colors color, float thickness = 1.0f);
        void gradient(Vector2D start, Vector2D end, Colors startColor, Colors endColor, float thickness = 1.0f);
        void gradient(int x1, int y1, int x2, int y2, Colors startColor, Colors endColor, float thickness = 1.0f);
    };
	Line line;

    class Text {
    public:
        void draw(ImFont* font, Vector2D position, const char* text, Colors color, bool centered = false);
        void draw(ImFont* font, int x, int y, const char* text, Colors color, bool centered = false);
        void outline(ImFont* font, Vector2D position, const char* text, Colors colText, Colors colOutline, bool centered);
        void outline(ImFont* font, int x, int y, const char* text, Colors colText, Colors colOutline, bool centered);
        int getTextWidth(ImFont* font, const char* text);
        int getTextHeight(ImFont* font, const char* text);
        void shadow(ImFont* font, Vector2D position, const char* text, Colors textColor, Colors shadowColor, float offset = 1.0f, bool centered = false);
        void shadow(ImFont* font, int x, int y, const char* text, Colors textColor, Colors shadowColor, float offset = 1.0f, bool centered = false);
    private:
        int getTextDimensions(ImFont* font, const char* text, bool width);
    };
    Text text;

    class Image {
    public:
        void draw(ID3D11ShaderResourceView* texture, Vector2D position, Vector2D size, Colors tint = { 255,255,255,255 });
        void draw(ID3D11ShaderResourceView* texture, int x, int y, int width, int height, Colors tint = { 255,255,255,255 });
    };
	Image image;

    Vector2D getTextureSize(ID3D11ShaderResourceView* texture);
};
inline DrawingSystem drawingSystem;
