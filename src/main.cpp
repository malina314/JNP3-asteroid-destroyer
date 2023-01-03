#include "windows_h.h"
#include "MainWindow.h"
#include "common/Singleton.h"
#include "common/constants.h"

int WINAPI wWinMain(_In_ [[maybe_unused]] HINSTANCE instance,
                    _In_opt_ [[maybe_unused]] HINSTANCE prevInstance,
                    _In_ [[maybe_unused]] PWSTR cmdLine,
                    _In_ [[maybe_unused]] INT nCmdShow) {
    MainWindow &mainWindow = Singleton<MainWindow>::getInstance();
    Engine &engine = Singleton<Engine>::getInstance();

    if (!mainWindow.Create(TEXT("Asteroid Destroyer"), WS_OVERLAPPEDWINDOW)) {
        return 0;
    }

    ShowWindow(mainWindow.Window(), nCmdShow);

    engine.start();

    // Run the message loop.
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        engine.update();
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}