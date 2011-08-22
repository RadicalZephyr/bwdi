// NoQuestionsAskedInstaller.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "NoQuestionsAskedInstaller.h"
#include "BinaryLoader.h"

#include "..\svnrev.h"

#include <stdio.h>
#include <stdexcept>

const char* title = "BWDI r" SVN_REV_STR " installer";

DWORD InstallPathLength = 1000;
char InstallPath[1000];

DWORD calculateChecksum(BYTE *data, int size)
{
  DWORD checksum = 0;
  for(int p = 0; p < size; p++)
  {
    ((BYTE*)&checksum)[p%4] += data[p];
  }
  return checksum;
}

//
// returns -1 if not found
//

int findFirstOccurence(BYTE* haystack, int haystackSize, BYTE* needle, int needleSize)
{
  int p = 0;
  int i = 0;
  for(p = 0; p < haystackSize - needleSize + 1; p++)
  {
    for(i = 0; i < needleSize; i++)
    {
      if(haystack[p + i] != needle[i])
        break;
    }
    if(i == needleSize)
      return p;
  }
  return -1;
}

//
// Icon header structure extracted from http://en.wikipedia.org/wiki/ICO_(file_format)
//

#pragma pack(push, 1)
struct IcoFileHeader
{
  WORD _zero0;
  WORD imageType;
  WORD imageCount;
  struct
  {
    BYTE width;
    BYTE height;
    BYTE colors;
    BYTE _zero0;
    WORD colorPlaneCount;
    WORD bitsPerPixel;
    DWORD bitmapSize;
    DWORD bitmapOffset;
  } images[1];
};
#pragma pack(pop)

BYTE *getIconData(BYTE *iconFile)
{
  return iconFile + ((IcoFileHeader*)iconFile)->images[0].bitmapOffset;
}

int getIconDataSize(BYTE *iconFile)
{
  int lastImage = ((IcoFileHeader*)iconFile)->imageCount - 1;
  return 
      ((IcoFileHeader*)iconFile)->images[lastImage].bitmapOffset
    - ((IcoFileHeader*)iconFile)->images[0].bitmapOffset
    + ((IcoFileHeader*)iconFile)->images[lastImage].bitmapSize;
}

void patchIcons(BYTE* executable, int executableSize)
{
  BinaryLoader icon1source;
  BinaryLoader icon1dest;
  BinaryLoader icon2source;
  BinaryLoader icon2dest;
  icon1source.loadFromFile("icons\\icon1source.ico");
  icon1dest.loadFromFile("icons\\icon1dest.ico");
  icon2source.loadFromFile("icons\\icon2source.ico");
  icon2dest.loadFromFile("icons\\icon2dest.ico");

  //
  // the icon data is stored in Starcraft.exe raw, but without the header
  // our goal is to replace the old icon data, with the new one.
  //

  // first find the icon data location in the executable
  int icon1offset = findFirstOccurence(executable, executableSize, getIconData(icon1source.buffer), getIconDataSize(icon1source.buffer));
  int icon2offset = findFirstOccurence(executable, executableSize, getIconData(icon2source.buffer), getIconDataSize(icon2source.buffer));
  if(icon1offset == -1 || icon2offset == -1)
  {
    MessageBox(NULL, "Icon patch error. Cannot Install.", title, MB_ICONERROR|MB_OK);
    exit(1);
  }

  // now overwrite it with the updated versions
  memcpy(executable + icon1offset, getIconData(icon1dest.buffer), getIconDataSize(icon1dest.buffer));
  memcpy(executable + icon2offset, getIconData(icon2dest.buffer), getIconDataSize(icon2dest.buffer));
}

void patchMultipleInstances(BYTE* executable)
{
  // NOP out some code
  void *nop1 = executable + 0x0E0AF8;
  memset(nop1, 0x90, 5);
  void *nop2 = executable + 0x0E0B02;
  memset(nop2, 0x90, 5);
}

void patchBWDILoader(BYTE* executable)
{
  // expand the .text section size to cover the loader
  DWORD *sectionSize = (DWORD*)&executable[0x208];
  *sectionSize = 0x000FD000;

  // inject the loader
  BYTE loader[] = {0x68, 0xA0, 0xDF, 0x4F, 0x00, 0xFF, 0x15, 0xE4,
                     0xE1, 0x4F, 0x00, 0xE9, 0x8B, 0x6C, 0xF0, 0xFF};
  char *moduleName = "BWDIDriver.dll";

  DWORD *loaderLocation = (DWORD*)&executable[0x0FDF86];
  char *loaderParameter = (char*)&executable[0x0FDFA0];
  memcpy(loaderLocation, loader, sizeof(loader));
  strcpy(loaderParameter, moduleName);

  // set entry point to the loader
  DWORD *entryPoint = (DWORD*)&executable[0x130];
  *entryPoint = 0x000FDF86;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
  char path[1000];

  // get Starcraft's install path from the registry
  const char *subkey = "SOFTWARE\\Blizzard Entertainment\\Starcraft";
  HKEY keyHandle;
  if(ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER, subkey, NULL, KEY_READ, &keyHandle))
  {
      // Try Current_User hive first, then fall back on checking local machine
      // As a user-land program starcraft SHOULD install itself to the Current_User hive
      // might be overridden by the setting of 
      if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, subkey, NULL, KEY_READ, &keyHandle)) {
          MessageBox(NULL, "Starcraft is not installed (Registry key missing). Cannot install BWDI", title, MB_ICONERROR|MB_OK);
          exit(1);
      }
  }

  if(ERROR_SUCCESS != RegQueryValueEx(keyHandle, "InstallPath", NULL, NULL, (LPBYTE)InstallPath, &InstallPathLength))
  {
    MessageBox(NULL, "Error reading the registry. Cannot install BWDI", title, MB_ICONERROR|MB_OK);
    exit(1);
  }

  RegCloseKey(keyHandle);

  try
  {
    // patch starcraft.exe
    BinaryLoader starcraft;
    sprintf(path, "%s\\Starcraft.exe", InstallPath);
    starcraft.loadFromFile(path);

    // check if starcraft.exe is the 1.16.1 version
    // checksum of .text only
    DWORD chk = calculateChecksum(starcraft.buffer + 0x1000, min(0xFD000, starcraft.bufferSize - 0x1000));

    // debug checksum
    /*
      char buffer[1000];
      sprintf_s(buffer, 1000, "Starcraft.exe checksum: %#08x", chk);
      MessageBox(NULL, buffer, "Debug message", 0);
      exit(1);
    */

    // .text hash
    if(chk != 0xab41666b)
    {
      MessageBox(NULL, "Starcraft is not version 1.16.1, please update Starcraft (just log on to Battle.net, it will update automatically). Cannot install BWDI", title, MB_ICONERROR|MB_OK);
      exit(1);
    }

    patchBWDILoader(starcraft.buffer);
    patchIcons(starcraft.buffer, starcraft.bufferSize);
    patchMultipleInstances(starcraft.buffer);

    starcraft.saveToFile("F:\\prog\\BWDI_Starcraft.exe");
  }
  catch(std::exception &e)
  {
    char buffer[512];
    sprintf_s(buffer, sizeof(buffer), "Could not finish installing: %s", e.what());
    MessageBox(NULL, buffer, title, 16);
    exit(1);
  }

  MessageBox(NULL, "BWDI successfully installed", title, MB_OK);
	return 0;
}
