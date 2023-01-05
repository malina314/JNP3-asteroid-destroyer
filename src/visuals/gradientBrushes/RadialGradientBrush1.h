#ifndef ASTEROID_DESTROYER_RADIALGRADIENTBRUSH1_H
#define ASTEROID_DESTROYER_RADIALGRADIENTBRUSH1_H


#include <d2d1.h>
#include "common/utils.h"

class RadialGradientBrush1 {
    static constexpr UINT NUM_RAD_STOPS = 2;

    ID2D1RadialGradientBrush *rad_brush = nullptr;
    ID2D1GradientStopCollection *rad_stops = nullptr;
    D2D1_GRADIENT_STOP rad_stops_data[NUM_RAD_STOPS];

public:
    void init(ID2D1HwndRenderTarget *pTarget) {
        // Create the gradient stops
        rad_stops_data[0] =
                { .position = 0.07f, .color = D2D1::ColorF(D2D1::ColorF::Yellow, 1.0f) };
        rad_stops_data[1] =
                { .position = 0.85f, .color = D2D1::ColorF(D2D1::ColorF::Red, 1.0f) };

        // Create gradient stop collection
        pTarget->CreateGradientStopCollection(rad_stops_data, NUM_RAD_STOPS, &rad_stops);

        // Create radial gradient brush
        if (rad_stops) {
            pTarget->CreateRadialGradientBrush(
                    D2D1::RadialGradientBrushProperties(D2D1::Point2F(1515, 1050),
                                                        D2D1::Point2F(0, 0),
                                                        500, 500),
                    rad_stops, &rad_brush);
        }

    }

    ~RadialGradientBrush1() {
        utils::SafeRelease(&rad_brush);
        utils::SafeRelease(&rad_stops);
    }

    ID2D1RadialGradientBrush *getBrush() {
        return rad_brush;
    }

};


#endif //ASTEROID_DESTROYER_RADIALGRADIENTBRUSH1_H
