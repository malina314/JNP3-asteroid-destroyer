#ifndef ASTEROID_DESTROYER_MAINWINDOW_H
#define ASTEROID_DESTROYER_MAINWINDOW_H


#include "BaseWindow.h"
#include "windows_h.h"
#include "BitmapNames.h"
#include "BitmapsManager.h"
#include "Engine.h"
#include "Vec2.h"
#include "gradientBrushes/LinearGradientBrush1.h"
#include "gradientBrushes/LinearGradientBrush2.h"
#include "gradientBrushes/RadialGradientBrush1.h"
#include "ExplosionPath.h"

#include <d2d1.h>
#include <d2d1_1.h>
#include <windowsx.h>

class MainWindow : public BaseWindow<MainWindow> {
    ID2D1Factory *pFactory;
    ID2D1HwndRenderTarget *pRenderTarget;
    ID2D1SolidColorBrush *pBrush;
    IWICImagingFactory *pWicFactory;
    LinearGradientBrush1 linearGradientBrush1;
    LinearGradientBrush2 linearGradientBrush2;
    RadialGradientBrush1 radialGradientBrush1;
    ExplosionPath explosionPath;

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
                   pWicFactory(NULL) {}

    ~MainWindow() {
        DiscardGraphicsResources();
        utils::SafeRelease(&pFactory);
        utils::SafeRelease(&pRenderTarget);
    }

    PCWSTR ClassName() const override { return TEXT("MainWindow Class"); }

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

    Vec2 GetWindowSize() const;

    void CloseWindow();

    void DrawExplosionPath(Vec2 position, float scale);
};


#endif //ASTEROID_DESTROYER_MAINWINDOW_H
