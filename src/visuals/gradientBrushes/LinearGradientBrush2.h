#ifndef ASTEROID_DESTROYER_LINEARGRADIENTBRUSH2_H
#define ASTEROID_DESTROYER_LINEARGRADIENTBRUSH2_H


#include "common/utils.h"

#include <d2d1.h>
#include <d2d1helper.h>

class LinearGradientBrush2 {
    static constexpr UINT NUM_LIN_STOPS = 2;

    ID2D1LinearGradientBrush *lin_brush = nullptr;
    ID2D1GradientStopCollection *lin_stops = nullptr;
    D2D1_GRADIENT_STOP lin_stops_data[NUM_LIN_STOPS];

    public:
        void init(ID2D1HwndRenderTarget *pTarget) {
            // Create the gradient stops
            lin_stops_data[0] =
                    { .position = 0.25f, .color = D2D1::ColorF(D2D1::ColorF::Yellow, 1.0f) };
            lin_stops_data[1] =
                    { .position = 0.75f, .color = D2D1::ColorF(D2D1::ColorF::Red, 1.0f) };

            // Create gradient stop collection
            pTarget->CreateGradientStopCollection(lin_stops_data, NUM_LIN_STOPS, &lin_stops);
        }

        ~LinearGradientBrush2() {
            utils::SafeRelease(&lin_brush);
            utils::SafeRelease(&lin_stops);
        }

        ID2D1LinearGradientBrush *getBrush(ID2D1HwndRenderTarget *pTarget, D2D1_POINT_2F start, D2D1_POINT_2F end) {
            // Release old brush
            utils::SafeRelease(&lin_brush);

            // Create linear gradient brush
            if (lin_stops) {
                pTarget->CreateLinearGradientBrush(
                        D2D1::LinearGradientBrushProperties(start, end),
                        lin_stops, &lin_brush);
            }

            return lin_brush;
        }
};


#endif //ASTEROID_DESTROYER_LINEARGRADIENTBRUSH2_H
