#include "BitmapsManager.h"
#include "windows_h.h"
#include "common/utils.h"
#include "common/constants.h"

#include <d2d1_3.h>
#include <wincodec.h>
#include <d2d1helper.h>

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
    return static_cast<BitmapNames>(utils::random(constants::FIRST_ASTEROID_IN_ENUM, constants::LAST_ASTEROID_IN_ENUM));
}

void BitmapsManager::DrawBackground(ID2D1HwndRenderTarget *pTarget, RECT &bgSize) {
    Draw(pTarget, BitmapNames::BACKGROUND, D2D1::RectF(0, 0, bgSize.right, bgSize.bottom));
}

void BitmapsManager::Draw(ID2D1HwndRenderTarget *pTarget, BitmapNames bitmapName, D2D_RECT_F D_rc, float opacity) {
    pTarget->DrawBitmap(bitmaps[static_cast<int>(bitmapName)], D_rc, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
}

void BitmapsManager::DrawWithTransformation(ID2D1HwndRenderTarget *pTarget, BitmapNames bitmapName, D2D_RECT_F D_rc,
        D2D1::Matrix3x2F tfMatrix, D2D1::Matrix3x2F tfMatrixInv, float opacity ) {
    pTarget->SetTransform(tfMatrix);

    pTarget->DrawBitmap(bitmaps[static_cast<int>(bitmapName)], D_rc, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);

    pTarget->SetTransform(tfMatrixInv);
}

BitmapsManager::~BitmapsManager() {
    for (auto &bitmap : bitmaps) {
        utils::SafeRelease(&bitmap);
    }
}
