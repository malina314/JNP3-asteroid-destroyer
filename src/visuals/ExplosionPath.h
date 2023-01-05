#ifndef ASTEROID_DESTROYER_EXPLOSIONPATH_H
#define ASTEROID_DESTROYER_EXPLOSIONPATH_H


#include "common/utils.h"

#include <d2d1.h>

class ExplosionPath {
    ID2D1PathGeometry *path = nullptr;
    ID2D1GeometrySink *path_sink = nullptr;

public:
    void init(ID2D1Factory *pFactory) {
        pFactory->CreatePathGeometry(&path);
        path->Open(&path_sink);
        path_sink->BeginFigure(D2D1::Point2F(1302, 636), D2D1_FIGURE_BEGIN_FILLED);
        path_sink->AddBezier(D2D1::BezierSegment(
                D2D1::Point2F(1369, 723), D2D1::Point2F(1495, 784), D2D1::Point2F(1609, 641)));
        path_sink->AddBezier(D2D1::BezierSegment(
                D2D1::Point2F(1656, 774), D2D1::Point2F(1779, 763), D2D1::Point2F(1920, 700)));
        path_sink->AddBezier(D2D1::BezierSegment(
                D2D1::Point2F(1791, 866), D2D1::Point2F(1939, 1010), D2D1::Point2F(2030, 1042)));
        path_sink->AddBezier(D2D1::BezierSegment(
                D2D1::Point2F(1811, 1063), D2D1::Point2F(1743, 1141), D2D1::Point2F(1776, 1282)));
        path_sink->AddBezier(D2D1::BezierSegment(
                D2D1::Point2F(1619, 1226), D2D1::Point2F(1553, 1455), D2D1::Point2F(1563, 1505)));
        path_sink->AddBezier(D2D1::BezierSegment(
                D2D1::Point2F(1508, 1295), D2D1::Point2F(1345, 1318), D2D1::Point2F(1235, 1447)));
        path_sink->AddBezier(D2D1::BezierSegment(
                D2D1::Point2F(1287, 1283), D2D1::Point2F(1242, 1141), D2D1::Point2F(1016, 1128)));
        path_sink->AddBezier(D2D1::BezierSegment(
                D2D1::Point2F(1115, 1078), D2D1::Point2F(1230, 982), D2D1::Point2F(1113, 843)));
        path_sink->AddBezier(D2D1::BezierSegment(
                D2D1::Point2F(1219, 843), D2D1::Point2F(1299, 811), D2D1::Point2F(1303, 636)));
        path_sink->EndFigure(D2D1_FIGURE_END_OPEN);
        path_sink->Close();
    }

    ~ExplosionPath() {
        utils::SafeRelease(&path);
        utils::SafeRelease(&path_sink);
    }

    ID2D1PathGeometry *getPath() const {
        return path;
    }
};


#endif //ASTEROID_DESTROYER_EXPLOSIONPATH_H
