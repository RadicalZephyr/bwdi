#pragma once

#include "Position.h"

#include <Util\Types.h>
#include <Util\MemoryFrame.h>

namespace BW
{
//public:
  extern bool isInReplay();
  extern bool isInGame();
  extern bool isMultiplayer();
  extern bool isSingleplayer();
  extern bool isPaused();
  extern int getMouseX();
  extern int getMouseY();
  extern Position getMousePos();
  extern int getScreenX();
  extern int getScreenY();
  extern Position getScreenPos();
  extern int getLatency();
  extern void setLocalSpeed(int speed);
  extern void resetLocalSpeed();

  extern void changeRace(int raceId);

  extern void setScreenPosition(Position pos);
  extern void startGame();
  extern void pauseGame();
  extern void resumeGame();
  extern void leaveGame();
  extern void restartGame();

  void printf(const char* text, ...);
  void sendTextEx(int playerID, const char *format, ...);
  void sendText(const char* format, ...);

  void __fastcall issueCommandFromMemory(BYTE *buffer, DWORD length);
  // commands
  template<typename T>
    void issueCommand(T &cmdStruct)
    {
      issueCommandFromMemory((BYTE*)&cmdStruct, sizeof(T));
    }
    void executeCommandBuffer(int playerIndex, Util::MemoryFrame data, bool asReplay);
}
