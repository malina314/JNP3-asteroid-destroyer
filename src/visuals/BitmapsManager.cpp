#include <iostream>
#include <string>
#include "BitmapsManager.h"
#include "windows_h.h"

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

void BitmapsManager::DrawAll(ID2D1HwndRenderTarget *pTarget, RECT &rc) {
    pTarget->DrawBitmap(bitmaps[(int) BitmapNames::BACKGROUND], D2D1::RectF(0, 0, rc.right, rc.bottom), 1.0f,
                        D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
    pTarget->DrawBitmap(bitmaps[0], D2D1::RectF(player_pos_x_tmp, 0, 100 + player_pos_x_tmp, 100), 1.0f,
                        D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
}
