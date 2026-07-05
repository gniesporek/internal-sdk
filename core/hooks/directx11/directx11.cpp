#include "../hooks.h"

HRESULT __stdcall PresentScene::hkPresentScene(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (!renderer.isRendererReady)
        renderer.setup(pSwapChain);

    renderer.beginScene();

    renderStackSystem.renderDrawData(ImGui::GetBackgroundDrawList());

    ui.paint();

    renderer.endScene();

	return oPresentScene(pSwapChain, SyncInterval, Flags);
}

HRESULT __stdcall CreateSwapChain::hkCreateSwapChain(IDXGIFactory* pFactory, IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain)
{
	renderer.clearRenderTarget();

	return oCreateSwapChain(pFactory, pDevice, pDesc, ppSwapChain);
}

HRESULT __stdcall ResizeBuffers::hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
    HRESULT hr = oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

    if (SUCCEEDED(hr) && renderer.isRendererReady)
    {
        renderer.createRenderTarget(pSwapChain);
    }

    return hr;
}
