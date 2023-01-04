#ifndef ASTEROID_DESTROYER_TEXTWRITER_H
#define ASTEROID_DESTROYER_TEXTWRITER_H


#include <string>
#include <d2d1_3.h>
#include <dwrite_3.h>

class TextWriter {
    IDWriteFactory *write_factory;
    IDWriteTextFormat *text_format;

public:
    TextWriter();

    ~TextWriter();

    void WriteText(ID2D1HwndRenderTarget *pTarget, const std::wstring &text, D2D1_RECT_F rc,
                   ID2D1SolidColorBrush *pBrush);
};


#endif //ASTEROID_DESTROYER_TEXTWRITER_H
