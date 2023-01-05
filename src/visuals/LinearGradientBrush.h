#ifndef ASTEROID_DESTROYER_LINEARGRADIENTBRUSH_H
#define ASTEROID_DESTROYER_LINEARGRADIENTBRUSH_H


#include "common/utils.h"

#include <d2d1.h>
#include <d2d1helper.h>

class LinearGradientBrush {
    static constexpr UINT NUM_LIN_STOPS = 3;
    ID2D1LinearGradientBrush *lin_brush = nullptr;
    ID2D1GradientStopCollection *lin_stops = nullptr;
    D2D1_GRADIENT_STOP lin_stops_data[NUM_LIN_STOPS];

    public:
        void init(ID2D1HwndRenderTarget *pTarget) {
            // Create the gradient stops
            lin_stops_data[0] =
                    { .position = 0.0f, .color = D2D1::ColorF(D2D1::ColorF::Yellow, 1.0f) };
            lin_stops_data[1] =
                    { .position = 0.25f, .color = D2D1::ColorF(D2D1::ColorF::Red, 1.0f) };
            lin_stops_data[2] =
                    { .position = 0.75f, .color = D2D1::ColorF(D2D1::ColorF::ForestGreen, 1.0f) };

            // Creating gradient stop collection
            pTarget->CreateGradientStopCollection(lin_stops_data, NUM_LIN_STOPS, &lin_stops);

            // Creating linear gradient brush
            if (lin_stops) {
                pTarget->CreateLinearGradientBrush(
                        D2D1::LinearGradientBrushProperties(D2D1::Point2F(20, 20), D2D1::Point2F(200, 300)),
                        lin_stops, &lin_brush);
            }

        }

        ~LinearGradientBrush() {
            utils::SafeRelease(&lin_brush);
            utils::SafeRelease(&lin_stops);
        }

        ID2D1LinearGradientBrush *getBrush() {
            return lin_brush;
        }
};


#endif //ASTEROID_DESTROYER_LINEARGRADIENTBRUSH_H
