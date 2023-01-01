#ifndef JNP3_VS_PROJECTS_BITMAPSMANAGER_H
#define JNP3_VS_PROJECTS_BITMAPSMANAGER_H


#include "utils.h"
#include "windows_h.h"

#include <d2d1_3.h>
#include <wincodec.h>

class BitmapsManager {
public:
    enum class BitmapNames {
        PLAYER,
        BACKGROUND,
        BULLET,
        ASTEROID1,
        ASTEROID2,
        ASTEROID3,
        Count // special value used for declaring arrays
    };
private:
    ID2D1Bitmap *bitmaps[static_cast<int>(BitmapNames::Count)];

public:
    int player_pos_x_tmp;

    void Load(ID2D1RenderTarget *pRenderTarget,
              IWICImagingFactory *pIWICFactory,
              PCWSTR uri,
              BitmapNames bitmapName
             ) {
        LoadBitmapFromFile(pRenderTarget, pIWICFactory, uri, &bitmaps[static_cast<int>(bitmapName)]);
    }

    static HRESULT LoadBitmapFromFile(
            ID2D1RenderTarget *pRenderTarget,
            IWICImagingFactory *pIWICFactory,
            PCWSTR uri,
            ID2D1Bitmap **ppBitmap
    );

    void DrawAll(ID2D1HwndRenderTarget *pTarget, RECT &rc);
};


#endif //JNP3_VS_PROJECTS_BITMAPSMANAGER_H
