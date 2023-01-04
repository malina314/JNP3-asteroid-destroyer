#include "MainWindow.h"
#include "paths.h"
#include "common/utils.h"
#include "BitmapNames.h"
#include "common/Singleton.h"
#include "Input.h"

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

        Singleton<BitmapsManager>::getInstance().DrawAll(pRenderTarget, rc);

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

            LoadBitmaps();

            return 0;

        case WM_DESTROY:
            DiscardGraphicsResources();
            utils::SafeRelease(&pFactory);
            PostQuitMessage(0);
            return 0;

        case WM_KEYDOWN:
            HandleKeyDown(wParam);
            return 0;

        case WM_KEYUP:
            HandleKeyUp(wParam);
            return 0;

        case WM_PAINT:
            OnPaint();
            return 0;

        case WM_SIZE:
            Resize();
            return 0;
    }
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

Vec2 MainWindow::GetWindowSize() const {
    RECT rc;
    GetClientRect(m_hwnd, &rc);
    return Vec2(rc.right, rc.bottom);
}

void MainWindow::LoadBitmaps() {
    BitmapsManager &bm = Singleton<BitmapsManager>::getInstance();

    bm.Load(pRenderTarget, pWicFactory, paths::PLAYER_ASSET, BitmapNames::PLAYER);
    bm.Load(pRenderTarget, pWicFactory, paths::BG_ASSET, BitmapNames::BACKGROUND);
    bm.Load(pRenderTarget, pWicFactory, paths::BULLET_ASSET, BitmapNames::BULLET);
    bm.Load(pRenderTarget, pWicFactory, paths::ASTEROID1_ASSET, BitmapNames::ASTEROID1);
    bm.Load(pRenderTarget, pWicFactory, paths::ASTEROID2_ASSET, BitmapNames::ASTEROID2);
    bm.Load(pRenderTarget, pWicFactory, paths::ASTEROID3_ASSET, BitmapNames::ASTEROID3);
}

void MainWindow::HandleKeyDown(WPARAM key) const {
    switch (key) {
        case VK_UP:
            Singleton<Input>::getInstance().sendKeyDown(Key::UP);
            break;
        case VK_DOWN:
            Singleton<Input>::getInstance().sendKeyDown(Key::DOWN);
            break;
        case VK_LEFT:
            Singleton<Input>::getInstance().sendKeyDown(Key::LEFT);
            break;
        case VK_RIGHT:
            Singleton<Input>::getInstance().sendKeyDown(Key::RIGHT);
            break;
        case VK_SPACE:
            Singleton<Input>::getInstance().sendKeyDown(Key::SPACE);
            break;
    }
}

void MainWindow::HandleKeyUp(WPARAM key) const {
    switch (key) {
        case VK_UP:
            Singleton<Input>::getInstance().sendKeyUp(Key::UP);
            break;
        case VK_DOWN:
            Singleton<Input>::getInstance().sendKeyUp(Key::DOWN);
            break;
        case VK_LEFT:
            Singleton<Input>::getInstance().sendKeyUp(Key::LEFT);
            break;
        case VK_RIGHT:
            Singleton<Input>::getInstance().sendKeyUp(Key::RIGHT);
            break;
        case VK_SPACE:
            Singleton<Input>::getInstance().sendKeyUp(Key::SPACE);
            break;
    }
}
