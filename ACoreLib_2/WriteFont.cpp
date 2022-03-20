#include "WriteFont.h"

void AWriteFont::DeleteDeviceResize()
{
    //아래 2가지는 먼저 삭제처리 되어야 한다.
    if (m_pd2dColorBrush)   m_pd2dColorBrush->Release();
    if (m_pd2dRT)           m_pd2dRT->Release();
}
bool AWriteFont::SetRenderTarget(IDXGISurface1* pSurface)
{
    UINT dpi = GetDpiForWindow(g_hWnd);

    D2D1_RENDER_TARGET_PROPERTIES rtp;
    ZeroMemory(&rtp, sizeof(D2D1_RENDER_TARGET_PROPERTIES));
    rtp.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
    rtp.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
    rtp.dpiX = dpi;
    rtp.dpiY = dpi;
    rtp.usage = D2D1_RENDER_TARGET_USAGE_NONE;
    rtp.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;
    HRESULT hr = m_pd2dFactory->CreateDxgiSurfaceRenderTarget(pSurface, &rtp, &m_pd2dRT);
    // IDXGISurface *dxgiSurface,CONST D2D1_RENDER_TARGET_PROPERTIES* renderTargetProperties,ID2D1RenderTarget** renderTarget
    if (FAILED(hr))  return false;
    if (FAILED(m_pd2dRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pd2dColorBrush))) { return false; }
    return true;
}
void AWriteFont::Draw(wstring msg, RECT rt, D2D1::ColorF color, IDWriteTextFormat* tf)
{
    m_pd2dRT->BeginDraw();
    D2D_RECT_F fRT;
    fRT.left = rt.left;
    fRT.top = rt.top;
    fRT.right = rt.right;
    fRT.bottom = rt.bottom;

    /*D2D_RECT_F rt;
    rt.top = 0;
    rt.left = 0;
    rt.right = g_rtClient.right;
    rt.bottom = g_rtClient.bottom;
    std::wstring msg = L"FPS arhan 2Dgame";
    m_pd2dRT->DrawText(msg.c_str(), msg.size(),m_pd2dTextFormat,
                        &rt,m_pd2dColorBrush);*/

    m_pd2dColorBrush->SetColor(color);
    if (tf == nullptr)
    {
        m_pd2dRT->DrawText(msg.c_str(), msg.size(), m_pd2dTextFormat, &fRT, m_pd2dColorBrush);
    }
    else
    {
        m_pd2dRT->DrawText(msg.c_str(), msg.size(), tf, &fRT, m_pd2dColorBrush);
    }
    m_pd2dRT->EndDraw();
}
bool AWriteFont::Init()
{
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pd2dFactory);
    if (SUCCEEDED(hr))
    {
        hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory), (IUnknown**)(&m_pWriteFactory));
        if (SUCCEEDED(hr))
        {
            hr = m_pWriteFactory->CreateTextFormat(
                L"돋움",
                NULL,
                DWRITE_FONT_WEIGHT_MEDIUM,     //노멀->레귤러
                DWRITE_FONT_STYLE_NORMAL,
                DWRITE_FONT_STRETCH_NORMAL,
                15,
                L"ko-kr",
                &m_pd2dTextFormat);

            hr = m_pWriteFactory->CreateTextFormat(
                L"Imprint MT Shadow",
                NULL,
                DWRITE_FONT_WEIGHT_MEDIUM,
                DWRITE_FONT_STYLE_NORMAL,
                DWRITE_FONT_STRETCH_NORMAL,
                15,
                L"en-us",
                &m_pd2dMTShadowTF);
        }
    }
    if (SUCCEEDED(hr)) { return true; }
    return false;
}
bool AWriteFont::Frame() { return true; }
bool AWriteFont::Render()
{
    //begin~end 사이에 뿌릴것
    m_pd2dRT->BeginDraw();
    m_pd2dRT->EndDraw();
    return true;
}
bool AWriteFont::Release()
{
    if (m_pd2dMTShadowTF)   m_pd2dMTShadowTF->Release();
    if (m_pd2dTextFormat)   m_pd2dTextFormat->Release();
    if (m_pd2dColorBrush)   m_pd2dColorBrush->Release();
    if (m_pd2dRT)           m_pd2dRT->Release();
    if (m_pWriteFactory)    m_pWriteFactory->Release();
    if (m_pd2dFactory)      m_pd2dFactory->Release();
    return true;
}