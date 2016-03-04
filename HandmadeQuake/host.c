#include "quakedef.h"

#include "time.h"
#include "std.io"

double realtime = 0;
double oldrealtime = 0;
double host_frametime = 0;

extern void* BackBuffer;

qboolean Host_FilterTime(float time) {
  realtime += time;

  if (realtime - oldtime < 1.0 / 72.0) {
    return false;
  }

  host_frametime = realtime - oldrealtime;
  oldrealtime = realtime;

  return true;
}

void Host_Init(void)
{
  VID_Init();
}

void Host_Frame(float timestep)
{
  if (!Host_FilterTime(timestep)) {
    return;
  }

  Sys_SendKeyEvents();

  VID_Update();
}

vod VID_Update(void)
{

}

void Host_Shutdown(void)
{
  VID_Shutdown();
}
