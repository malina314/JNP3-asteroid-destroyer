#ifndef ASTEROID_DESTROYER_BASEWINDOW_H
#define ASTEROID_DESTROYER_BASEWINDOW_H


#include "windows_h.h"

template<class DERIVED_TYPE>
class BaseWindow {
public:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        DERIVED_TYPE *pThis = NULL;

        if (uMsg == WM_NCCREATE) {
            CREATESTRUCT *pCreate = (CREATESTRUCT *) lParam;
            pThis = (DERIVED_TYPE *) pCreate->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) pThis);

            pThis->m_hwnd = hwnd;
        } else {
            pThis = (DERIVED_TYPE *) GetWindowLongPtr(hwnd, GWLP_USERDATA);
        }
        if (pThis) {
            return pThis->HandleMessage(uMsg, wParam, lParam);
        } else {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    BaseWindow() : m_hwnd(NULL) {}

    BOOL Create(
            PCWSTR lpWindowName,
            DWORD dwStyle,
            DWORD dwExStyle = 0,
            int x = CW_USEDEFAULT,
            int y = CW_USEDEFAULT,
            int nWidth = CW_USEDEFAULT,
            int nHeight = CW_USEDEFAULT,
            HWND hWndParent = 0,
            HMENU hMenu = 0
    ) {
        WNDCLASS wc = {0};

        wc.lpfnWndProc = DERIVED_TYPE::WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = ClassName();

        // hide cursor
        wc.hCursor = NULL;

        RegisterClass(&wc);

        m_hwnd = CreateWindowEx(
                dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
                nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this
        );

        return (m_hwnd ? TRUE : FALSE);
    }

    void SwitchToFullscreen() {
        HWND hwnd = m_hwnd;
        WINDOWPLACEMENT g_wpPrev = { sizeof(g_wpPrev) };
        DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);
        if (dwStyle & WS_OVERLAPPEDWINDOW) {
            MONITORINFO mi = { sizeof(mi) };
            if (GetWindowPlacement(hwnd, &g_wpPrev) &&
                GetMonitorInfo(MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY), &mi)) {
                SetWindowLong(hwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
                SetWindowPos(hwnd, HWND_TOP,
                             mi.rcMonitor.left, mi.rcMonitor.top,
                             mi.rcMonitor.right - mi.rcMonitor.left,
                             mi.rcMonitor.bottom - mi.rcMonitor.top,
                             SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
            }
        } else {
            SetWindowLong(hwnd, GWL_STYLE,
                          dwStyle | WS_OVERLAPPEDWINDOW);
            SetWindowPlacement(hwnd, &g_wpPrev);
            SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
                         SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
                         SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
        }
    }

    HWND Window() const { return m_hwnd; }

protected:

    virtual PCWSTR ClassName() const = 0;

    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

    HWND m_hwnd;
};


#endif //ASTEROID_DESTROYER_BASEWINDOW_H
