#include "drawing.h"

inline ImVec2 ToVec(Vector2D v) { return ImVec2(v.x, v.y); }
inline ImVec2 ToVec(int x, int y) { return ImVec2((float)x, (float)y); }

void RenderStackSystem::Clear() {
    std::unique_lock lock(drawMutex);
    vecDrawData.clear(); vecSafeDrawData.clear();
}
void RenderStackSystem::ClearDrawData() {
    std::unique_lock lock(drawMutex);
    vecDrawData.clear();
}
void RenderStackSystem::SwapDrawData() {
    std::unique_lock lock(drawMutex);
    vecSafeDrawData = std::move(vecDrawData);
    vecDrawData.clear();
}

void RenderStackSystem::RenderDrawData(ImDrawList* pDrawList) {
    std::unique_lock lock(drawMutex);
    if (vecSafeDrawData.empty()) return;

    for (const auto& o : vecSafeDrawData) {
        switch (o.type) {
        case EDrawType::RECT:
            pDrawList->AddRect(o.p1, o.p2, o.col1.ToImColor());
            if (o.hasOutline) {
                pDrawList->AddRect(ImVec2(o.p1.x - 1, o.p1.y - 1), ImVec2(o.p2.x + 1, o.p2.y + 1), o.col2.ToImColor());
                pDrawList->AddRect(ImVec2(o.p1.x + 1, o.p1.y + 1), ImVec2(o.p2.x - 1, o.p2.y - 1), o.col2.ToImColor());
            } break;
        case EDrawType::FILLED_RECT:
            pDrawList->AddRectFilled(o.p1, o.p2, o.col1.ToImColor()); break;
        case EDrawType::LINE: {
            int old = pDrawList->Flags; pDrawList->Flags &= ~ImDrawListFlags_AntiAliasedLines;
            pDrawList->AddLine(o.p1, o.p2, o.col1.ToImColor(), o.thickness);
            pDrawList->Flags = old;
        } break;
        case EDrawType::TEXT:
        case EDrawType::TEXT_OUTLINED:
        case EDrawType::TEXT_SHADOW: {
            if (!o.font || o.text.empty()) break;
            ImGui::PushFont(o.font);
            ImVec2 pos = o.p1;
            if (o.centered) {
                ImVec2 s = ImGui::CalcTextSize(o.text.c_str());
                pos.x -= s.x * 0.5f; pos.y -= s.y * 0.5f;
            }
            if (o.type == EDrawType::TEXT_OUTLINED) {
                for (int x = -1; x <= 1; x++) for (int y = -1; y <= 1; y++)
                    if (x || y) pDrawList->AddText(ImVec2(pos.x + x, pos.y + y), o.col2.ToImColor(), o.text.c_str());
            }
            else if (o.type == EDrawType::TEXT_SHADOW) {
                pDrawList->AddText(ImVec2(pos.x + o.offset, pos.y + o.offset), o.col2.ToImColor(), o.text.c_str());
            }
            pDrawList->AddText(pos, o.col1.ToImColor(), o.text.c_str());
            ImGui::PopFont();
        } break;
        case EDrawType::CIRCLE: {
            int seg = Math::CalculateSegments(o.radius);
            if (o.hasOutline) pDrawList->AddCircle(o.p1, o.radius + 1.0f, o.col2.ToImColor(), seg, 1.0f);
            pDrawList->AddCircle(o.p1, o.radius, o.col1.ToImColor(), seg, 1.0f);
        } break;
        case EDrawType::FILLED_CIRCLE:
            pDrawList->AddCircleFilled(o.p1, o.radius, o.col1.ToImColor(), Math::CalculateSegments(o.radius)); break;
        case EDrawType::TRIANGLE:
            pDrawList->AddTriangle(o.p1, o.p2, o.p3, o.col1.ToImColor());
            if (o.hasOutline) pDrawList->AddTriangle(ImVec2(o.p1.x - 1, o.p1.y - 1), ImVec2(o.p2.x - 1, o.p2.y - 1), ImVec2(o.p3.x - 1, o.p3.y - 1), o.col2.ToImColor());
            break;
        case EDrawType::FILLED_TRIANGLE:
            pDrawList->AddTriangleFilled(o.p1, o.p2, o.p3, o.col1.ToImColor()); break;
        case EDrawType::IMAGE:
            if (o.hasOutline) {
                for (int x = -1; x <= 1; x++) for (int y = -1; y <= 1; y++)
                    if (x || y) pDrawList->AddImage(o.texture, ImVec2(o.p1.x + x, o.p1.y + y), ImVec2(o.p2.x + x, o.p2.y + y), { 0,0 }, { 1,1 }, o.col2.ToImColor());
            }
            pDrawList->AddImage(o.texture, o.p1, o.p2, { 0,0 }, { 1,1 }, o.col1.ToImColor()); break;
        case EDrawType::GRADIENT_RECT: {
            ImU32 c1 = o.col1.ToImColor(), c2 = o.col2.ToImColor();
            pDrawList->AddRectFilledMultiColor(o.p1, o.p2, c1, o.vertical ? c1 : c2, c2, o.vertical ? c2 : c1);
        } break;
        case EDrawType::GRADIENT_LINE: {
            Vector2D s{ o.p1.x, o.p1.y }, e{ o.p2.x, o.p2.y };
            int segs = (int)(e - s).Length(); if (segs <= 0) segs = 1;
            for (int i = 0; i < segs; ++i) {
                float t1 = (float)i / segs, t2 = (float)(i + 1) / segs;
                Vector2D p1 = s + (e - s) * t1, p2 = s + (e - s) * t2;
                Colors c;
                c.r = o.col1.r + (o.col2.r - o.col1.r) * t1; c.g = o.col1.g + (o.col2.g - o.col1.g) * t1;
                c.b = o.col1.b + (o.col2.b - o.col1.b) * t1; c.a = o.col1.a + (o.col2.a - o.col1.a) * t1;
                pDrawList->AddLine(ToVec(p1), ToVec(p2), c.ToImColor(), o.thickness);
            }
        } break;
        }
    }
}

void RenderStackSystem::Rect::Draw(Vector2D p, Vector2D s, Colors c) { RenderObject_t o(EDrawType::RECT); o.p1 = ToVec(p); o.p2 = ToVec(p.x + s.x, p.y + s.y); o.col1 = c; vecDrawData.push_back(o); }
void RenderStackSystem::Rect::Draw(int x, int y, int w, int h, Colors c) { Rect::Draw({ (float)x,(float)y }, { (float)w,(float)h }, c); }
void RenderStackSystem::Rect::Outline(Vector2D p, Vector2D s, Colors c, Colors out) { RenderObject_t o(EDrawType::RECT); o.p1 = ToVec(p); o.p2 = ToVec(p.x + s.x, p.y + s.y); o.col1 = c; o.col2 = out; o.hasOutline = true; vecDrawData.push_back(o); }
void RenderStackSystem::Rect::Outline(int x, int y, int w, int h, Colors c, Colors out) { Rect::Outline({ (float)x,(float)y }, { (float)w,(float)h }, c, out); }
void RenderStackSystem::Rect::Fill(Vector2D p, Vector2D s, Colors c) { RenderObject_t o(EDrawType::FILLED_RECT); o.p1 = ToVec(p); o.p2 = ToVec(p.x + s.x, p.y + s.y); o.col1 = c; vecDrawData.push_back(o); }
void RenderStackSystem::Rect::Fill(int x, int y, int w, int h, Colors c) { Rect::Fill({ (float)x,(float)y }, { (float)w,(float)h }, c); }
void RenderStackSystem::Rect::Gradient(int x, int y, int w, int h, Colors c1, Colors c2, bool v) { RenderObject_t o(EDrawType::GRADIENT_RECT); o.p1 = ToVec(x, y); o.p2 = ToVec(x + w, y + h); o.col1 = c1; o.col2 = c2; o.vertical = v; vecDrawData.push_back(o); }

void RenderStackSystem::Line::Draw(Vector2D s, Vector2D e, Colors c, float t) { RenderObject_t o(EDrawType::LINE); o.p1 = ToVec(s); o.p2 = ToVec(e); o.col1 = c; o.thickness = t; vecDrawData.push_back(o); }
void RenderStackSystem::Line::Draw(int x1, int y1, int x2, int y2, Colors c, float t) { Line::Draw({ (float)x1,(float)y1 }, { (float)x2,(float)y2 }, c, t); }
void RenderStackSystem::Line::Gradient(Vector2D s, Vector2D e, Colors c1, Colors c2, float t) { RenderObject_t o(EDrawType::GRADIENT_LINE); o.p1 = ToVec(s); o.p2 = ToVec(e); o.col1 = c1; o.col2 = c2; o.thickness = t; vecDrawData.push_back(o); }
void RenderStackSystem::Line::Gradient(int x1, int y1, int x2, int y2, Colors c1, Colors c2, float t) { Line::Gradient({ (float)x1,(float)y1 }, { (float)x2,(float)y2 }, c1, c2, t); }

void RenderStackSystem::Text::Draw(ImFont* f, Vector2D p, const char* t, Colors c, bool cent) { RenderObject_t o(EDrawType::TEXT); o.font = f; o.p1 = ToVec(p); o.text = t; o.col1 = c; o.centered = cent; vecDrawData.push_back(o); }
void RenderStackSystem::Text::Draw(ImFont* f, int x, int y, const char* t, Colors c, bool cent) { Text::Draw(f, { (float)x,(float)y }, t, c, cent); }
void RenderStackSystem::Text::Outline(ImFont* f, Vector2D p, const char* t, Colors c, Colors out, bool cent) { RenderObject_t o(EDrawType::TEXT_OUTLINED); o.font = f; o.p1 = ToVec(p); o.text = t; o.col1 = c; o.col2 = out; o.centered = cent; vecDrawData.push_back(o); }
void RenderStackSystem::Text::Outline(ImFont* f, int x, int y, const char* t, Colors c, Colors out, bool cent) { Text::Outline(f, { (float)x,(float)y }, t, c, out, cent); }
void RenderStackSystem::Text::Shadow(ImFont* f, Vector2D p, const char* t, Colors c, Colors s, float off, bool cent) { RenderObject_t o(EDrawType::TEXT_SHADOW); o.font = f; o.p1 = ToVec(p); o.text = t; o.col1 = c; o.col2 = s; o.offset = off; o.centered = cent; vecDrawData.push_back(o); }
void RenderStackSystem::Text::Shadow(ImFont* f, int x, int y, const char* t, Colors c, Colors s, float off, bool cent) { Text::Shadow(f, { (float)x,(float)y }, t, c, s, off, cent); }
int RenderStackSystem::Text::GetTextDimensions(ImFont* f, const char* t, bool w) { if (!f || !t || !*t) return 0; ImVec2 s = f->CalcTextSizeA(f->LegacySize, FLT_MAX, 0.0f, t); return w ? (int)s.x : (int)s.y; }
int RenderStackSystem::Text::GetTextWidth(ImFont* f, const char* t) { return GetTextDimensions(f, t, true); }
int RenderStackSystem::Text::GetTextHeight(ImFont* f, const char* t) { return GetTextDimensions(f, t, false); }

void RenderStackSystem::Triangle::Draw(Vector2D a, Vector2D b, Vector2D c, Colors col) { RenderObject_t o(EDrawType::TRIANGLE); o.p1 = ToVec(a); o.p2 = ToVec(b); o.p3 = ToVec(c); o.col1 = col; vecDrawData.push_back(o); }
void RenderStackSystem::Triangle::Draw(int x1, int y1, int x2, int y2, int x3, int y3, Colors c) { Triangle::Draw({ (float)x1,(float)y1 }, { (float)x2,(float)y2 }, { (float)x3,(float)y3 }, c); }
void RenderStackSystem::Triangle::Fill(Vector2D a, Vector2D b, Vector2D c, Colors col) { RenderObject_t o(EDrawType::FILLED_TRIANGLE); o.p1 = ToVec(a); o.p2 = ToVec(b); o.p3 = ToVec(c); o.col1 = col; vecDrawData.push_back(o); }
void RenderStackSystem::Triangle::Fill(int x1, int y1, int x2, int y2, int x3, int y3, Colors c) { Triangle::Fill({ (float)x1,(float)y1 }, { (float)x2,(float)y2 }, { (float)x3,(float)y3 }, c); }
void RenderStackSystem::Triangle::Outline(Vector2D a, Vector2D b, Vector2D c, Colors col, Colors out) { RenderObject_t o(EDrawType::TRIANGLE); o.p1 = ToVec(a); o.p2 = ToVec(b); o.p3 = ToVec(c); o.col1 = col; o.col2 = out; o.hasOutline = true; vecDrawData.push_back(o); }

void RenderStackSystem::Circle::Draw(Vector2D p, float r, Colors c) { RenderObject_t o(EDrawType::CIRCLE); o.p1 = ToVec(p); o.radius = r; o.col1 = c; vecDrawData.push_back(o); }
void RenderStackSystem::Circle::Draw(int x, int y, float r, Colors c) { Circle::Draw({ (float)x,(float)y }, r, c); }
void RenderStackSystem::Circle::Fill(Vector2D p, float r, Colors c) { RenderObject_t o(EDrawType::FILLED_CIRCLE); o.p1 = ToVec(p); o.radius = r; o.col1 = c; vecDrawData.push_back(o); }
void RenderStackSystem::Circle::Fill(int x, int y, float r, Colors c) { Circle::Fill({ (float)x,(float)y }, r, c); }
void RenderStackSystem::Circle::Outline(Vector2D p, float r, Colors c, Colors out) { RenderObject_t o(EDrawType::CIRCLE); o.p1 = ToVec(p); o.radius = r; o.col1 = c; o.col2 = out; o.hasOutline = true; vecDrawData.push_back(o); }

void RenderStackSystem::Image::Draw(ImTextureID t, Vector2D p, Vector2D s, Colors tint) { RenderObject_t o(EDrawType::IMAGE); o.texture = t; o.p1 = ToVec(p); o.p2 = ToVec(p.x + s.x, p.y + s.y); o.col1 = tint; vecDrawData.push_back(o); }
void RenderStackSystem::Image::Draw(ImTextureID t, int x, int y, int w, int h, Colors tint) { Image::Draw(t, { (float)x,(float)y }, { (float)w,(float)h }, tint); }
void RenderStackSystem::Image::Outline(ImTextureID t, Vector2D p, Vector2D s, Colors tint, Colors out) { RenderObject_t o(EDrawType::IMAGE); o.texture = t; o.p1 = ToVec(p); o.p2 = ToVec(p.x + s.x, p.y + s.y); o.col1 = tint; o.col2 = out; o.hasOutline = true; vecDrawData.push_back(o); }
void RenderStackSystem::Image::Outline(ImTextureID t, int x, int y, int w, int h, Colors tint, Colors out) { Image::Outline(t, { (float)x,(float)y }, { (float)w,(float)h }, tint, out); }


// Immediate mode drawing functions (for compatibility with older code, not thread-safe)

void Draw::Rect::Outline(int x, int y, int width, int height, Colors color, Colors outlineColor) {
    auto draw = ImGui::GetBackgroundDrawList();
    draw->AddRect(ImVec2(x, y), ImVec2(x + width, y + height), color.ToImColor());
    draw->AddRect(ImVec2(x - 1, y - 1), ImVec2(x + width + 1, y + height + 1), outlineColor.ToImColor());
    draw->AddRect(ImVec2(x + 1, y + 1), ImVec2(x + width - 1, y + height - 1), outlineColor.ToImColor());
}

void Draw::Rect::Fill(int x, int y, int width, int height, Colors color) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + width, y + height), color.ToImColor());
}

void Draw::Rect::Draw(int x, int y, int width, int height, Colors color) {
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + width, y + height), color.ToImColor());
}

void Draw::Rect::Outline(Vector2D position, Vector2D size, Colors color, Colors outlineColor) {
    Outline((int)position.x, (int)position.y, (int)size.x, (int)size.y, color, outlineColor);
}

void Draw::Rect::Fill(Vector2D position, Vector2D size, Colors color) {
    Fill((int)position.x, (int)position.y, (int)size.x, (int)size.y, color);
}

void Draw::Rect::Draw(Vector2D position, Vector2D size, Colors color) {
    Draw((int)position.x, (int)position.y, (int)size.x, (int)size.y, color);
}

void Draw::Line::Draw(Vector2D start, Vector2D end, Colors color, float thickness) {
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(start.x, start.y), ImVec2(end.x, end.y), color.ToImColor(), thickness);
}

void Draw::Line::Draw(int x1, int y1, int x2, int y2, Colors color, float thickness) {
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2((float)x1, (float)y1), ImVec2((float)x2, (float)y2), color.ToImColor(), thickness);
}

void Draw::Line::Gradient(Vector2D start, Vector2D end, Colors startColor, Colors endColor, float thickness) {
    int segments = static_cast<int>((end - start).Length());
    if (segments <= 0) segments = 1;

    auto draw = ImGui::GetBackgroundDrawList();
    for (int i = 0; i < segments; ++i) {
        float t1 = (float)i / segments;
        float t2 = (float)(i + 1) / segments;
        Vector2D p1 = start + (end - start) * t1;
        Vector2D p2 = start + (end - start) * t2;

        Colors col;
        col.r = (int)(startColor.r + (endColor.r - startColor.r) * t1);
        col.g = (int)(startColor.g + (endColor.g - startColor.g) * t1);
        col.b = (int)(startColor.b + (endColor.b - startColor.b) * t1);
        col.a = (int)(startColor.a + (endColor.a - startColor.a) * t1);

        draw->AddLine(ImVec2(p1.x, p1.y), ImVec2(p2.x, p2.y), col.ToImColor(), thickness);
    }
}

void Draw::Line::Gradient(int x1, int y1, int x2, int y2, Colors startColor, Colors endColor, float thickness) {
    Gradient(Vector2D{ (float)x1, (float)y1 }, Vector2D{ (float)x2, (float)y2 }, startColor, endColor, thickness);
}

void Draw::Text::Draw(ImFont* font, Vector2D position, const char* text, Colors color, bool centered) {
    if (!font || !text) return;
    ImGui::PushFont(font);
    ImVec2 textSize = ImGui::CalcTextSize(text);
    ImVec2 pos = centered ? ImVec2(position.x - textSize.x / 2.f, position.y - textSize.y / 2.f) : ImVec2(position.x, position.y);
    ImGui::GetBackgroundDrawList()->AddText(pos, color.ToImColor(), text);
    ImGui::PopFont();
}

void Draw::Text::Draw(ImFont* font, int x, int y, const char* text, Colors color, bool centered) {
    Draw(font, Vector2D{ (float)x, (float)y }, text, color, centered);
}

void Draw::Text::Outline(ImFont* font, Vector2D position, const char* text, Colors colText, Colors colOutline, bool centered) {
    if (!font || !text) return;
    ImGui::PushFont(font);
    ImVec2 textSize = ImGui::CalcTextSize(text);
    ImVec2 pos = centered ? ImVec2(position.x - textSize.x / 2.f, position.y - textSize.y / 2.f) : ImVec2(position.x, position.y);

    auto draw = ImGui::GetBackgroundDrawList();
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i != 0 || j != 0)
                draw->AddText(ImVec2(pos.x + i, pos.y + j), colOutline.ToImColor(), text);
        }
    }
    draw->AddText(pos, colText.ToImColor(), text);
    ImGui::PopFont();
}

void Draw::Text::Outline(ImFont* font, int x, int y, const char* text, Colors colText, Colors colOutline, bool centered) {
    Outline(font, Vector2D{ (float)x, (float)y }, text, colText, colOutline, centered);
}

void Draw::Text::Shadow(ImFont* font, Vector2D position, const char* text, Colors textColor, Colors shadowColor, float offset, bool centered) {
    if (!font || !text) return;
    ImGui::PushFont(font);
    ImVec2 textSize = ImGui::CalcTextSize(text);
    ImVec2 pos = centered ? ImVec2(position.x - textSize.x / 2.f, position.y - textSize.y / 2.f) : ImVec2(position.x, position.y);

    auto draw = ImGui::GetBackgroundDrawList();
    draw->AddText(ImVec2(pos.x + offset, pos.y + offset), shadowColor.ToImColor(), text);
    draw->AddText(pos, textColor.ToImColor(), text);
    ImGui::PopFont();
}

void Draw::Text::Shadow(ImFont* font, int x, int y, const char* text, Colors textColor, Colors shadowColor, float offset, bool centered) {
    Shadow(font, Vector2D{ (float)x, (float)y }, text, textColor, shadowColor, offset, centered);
}

int Draw::Text::GetTextDimensions(ImFont* font, const char* text, bool width) {
    if (!font || !text || !*text) return 0;
    ImVec2 size = font->CalcTextSizeA(font->LegacySize, FLT_MAX, 0.0f, text);
    return width ? (int)size.x : (int)size.y;
}

int Draw::Text::GetTextWidth(ImFont* font, const char* text) {
    return GetTextDimensions(font, text, true);
}

int Draw::Text::GetTextHeight(ImFont* font, const char* text) {
    return GetTextDimensions(font, text, false);
}

void Draw::Image::Draw(ID3D11ShaderResourceView* texture, Vector2D position, Vector2D size, Colors tint) {
    if (!texture) return;

    Vector2D tex_size = GetTextureSize(texture);
    if (tex_size.x == 0 || tex_size.y == 0) return;

    ImVec2 uv_max = ImVec2(size.x / tex_size.x, size.y / tex_size.y);

    ImGui::GetBackgroundDrawList()->AddImage(texture, ImVec2(position.x, position.y), ImVec2(position.x + size.x, position.y + size.y), ImVec2(0, 0), uv_max, tint.ToImColor());
}

void Draw::Image::Draw(ID3D11ShaderResourceView* texture, int x, int y, int width, int height, Colors tint) {
    Draw(texture, Vector2D{ (float)x, (float)y }, Vector2D{ (float)width, (float)height }, tint);
}

Vector2D Draw::GetTextureSize(ID3D11ShaderResourceView* texture)
{
    if (!texture) return Vector2D{ 0, 0 };
    ID3D11Resource* resource = nullptr;
    texture->GetResource(&resource);
    if (!resource) return Vector2D{ 0, 0 };
    D3D11_RESOURCE_DIMENSION dimension;
    resource->GetType(&dimension);
    if (dimension != D3D11_RESOURCE_DIMENSION_TEXTURE2D) {
        resource->Release();
        return Vector2D{ 0, 0 };
    }
    ID3D11Texture2D* tex2D = static_cast<ID3D11Texture2D*>(resource);
    D3D11_TEXTURE2D_DESC desc;
    tex2D->GetDesc(&desc);
    resource->Release();
    return Vector2D{ (float)desc.Width, (float)desc.Height };
}
