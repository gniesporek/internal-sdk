#include "renderer.h"

bool Renderer::setup(IDXGISwapChain* pSwapChain)
{
    if (isRendererReady)
        return true;

    if (FAILED(pSwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&pDevice))))
        return false;

    pSwapChainGlobal = pSwapChain;

    Renderer::pDevice->GetImmediateContext(&Renderer::pContext);
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    if (FAILED(pSwapChainGlobal->GetDesc(&swapChainDesc)))
        return false;

    Renderer::hWnd = swapChainDesc.OutputWindow;

    WindowProcedure::gWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(Renderer::hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProcedure::hWindowProcedure)));

    Renderer::createRenderTarget(pSwapChain);

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

    ImGui_ImplWin32_Init(Renderer::hWnd);
    ImGui_ImplDX11_Init(Renderer::pDevice, Renderer::pContext);

	Renderer::setupFonts();

    Renderer::isRendererReady = true;

    MESSAGE_SUCCESS("successfully initialized renderer");

    return true;
}

void Renderer::destroy()
{

    if (WindowProcedure::gWndProc && Renderer::hWnd)
        SetWindowLongPtr(Renderer::hWnd, GWLP_WNDPROC, (LONG_PTR)WindowProcedure::gWndProc);


    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    if (pRenderTargetView) { pRenderTargetView->Release(); pRenderTargetView = nullptr; }
    if (pContext) { pContext->Release(); pContext = nullptr; }
    if (pDevice) { pDevice->Release(); pDevice = nullptr; }

    Renderer::isRendererReady = false; // @ force init


}

void Renderer::clearRenderTarget()
{
    if (Renderer::pRenderTargetView)
    {
        Renderer::pRenderTargetView->Release();
        Renderer::pRenderTargetView = nullptr;
    }
}

void Renderer::createRenderTarget(IDXGISwapChain* pSwapChain)
{
    if (Renderer::pRenderTargetView)
    {
        Renderer::pRenderTargetView->Release();
        Renderer::pRenderTargetView = nullptr;
    }

    ID3D11Texture2D* pBackBuffer = nullptr;
    if (FAILED(pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer))))
        return;

    DXGI_SWAP_CHAIN_DESC desc{};
    pSwapChain->GetDesc(&desc);

    D3D11_RENDER_TARGET_VIEW_DESC rtvDesc{};
    rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    rtvDesc.Texture2D.MipSlice = 0;

    HRESULT hr = pDevice->CreateRenderTargetView(pBackBuffer, &rtvDesc, &Renderer::pRenderTargetView);

    if (FAILED(hr))
    {
        rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
        hr = pDevice->CreateRenderTargetView(pBackBuffer, &rtvDesc, &Renderer::pRenderTargetView);
        if (FAILED(hr))
            pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &Renderer::pRenderTargetView);
    }

    pBackBuffer->Release();
}

void Renderer::beginScene()
{
    if (Renderer::pContext)
        Renderer::pContext->OMSetRenderTargets(1, &Renderer::pRenderTargetView, NULL);

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void Renderer::endScene()
{
    ImGui::Render();
    ImGui::EndFrame();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

bool Renderer::setupFonts()
{
    ImFontConfig smallConfig;

    smallConfig.FontDataOwnedByAtlas = false;

    smallConfig.FontLoaderFlags = ImGuiFreeTypeLoaderFlags_::ImGuiFreeTypeBuilderFlags_MonoHinting | ImGuiFreeTypeLoaderFlags_::ImGuiFreeTypeBuilderFlags_Monochrome;


    ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdana.ttf", 12.0f, &smallConfig, Fonts::fontRanges); // default font

    ImGui::GetIO().Fonts->Build();

    MESSAGE_SUCCESS("successfully loaded fonts");
    return true;
}

LRESULT WindowProcedure::hWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (!ImGui::GetCurrentContext())
        return CallWindowProc(gWndProc, hWnd, uMsg, wParam, lParam);

    ImGuiIO& io = ImGui::GetIO();

    if (io.BackendPlatformUserData)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
            return TRUE;
    }


    return CallWindowProc(gWndProc, hWnd, uMsg, wParam, lParam);

}
