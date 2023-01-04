#ifndef ASTEROID_DESTROYER_BITMAPSMANAGER_H
#define ASTEROID_DESTROYER_BITMAPSMANAGER_H


#include "Vec2.h"
#include "common/utils.h"
#include "windows_h.h"
#include "BitmapNames.h"

#include <d2d1_3.h>
#include <wincodec.h>
#include <functional>

class BitmapsManager {
private:
    ID2D1Bitmap *bitmaps[static_cast<int>(BitmapNames::Count)];

public:
    void Load(ID2D1RenderTarget *pRenderTarget,
              IWICImagingFactory *pIWICFactory,
              PCWSTR uri,
              BitmapNames bitmapName
             ) {
        LoadBitmapFromFile(pRenderTarget, pIWICFactory, uri, &bitmaps[static_cast<int>(bitmapName)]);
    }

    void DrawBackground(ID2D1HwndRenderTarget *pTarget, RECT &bgSize);

    void Draw(ID2D1HwndRenderTarget *pTarget, BitmapNames bitmapName, D2D_RECT_F D_rc, float opacity = 1.0f);

    void DrawWithTransformation(ID2D1HwndRenderTarget *pTarget, BitmapNames bitmapName, D2D_RECT_F D_rc,
                                D2D1::Matrix3x2F tfMatrix, D2D1::Matrix3x2F tfMatrixInv, float opacity = 1.0f);

    static HRESULT LoadBitmapFromFile(
            ID2D1RenderTarget *pRenderTarget,
            IWICImagingFactory *pIWICFactory,
            PCWSTR uri,
            ID2D1Bitmap **ppBitmap
    );

    static BitmapNames randomAsteroid();
};


#endif //ASTEROID_DESTROYER_BITMAPSMANAGER_H
