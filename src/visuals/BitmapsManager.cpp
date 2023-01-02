#include "BitmapsManager.h"
#include "windows_h.h"
#include "common/utils.h"
#include "Engine.h"
#include "Singleton.h"

#include <d2d1_3.h>
#include <wincodec.h>

HRESULT BitmapsManager::LoadBitmapFromFile(
        ID2D1RenderTarget *pRenderTarget,
        IWICImagingFactory *pIWICFactory,
        PCWSTR uri,
        ID2D1Bitmap **ppBitmap
) {
    IWICBitmapDecoder *pDecoder = NULL;
    IWICBitmapFrameDecode *pSource = NULL;
    IWICStream *pStream = NULL;
    IWICFormatConverter *pConverter = NULL;
    IWICBitmapScaler *pScaler = NULL;

    HRESULT hr = pIWICFactory->CreateDecoderFromFilename(
            uri,
            NULL,
            GENERIC_READ,
            WICDecodeMetadataCacheOnLoad,
            &pDecoder
    );

    if (SUCCEEDED(hr)) {
        // Create the initial frame.
        hr = pDecoder->GetFrame(0, &pSource);
    }

    if (SUCCEEDED(hr)) {
        // Create a FormatConverter and initialize it with the FrameDecode.
        hr = pIWICFactory->CreateFormatConverter(&pConverter);
    }

    if (SUCCEEDED(hr)) {
        hr = pConverter->Initialize(
                pSource,
                GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone,
                NULL,
                0.f,
                WICBitmapPaletteTypeMedianCut
        );

        if (SUCCEEDED(hr)) {
            // Create a Direct2D bitmap from the WIC bitmap.
            hr = pRenderTarget->CreateBitmapFromWicBitmap(
                    pConverter,
                    NULL,
                    ppBitmap
            );
        }

        utils::SafeRelease(&pDecoder);
        utils::SafeRelease(&pSource);
        utils::SafeRelease(&pStream);
        utils::SafeRelease(&pConverter);
        utils::SafeRelease(&pScaler);

        return hr;
    }

    utils::SafeRelease(&pDecoder);
    utils::SafeRelease(&pSource);
    utils::SafeRelease(&pStream);
    utils::SafeRelease(&pConverter);
    utils::SafeRelease(&pScaler);

    return -1;
}

BitmapNames BitmapsManager::randomAsteroid() {
    return static_cast<BitmapNames>(utils::random(3, 5));
}

void BitmapsManager::DrawAll(ID2D1HwndRenderTarget *pTarget, RECT &bgSize) {
    // draw background
    Draw(pTarget, BitmapNames::BACKGROUND, D2D1::RectF(0, 0, bgSize.right, bgSize.bottom));

    // draw game objects
    Singleton<Engine>::getInstance().DrawGameObjects(pTarget);
}

void BitmapsManager::Draw(ID2D1HwndRenderTarget *pTarget, BitmapNames bitmapName, D2D_RECT_F D_rc) {
    pTarget->DrawBitmap(bitmaps[static_cast<int>(bitmapName)], D_rc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
}
