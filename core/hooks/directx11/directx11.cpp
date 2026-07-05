#include "../hooks.h"

HRESULT __stdcall PresentScene::hkPresentScene(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (!Renderer::m_bInitialized)
        Renderer::Setup(pSwapChain);

    Renderer::BeginScene();

    RenderStackSystem::RenderDrawData(ImGui::GetBackgroundDrawList());

    UI::Setup();

    Renderer::EndScene();

	return oPresentScene(pSwapChain, SyncInterval, Flags);
}

HRESULT __stdcall CreateSwapChain::hkCreateSwapChain(IDXGIFactory* pFactory, IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain)
{
	Renderer::ClearRenderTarget ();

	return oCreateSwapChain(pFactory, pDevice, pDesc, ppSwapChain);
}

HRESULT __stdcall ResizeBuffers::hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
    HRESULT hr = oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

    if (SUCCEEDED(hr) && Renderer::m_bInitialized)
    {
        Renderer::CreateRenderTarget(pSwapChain);
    }

    return hr;
}
