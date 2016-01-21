#include <windows.h>

BOOL IsRunning = TRUE;

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM, lParam)
{
    // catch any relevant messages here
    switch (uMsg) {
    case WM_KEYUP:
        IsRunning = FALSE;
        break;
    case WM_ACTIVATE:
    case WM_CREATE:
    case WM_DESTROY:
        IsRunning = FALSE;
        break;
    default:
        Result = DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    
    return Result;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = MainWndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = "Module 2";

    if (!RegisterClass(&wc)) {
        exit(EXIT_FAILURE);
    }

    HWND mainwindow;
    DWORD WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
    
    RECT r;
    r.top = r.left = 0;
    r.right = 800;
    r.bottom - 600;

    AdjustWindowRect(&r, WindowStyle, FALSE);

    mainwindow = CreateWindowEx(
        0,
        "Module 2",
        "Lesson 2.1",
        WindowStyle,
        200,
        200,
        r.right - r.left,
        r.bottom - r.top,
        NULL,
        NULL,
        hInstance,
        0
    );

    ShowWindow(mainwindow, SW_SHOWDEFAULT);

    HDC DeviceContext = GETDC(mainwindow);
    PatBlt(DeviceContext, 0, 0, 800, 600, BLACKNESS);
    ReleaseDC(mainWindow, DeviceContext);
    
    MSG msg;
    LRESULT Result;

    while (IsRunning)
    {
        // Check in with OS
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {    
            TranslateMessage(&msg);
            Result = DispatchMessage(&msg);
        }
    }

    return 0;
}
