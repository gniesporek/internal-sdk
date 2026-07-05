#pragma once
#include "../../renderer/renderer.h"

class PresentScene {
public:
    typedef HRESULT(__stdcall* oPresentSceneFn)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
    static inline oPresentSceneFn oPresentScene;
    static HRESULT __stdcall hkPresentScene(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
};

class CreateSwapChain {
public:
	typedef HRESULT(__stdcall* oCreateSwapChainFn)(IDXGIFactory* pFactory, IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain);
	static inline oCreateSwapChainFn oCreateSwapChain;
	static HRESULT __stdcall hkCreateSwapChain(IDXGIFactory* pFactory, IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain);
};

class ResizeBuffers {
public:
	typedef HRESULT(__stdcall* oResizeBuffersFn)(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
	static inline oResizeBuffersFn oResizeBuffers;
	static HRESULT __stdcall hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
};