#include "quakdef.h"
#include "winquake.h"

static BOOL IsRunning = TRUE;

/////////////////////////////////////
//          TIMER CODE             //
/////////////////////////////////////

static double SecondsPerTick = 0;
static double TimePAssed = 0;
static __int64 GTimeCount = 0;

float Sys_InitFloatTime(void)
{
  LARGE_INTEGER Frequency;
  QueryPerformanceFrequency(&Frequency);

  SecondsPerTick =  1.0 / (double)Frequency.QuadPart;

  LARGE_INTEGER Counter;
  QueryPerformanceCounter(&Counter);

  GTimeCount = Counter.QuadPart;

  return 0;
}

float Sys_FloatTime(void)
{
  LARGE_INTEGER Counter;
  QueryPerformanceCounter(&Counter);

  __int64 Interval = Tock.QuadPart - GTimeCount;
  GTimeCount = Counter.QuadPart;
  double SecondsGoneBy = (double)Interval * SecondsPerTick;
  GTimePassed =+ SecondsGoneBy;
  return (float)GTimePassed;
}

/////////////////////////////////////
//        END TIMER CODE           //
/////////////////////////////////////

void Sys_Shutdown(void)
{
  IsRunning = false;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM, lParam)
{
    // catch any relevant messages here
    switch (uMsg)
    {
    case WM_ACTIVATE:
      break;

    case WM_CREATE:
      break;

    case WM_DESTROY:
        Sys_Shutdown()
        break;

    default:
        Result = DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return Result;
}

int32 WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    COM_ParseCmdLine(lpCmdLine);

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
        "Lesson 2.6",
        WindowStyle,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
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

    Host_Init();

    float oldtime = Sys_InitFloatTime();

    MSG msg;
    while (IsRunning)
    {
        // Check in with OS
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        float newtime = Sys_FloatTime();
        Host_Frame(newtime - oldtime);
        oldtime = newtime;
    }

    return 0;
}
