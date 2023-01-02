#include "windows_h.h"
#include "MainWindow.h"
#include "Singleton.h"

int WINAPI wWinMain(_In_ [[maybe_unused]] HINSTANCE instance,
                    _In_opt_ [[maybe_unused]] HINSTANCE prevInstance,
                    _In_ [[maybe_unused]] PWSTR cmdLine,
                    _In_ [[maybe_unused]] INT nCmdShow) {
    MainWindow &mainWindow = Singleton<MainWindow>::getInstance();


    if (!mainWindow.Create(TEXT("Game window"), WS_OVERLAPPEDWINDOW)) {
        return 0;
    }

    ShowWindow(mainWindow.Window(), nCmdShow);

    // Run the message loop.
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}