#include "TextWriter.h"
#include "common/utils.h"
#include "common/constants.h"

#include <d2d1_3.h>
#include <dwrite_3.h>

TextWriter::TextWriter() {
    DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory),
            reinterpret_cast<IUnknown**>(&write_factory)
    );

    write_factory->CreateTextFormat(
            L"Arial",
            nullptr,
            DWRITE_FONT_WEIGHT_BOLD,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            constants::FONT_SIZE,
            L"en-us",
            &text_format[static_cast<int>(TextType::NORMAL)]
    );

    write_factory->CreateTextFormat(
            L"Arial",
            nullptr,
            DWRITE_FONT_WEIGHT_BOLD,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            constants::FONT_SIZE_GAME_OVER,
            L"en-us",
            &text_format[static_cast<int>(TextType::GAME_OVER)]
    );
    text_format[static_cast<int>(TextType::GAME_OVER)]->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    text_format[static_cast<int>(TextType::GAME_OVER)]->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

    write_factory->CreateTextFormat(
            L"Arial",
            nullptr,
            DWRITE_FONT_WEIGHT_BOLD,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            constants::FONT_SIZE_BOTTOM_TEXT,
            L"en-us",
            &text_format[static_cast<int>(TextType::BOTTOM_TEXT)]
    );
    text_format[static_cast<int>(TextType::BOTTOM_TEXT)]->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
}

TextWriter::~TextWriter() {
    utils::SafeRelease(&write_factory);
    for (auto &format : text_format) {
        utils::SafeRelease(&format);
    }
}

void TextWriter::WriteText(ID2D1HwndRenderTarget *pTarget, const std::wstring &text, D2D1_RECT_F rc,
                           ID2D1Brush *pBrush) {
    pTarget->DrawText(
            text.c_str(),
            text.length(),
            text_format[static_cast<int>(TextType::NORMAL)],
            rc,
            pBrush
    );
}

void TextWriter::WriteGameOverText(ID2D1HwndRenderTarget *pTarget, const std::wstring &text, D2D1_RECT_F rc,
                                   ID2D1Brush *pBrush) {
    pTarget->DrawText(
            text.c_str(),
            text.length(),
            text_format[static_cast<int>(TextType::GAME_OVER)],
            rc,
            pBrush
    );
}

void TextWriter::WriteBottomText(ID2D1HwndRenderTarget *pTarget, const std::wstring &text, D2D1_RECT_F rc,
                                 ID2D1Brush *pBrush) {
    pTarget->DrawText(
            text.c_str(),
            text.length(),
            text_format[static_cast<int>(TextType::BOTTOM_TEXT)],
            rc,
            pBrush
    );
}
