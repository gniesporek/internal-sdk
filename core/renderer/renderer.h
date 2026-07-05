#pragma once
#include "../../core/utils/utils.h"

#include "../../ext/imgui/imgui.h"
#include "../../ext/imgui/imgui_impl_win32.h"
#include "../../ext/imgui/imgui_impl_dx11.h"
#include "../../ext/imgui/imgui_freetype.h"

#include <d3d11.h>
#include <D3DX11.h>
#include <D3DX11tex.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib,"D3DX11.lib")

#include "drawing.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class WindowProcedure {
public:
	static inline WNDPROC gWndProc;
	static LRESULT CALLBACK hWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

class Fonts {
public:
	static inline const ImWchar fontRanges[] = {
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0100, 0x017F, // Latin Extended-A
		0x0180, 0x024F, // Latin Extended-B
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0xE000, 0xE226, // icons
		0,
	};
};
inline Fonts fonts;

class Renderer {
public:
	bool setup(IDXGISwapChain* pSwapChain);
	void destroy();
	void clearRenderTarget();
	void createRenderTarget(IDXGISwapChain* pSwapChain);
	void beginScene();
	void endScene();
	bool setupFonts();
	bool isRendererReady = false;
private:
	static inline IDXGISwapChain* pSwapChainGlobal;
	static inline ID3D11Device* pDevice;
	static inline ID3D11DeviceContext* pContext;
	static inline HWND hWnd;
	static inline ID3D11RenderTargetView* pRenderTargetView;
};
inline Renderer renderer;