#ifndef ASTEROID_DESTROYER_MAINWINDOW_H
#define ASTEROID_DESTROYER_MAINWINDOW_H


#include "BaseWindow.h"
#include "windows_h.h"
#include "BitmapNames.h"
#include "BitmapsManager.h"
#include "Engine.h"

#include <d2d1.h>
#include <d2d1_1.h>
#include <windowsx.h>

class MainWindow : public BaseWindow<MainWindow> {
    ID2D1Factory *pFactory;
    ID2D1HwndRenderTarget *pRenderTarget;
    ID2D1SolidColorBrush *pBrush;
    D2D1_ELLIPSE ellipse;
    D2D1_POINT_2F ptMouse;
    IWICImagingFactory *pWicFactory;

    HRESULT InitializeWICFactory();

    HRESULT CreateGraphicsResources();

    void DiscardGraphicsResources();

    void OnPaint();

    void Resize();

    void LoadBitmaps();

    void HandleKeyDown(WPARAM key) const;

    void HandleKeyUp(WPARAM key) const;

public:
    MainWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL),
                   pWicFactory(NULL), ellipse(D2D1::Ellipse(D2D1::Point2F(), 0, 0)),
                   ptMouse(D2D1::Point2F()) {
    }

    PCWSTR ClassName() const override { return TEXT("MainWindow Class"); }

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

    Vec2 GetWindowSize() const;
};


#endif //ASTEROID_DESTROYER_MAINWINDOW_H
