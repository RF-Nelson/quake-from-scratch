#include <stdio.h>
#include <windows.h>

int Running = 1;

typdef struct dibinfo_s
{
  BITMAPINFOHEADER bmiHeader;
  RGBQUAD acolors[256];

} dibinfo_t;

dibinfo_t BitMapInfo = { 0 };

void DrawRect32(int X, int Y, int Width, int Height, unsigned char Red,
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

void DrawPic32(int X, int Y, int Width, int Height, unsigned char* Source, unsigned char* Dest)
{
  Dest += (BufferWidth * BytesPerPixel * Y) + (X * BytesPerPixel);

  unsigned int* BufferWalker = (unsingned int*)Dest;

  for (int HeightWalker = 0; HeightWalker < Height; HeightWalker++)
  {
    // FOR EACH COLUMN, LOOP THROUGH EACH ROW OF PIXELS
    for (int WidthWalker = 0; WidthWalker < Width; WidthWalker++)
    {
      int* ColorValue = (int*)&BitMapInfo.acolors[*Source];
      *BufferWalker = *ColorValue;
      BufferWalker++;
      Source++;
    }

    Dest += BufferWidth * BytesPerPixel;
    BufferWalker = (unsigned int*)Dest;
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



  FILE * disc = fopen("DISC.lmp", "rb");
  int DiscWidth, discheight;
  size_t RetVal = fread(&DiscWidth, 4, 1, Disc);
  RetVal = fread(&DiscHeight, 4, 1, Disc);
  void* DiscData = malloc(DiscWidth * DiscHeight);
  RetVal = fread(DiscData, 1, DiscWidth * DiscHeight, Disc)
  fclose(disc)

  FILE *Pause = fopen("pause.lmp", "rb");
  int PauseWidth, PauseHeight;
  RetVal = fread(&PauseWidth, 1, 4, Pause);
  RetVal = fread(&PauseHeight, 1, 4, Pause);
  void *PauseData = malloc(PauseWidth * PauseHeight);
  RetVal = fread(PauseData, 1, PauseWidth * PauseHeight, Pause);
  fclose(pause)

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
      DrawPic32(10, 10, PauseWidth, PauseHeight, PauseData, BackBuffer);
      // DrawRect(10, 10, 800, 200, 255, 0, 255, BackBuffer);
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
      DrawPic(100, 100, DiscWidth, DiscHeight, DiscData);
      // DrawRect8(10, 10, 300, 150, 1, BackBuffer);
    }


    HDC dc = GetDC(MainWindow);
    StretchDIBITS(dc, 0, 0, BufferWidth, BufferHeight,
      0, 0, BufferWidth, BufferHeight,
      BackBuffer, (BITMAPINFO*)&BitMapInfo, DIB_RGB_COLORS, SRCCOPY
    );
    ReleaseDC(dc);
  }

  free(BackBuffer);
  free(DiscData);
  free(PauseData);

  return EXIT_SUCCESS;
}
