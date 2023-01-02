#include "MainWindow.h"
#include "paths.h"
#include "utils.h"
#include "BitmapNames.h"

#include <wincodec.h>

HRESULT MainWindow::InitializeWICFactory() {
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr)) {
        hr = CoCreateInstance(
                CLSID_WICImagingFactory,
                NULL,
                CLSCTX_INPROC_SERVER,
                IID_PPV_ARGS(&pWicFactory)
        );

        if (SUCCEEDED(hr)) {
            return 0;
        }
    }
    return -1;
}

HRESULT MainWindow::CreateGraphicsResources() {
    HRESULT hr = S_OK;
    if (pRenderTarget == NULL) {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        hr = pFactory->CreateHwndRenderTarget(
                D2D1::RenderTargetProperties(),
                D2D1::HwndRenderTargetProperties(m_hwnd, size),
                &pRenderTarget);

        if (SUCCEEDED(hr)) {
            const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0);
            hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);
        }
    }
    return hr;
}

void MainWindow::DiscardGraphicsResources() {
    utils::SafeRelease(&pRenderTarget);
    utils::SafeRelease(&pBrush);
}

void MainWindow::OnPaint() {
    HRESULT hr = CreateGraphicsResources();
    if (SUCCEEDED(hr)) {
        PAINTSTRUCT ps;
        BeginPaint(m_hwnd, &ps);

        pRenderTarget->BeginDraw();

        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
        pRenderTarget->FillEllipse(ellipse, pBrush);

        RECT rc;
        GetClientRect(m_hwnd, &rc);

//        auto lambda = [&](std::function<void(BitmapNames, D2D_RECT_F)> &cb) {
//            engine.DrawGameObjects(cb);
//        };

        bitmapsManager.DrawAll(pRenderTarget, rc, Engine::sDrawGameObjects, engine);

        hr = pRenderTarget->EndDraw();
        if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET) {
            DiscardGraphicsResources();
        }

        EndPaint(m_hwnd, &ps);

        InvalidateRect(m_hwnd, NULL, FALSE);
    }
}

void MainWindow::Resize() {
    if (pRenderTarget != NULL) {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        pRenderTarget->Resize(size);
        InvalidateRect(m_hwnd, NULL, FALSE);
    }
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: // initialize resources
            if (FAILED(D2D1CreateFactory(
                    D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory))) {
                return -1;  // Fail CreateWindowEx.
            }

            CreateGraphicsResources();

            if (InitializeWICFactory() == -1) {
                return -1;
            }

            bitmapsManager.Load(pRenderTarget, pWicFactory, paths::PLAYER_ASSET,
                                BitmapNames::PLAYER);
            bitmapsManager.Load(pRenderTarget, pWicFactory, paths::BG_ASSET,
                                BitmapNames::BACKGROUND);

            return 0;

        case WM_DESTROY:
            DiscardGraphicsResources();
            utils::SafeRelease(&pFactory);
            PostQuitMessage(0);
            return 0;

        case WM_KEYDOWN:
            if (wParam == VK_RIGHT)
                bitmapsManager.player_pos_x_tmp += 5;
            if (wParam == VK_LEFT)
                bitmapsManager.player_pos_x_tmp -= 5;
            // no return is intentional

        case WM_PAINT:
            OnPaint();
            return 0;

        case WM_SIZE:
            Resize();
            return 0;
    }
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}
