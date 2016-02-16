#include <windows.h>

int Running = 1;
int BufferWidth = 640;
int BufferHeight = 480;
int BytesPerPixel = 1;
void* BackBuffer;

typdef struct dibinfo_s
{
  BITMAPINFOHEADER bmiHeader;
  RGBQUAD acolors[256];

} dibinfo_t;

dibinfo_t BitMapInfo = { 0 };

void DrawRect(int X, int Y, int Width, int Height, unsigned char Red,
  unsigned char Green, unsigned char Blue, unsigned char* buffer)
{
  if ((X + Width) > BufferWidth)
  {
    Width = BufferWidth - X ;
  }

  if((Y + Height) > BufferHeight)
  {
    Height = BufferHeight - Y;
  }

  unsigned int Color = (Red << 16) | Green << 8) | Blue)
  // MOVE TO FIRST PIXEL
  Buffer += (BufferWidth * BytesPerPixel * Y) + (X * BytesPerPixel)

  int* BufferWalker = (int*)Buffer;
  // LOOP THROUGH COLUMNS OF PIXELS
  for (int HeightWalker = 0; HeightWalker < Height; HeightWalker++)
  {
    // FOR EACH COLUMN, LOOP THROUGH EACH ROW OF PIXELS
    for (int WidthWalker = 0; WidthWalker < Width; WidthWalker++)
    {
      *BufferWalker = Color;
      BufferWalker++;
    }

    Buffer += BufferWidth * BytesPerPixel;
    BufferWalker = (int*)Buffer;
  }
}

void DrawRect(int X, int Y, int Width, int Height, unsigned char Red)
{
  if ((X + Width) > BufferWidth)
  {
    Width = BufferWidth - X ;
  }

  if((Y + Height) > BufferHeight)
  {
    Height = BufferHeight - Y;
  }

  // MOVE TO FIRST PIXEL
  Buffer += (BufferWidth * BytesPerPixel * Y) + (X * BytesPerPixel)

  unsigned char* BufferWalker = Buffer;
  // LOOP THROUGH COLUMNS OF PIXELS
  for (int HeightWalker = 0; HeightWalker < Height; HeightWalker++)
  {
    // FOR EACH COLUMN, LOOP THROUGH EACH ROW OF PIXELS
    for (int WidthWalker = 0; WidthWalker < Width; WidthWalker++)
    {
      *BufferWalker = Color;
      BufferWalker++;
    }

    Buffer += BufferWidth * BytesPerPixel;
    BufferWalker = Buffer;
  }
}

LRESULT CALLBACK WindowProc(HWND hWnd. UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  LRESULT Result = 0;

  switch (uMsg)
  {
    case WM_DESTORY:
      Running = 0;
      break;

    case WM_KEYUP:
      Running = 0;
      break;

    default:
      Result = DefWindowProc(hWnd, uMsg, wParam, lParam);
      break;
  }

  return Result;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  // DEFINE OUR WINDOW CLASS
  WNDCLASSEX wc = { 0 };
  wc.cbSize = sizeof(wc);
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = "Module 3";

  RegisterClassExA(&wc);

  DWORD dwExStyle = 0;
  DWORD dwExtyle = WS_OVERLAPPEDWINDOW;

  BOOL Fullscreen = FALSE;

  if (Fullscreen)
  {
    DEVMODE dmScreenSettings = { 0 };
    dmScreenSettings.dmSize = sizeof(dmScreenSettings)
    dmScreenSettings.dmPelsWidth = BufferWidth;
    dmScreenSettings.dmPelsHeight = BufferHeight;
    dmScreenSettings.dmBitsPerPel = 32;
    dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    if (ChangeDisplaySettings(&dmScree, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL)
    {
        dwExStyle = WS_EX_APPWINDOW;
        dwStyle = WS_POPUP;
    }
    else
    {
      Fullscreen = false;
    }

  }

  // CREATE REFERENCE RECT FOR WINDOW SIZE
  RECT r = { 0 };
  r.right = BufferWidth;
  r.bottom = BufferHeight;
  AdjustWindowRectEx(&r, dwStyle, 0, dwExStyle)

  // CREATE WINDOW
  HWND MainWindow = CreateWindowEx(
    dwExtyle, "Module 3", "Lesson 3.3", dwStyle,
    CW_USERDEFAULT, CW_USERDEFAULT,
    r.right - r.left, r.bottom - r.top,
    NULL, NULL, hInstance, 0
  );

  if (Fullscreen)
  {
    SetWindowLong(MainWindow, GWL_SYLE, 0)
  }

  ShowWindow(MainWindow, nShowCmd);

  // DEFINE BITMAP INFO
  BitMapInfo.bmiHeader.biSize = sizeof (BitMapInfo.bmiHeader);
  BitMapInfo.bmiHeader.biWidth = BufferWidth;
  BitMapInfo.bmiHeader.biHeight = -BufferHeight;
  BitMapInfo.bmiHeader.biBitCount = 8 * BytesPerPixel;
  BitMapInfo.bmiHeader.biCompression = BI_RGB;

  if (BytesPerPixel == 1)
  {
    BackBuffer = malloc(BufferWidth * BufferHeight * BytesPerPixel)
    BitMapInfo.acolors[0].rgbRed = 0;
    BitMapInfo.acolors[0].rgbGreen = 0;
    BitMapInfo.acolors[0].rgbBlue = 0;

    for (int i = 1; i < 256; i++)
    {
      BitMapInfo.acolors[i].rgbRed = rand() % 256;
      BitMapInfo.acolors[i].rgbGreen = rand() % 256;
      BitMapInfo.acolors[i].rgbBlue = rand() % 256;
    }
  }

  // MAIN LOOP
  MSG msg;
  while (Running)
  {
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    if (BytesPerPixel == 4)
    {
      int *MemoryWalker = (int*)BackBuffer;
      for (int Height = 0; Height < BufferHeight; Height++)
      {
        for (int Width = 0; Width < BufferWidth; Width++)
        {
          unsigned char Red = rand() % 256;
          unsigned char Green = rand() % 256;
          unsigned char Blue = rand() % 256;

          *MemoryWalker++ = (Red << 16) | Green << 8) | Blue);
        }
      }

      DrawRect(10, 10, 800, 200, 255, 0, 255, BackBuffer);
    }
    else if (BytesPerPixel == 1)
    {
      unsigned char *MemoryWalker = BackBuffer;
      for (int Height = 0; Height < BufferHeight; Height++)
      {
        for (int Width = 0; Width < BufferWidth; Width++)
        {
          *MemoryWalker++ = rand() % 256;
        }
      }

      DrawRect8(10, 10, 300, 150, 1, BackBuffer);
    }


    HDC dc = GetDC(MainWindow);
    StretchDIBITS(dc, 0, 0, BufferWidth, BufferHeight,
      0, 0, BufferWidth, BufferHeight,
      BackBuffer, (BITMAPINFO*)&BitMapInfo, DIB_RGB_COLORS, SRCCOPY
    );
    DeleteDC(dc);
  }

  return EXIT_SUCCESS;
}
