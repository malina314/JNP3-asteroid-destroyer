#ifndef JNP3_VS_PROJECTS_BITMAPSMANAGER_H
#define JNP3_VS_PROJECTS_BITMAPSMANAGER_H


#include "utils.h"
#include "windows_h.h"
#include "Engine.h"
#include "BitmapNames.h"

#include <d2d1_3.h>
#include <wincodec.h>
#include <functional>

class BitmapsManager {
private:
    ID2D1Bitmap *bitmaps[static_cast<int>(BitmapNames::Count)];

public:
    int player_pos_x_tmp; // TODO: remove this

    void Load(ID2D1RenderTarget *pRenderTarget,
              IWICImagingFactory *pIWICFactory,
              PCWSTR uri,
              BitmapNames bitmapName
             ) {
        LoadBitmapFromFile(pRenderTarget, pIWICFactory, uri, &bitmaps[static_cast<int>(bitmapName)]);
    }

    void DrawAll(ID2D1HwndRenderTarget *pTarget, RECT &bgSize,
                 std::function<void(Engine &, std::function<void(BitmapNames, D2D_RECT_F)>)>
                         engineDrawCallback,
                 Engine &engine);

    void Draw(ID2D1HwndRenderTarget *pTarget, ID2D1Bitmap *bitmap, D2D_RECT_F D_rc);

    static HRESULT LoadBitmapFromFile(
            ID2D1RenderTarget *pRenderTarget,
            IWICImagingFactory *pIWICFactory,
            PCWSTR uri,
            ID2D1Bitmap **ppBitmap
    );

    static BitmapNames randomAsteroid();
};


#endif //JNP3_VS_PROJECTS_BITMAPSMANAGER_H