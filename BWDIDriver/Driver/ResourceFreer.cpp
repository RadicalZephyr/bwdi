#include "ResourceFreer.h"

#include <windows.h>
#include <Util\Types.h>

namespace BWDI
{
  namespace RecFreer
  {
    uint targetFPS = 1000;
    uint lastVisit = 0;
    uint timeout = 1000;

    void setFramerate(int new_Fps)
    {
      if(!new_Fps)
        targetFPS = 1000;
      else
        targetFPS = new_Fps;
    }
    void setTimeout(int milliseconds)
    {
      timeout = milliseconds;
    }
    void freeResources()
    {
      uint frameEndTime = lastVisit + 1000/targetFPS;
      uint timeTillFrameEnd = frameEndTime - GetTickCount();
      if(timeTillFrameEnd > 0)
      {
        if(timeTillFrameEnd > timeout)
          timeTillFrameEnd = timeout;
        Sleep(timeTillFrameEnd-1);
      }
      lastVisit = GetTickCount();
    }
  }
}
