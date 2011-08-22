#include "DLLMain.h"

#include "Plugin\PluginLoader.h"

namespace BWDI
{
  namespace Engine
  {
    void onDllLoad();
  }
}

//------------------------------------------------- DLL MAIN -------------------------------------------------
BOOL APIENTRY DllMain(HMODULE, DWORD ul_reason_for_call, LPVOID)
{
  switch (ul_reason_for_call)
  {
    case DLL_PROCESS_ATTACH:
    {
      try
      {
        // WinAPI advises agains any code in DllMain except creation of a new thread, however:
        // memory transactions (hacks and hooks) are safe
        //MessageBoxA(NULL, "Loading BWDI", "", 0);
        BWDI::Engine::onDllLoad();
      }
      catch(...)
      {
        // if anything throws, the dll will unload
        return false;
      }
      return true;
    }
  }
  return true;
}
