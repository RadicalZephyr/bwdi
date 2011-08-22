#include "PluginLoader.h"

#include <windows.h>
#include <stdexcept>

typedef bool (__cdecl *ApplyPatchFuction)(HANDLE, DWORD); // hProcess, dwProcessID

bool LoadBWLPlugin(const char* filename)
{
  HMODULE moduleHandle = LoadLibrary(filename);
  if(!moduleHandle)
    return false;

  ApplyPatchFuction ApplyPatch = (ApplyPatchFuction)GetProcAddress(moduleHandle, "ApplyPatchSuspended");
  if(!ApplyPatch)
    return false;
  ApplyPatch(GetCurrentProcess(), GetCurrentProcessId());

  return true;
}
