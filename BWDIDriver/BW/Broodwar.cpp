#include "Broodwar.h"
#include "Command.h"
#include "Latency.h"
#include "Offsets.h"
#include "CheatFlags.h"
#include "CheatType.h"

#include <DLLMain.h>

#include <Util/StaticArray.h>
#include <Util/Exceptions.h>

namespace BW
{
//public:
  //----------------------------------- IN REPLAY -----------------------------------------
  bool isInReplay()
  {
    return *(BW::BWDATA_InReplay) != 0;
  }
  //----------------------------------- IN MATCH ------------------------------------------
  bool isInGame()
  {
    return *(BW::BWDATA_InGame) != 0;
  }
  //----------------------------------- MULTIPLAYER ---------------------------------------
  bool isMultiplayer()
  {
    return *BW::BWDATA_NetMode != 0 && *BW::BWDATA_NetMode != -1;
  }
  //----------------------------------- SINGLEPLAYER --------------------------------------
  bool isSingleplayer()
  {
    return !isMultiplayer();
  }
  //----------------------------------- IS PAUSED -----------------------------------------
  bool isPaused()
  {
    return *BW::BWDATA_IsRunning == 0;
  }
  //----------------------------------- GET MOUSE X ---------------------------------------
  int getMouseX()
  {
    // Retrieves the mouse's X coordinate
    return BW::BWDATA_Mouse->x;
  }
  //----------------------------------- GET MOUSE Y ---------------------------------------
  int getMouseY()
  {
    // Retrieves the mouse's Y coordinate
    return BW::BWDATA_Mouse->y;
  }
  //----------------------------------- GET MOUSE POS -------------------------------------
  Position getMousePos()
  {
    return Position(BW::BWDATA_Mouse->x, BW::BWDATA_Mouse->y);
  }
  //----------------------------------- GET SCREEN X --------------------------------------
  int getScreenX()
  {
    // Retrieves the screen's X coordinate in relation to the map
    return *(BW::BWDATA_ScreenX);
  }
  //----------------------------------- GET SCREEN Y --------------------------------------
  int getScreenY()
  {
    // Retrieves the screen's Y coordinate in relation to the map
    return *(BW::BWDATA_ScreenY);
  }
  //----------------------------------- GET SCREEN POS ------------------------------------
  Position getScreenPos()
  {
    return Position(*(BW::BWDATA_ScreenX), *(BW::BWDATA_ScreenY));
  }
  //-------------------------------- SET SCREEN POSITION ----------------------------------
  void setScreenPosition(Position pos)
  {
    int x = pos.x, y = pos.y;
    BW::rect scrLimit = { 0, 0, BW::BWDATA_GameScreenBuffer->wid, BW::BWDATA_GameScreenBuffer->ht };
    /* Sets the screen's position relative to the map */
    if (x < 0)
      x = 0;
    if (y < 0)
      y = 0;
    if (x > BW::BWDATA_MapSize->x  * 32 - scrLimit.Xmax)
      x = BW::BWDATA_MapSize->x * 32 - scrLimit.Xmax;
    if (y > BW::BWDATA_MapSize->y * 32 - (scrLimit.Ymax + 80))
      y = BW::BWDATA_MapSize->y * 32 - (scrLimit.Ymax + 80);

    x &= 0xFFFFFFF8;
    y &= 0xFFFFFFF8;
    *BW::BWDATA_MoveToX = x;
    BW::BWDATA_MoveToTile->x = (u16)(x >> 5);
    *BW::BWDATA_MoveToY = y;
    BW::BWDATA_MoveToTile->y = (u16)(y >> 5);
    BW::BWFXN_UpdateScreenPosition();
  }
  //------------------------------------ START GAME ---------------------------------------
  void startGame()
  {
    // Starts the game as a lobby host
    issueCommand(BW::Command::StartGame());
  }
  //------------------------------------ PAUSE GAME ---------------------------------------
  void pauseGame()
  {
    // Pauses the game
    issueCommand(BW::Command::PauseGame());
  }
  //------------------------------------ RESUME GAME --------------------------------------
  void resumeGame()
  {
    // Resumes the game
    issueCommand(BW::Command::ResumeGame());
  }
  //------------------------------------- LEAVE GAME --------------------------------------
  void leaveGame()
  {
    // Leaves the current game. Moves directly to the post-game score screen
  }
  //------------------------------------- RESTART GAME ------------------------------------
  void restartGame()
  {
    // Restarts the current match 
    // Does not work on Battle.net
  }
  //------------------------------------- GET LATENCY -------------------------------------
  int getLatency()
  {
    // Returns the real latency values

    // special case
    if (BW::isSingleplayer())
      return BW::Latencies::Singleplayer;

    /* Lame options checking */
    switch(*BW::BWDATA_Latency)
    {
      case 0:
        return BW::Latencies::LanLow;
      case 1:
        return BW::Latencies::LanMedium;
      case 2:
        return BW::Latencies::LanHigh;
      default:
        return BW::Latencies::LanLow;
    }
  }
  //--------------------------------- GAME SPEED ------------------------------------------
  void resetLocalSpeed()
  {
    BW::BWDATA_GameSpeedModifiers[0] = 501;
    BW::BWDATA_GameSpeedModifiers[1] = 333;
    BW::BWDATA_GameSpeedModifiers[2] = 249;
    BW::BWDATA_GameSpeedModifiers[3] = 201;
    BW::BWDATA_GameSpeedModifiers[4] = 168;
    BW::BWDATA_GameSpeedModifiers[5] = 144;
    BW::BWDATA_GameSpeedModifiers[6] = 126;
  }
  void setLocalSpeed(int speed)
  {
    // Sets the frame rate of the client
    if (speed < 0)
    {
      // Reset the speed if it is negative
      resetLocalSpeed();
    }
    else
    {
      // Set all speeds if it is positive
      for (int i = 0; i < 7; i++)
        BW::BWDATA_GameSpeedModifiers[i] = speed;
    }
  }
  //------------------------------------ CHANGE SLOT ---------------------------------------
  void changeSlot(BW::SlotID slot, BW::SlotStateID slotState)
  {
    issueCommand(BW::Command::ChangeSlot(slot, slotState));
  }
  //------------------------------------ CHANGE RACE ---------------------------------------
  void changeRace(int raceId)
  {
    issueCommand(BW::Command::ChangeRace((SlotID)(BWDATA_selfPlayerID),(RaceID)raceId));
  }
  //-------------------------------------- PRINTF ------------------------------------------
#define vstretchyprintf(buff,fmt) {\
  va_list ap;\
  va_start(ap, fmt);\
  int buffsize = _vscprintf(fmt, ap);\
  buff = new char[buffsize+1];\
  vsprintf_s(buff, buffsize+1, fmt, ap);\
  va_end(ap);\
}
  void printf(const char* text, ...)
  {
    // TODO: capsulate formatting to one function
    Util::StaticArray<char, 2048> buffer;
    va_list ap;
    va_start(ap, text);
    vsnprintf_s(buffer.data, buffer.size, buffer.size, text, ap);
    va_end(ap);

    s_evt evt;
    evt.dwFlags    = 4;
    evt.dwPlayerId = -1;
    evt.pData      = (BYTE*)buffer.data;
    evt.dwSize     = strlen(buffer.data) + 1;

    SEvtDispatch('SNET', 1, 4, &evt);
  }
  //--------------------------------- PRINT WITH PLAYER ID ---------------------------------
  void sendTextEx(int playerID, const char *format, ...)
  {
    if ( !format ) return;
    char *buffer;
    vstretchyprintf(buffer, format);

    if ( buffer[0] == '/' )
    {
      SNetSendServerChatCommand(buffer);
      delete buffer;
      return;
    }

    if (isInReplay())
    {
      printf("%s", buffer);
      delete buffer;
      return;
    }

    if (isInGame() &&isSingleplayer())
    {
/*
      BW::CheatFlags::Enum cheatID = BW::getCheatFlag(buffer);
      if (cheatID != BW::CheatFlags::None)
      {
        this->cheatFlags ^= cheatID;
        QueueGameCommand((PBYTE)&BW::Orders::UseCheat(this->cheatFlags), sizeof(BW::Orders::UseCheat));
        if (cheatID == BW::CheatFlags::ShowMeTheMoney ||
            cheatID == BW::CheatFlags::BreatheDeep ||
            cheatID == BW::CheatFlags::WhatsMineIsMine ||
            cheatID == BW::CheatFlags::SomethingForNothing)
          this->cheatFlags ^= cheatID;
      }
      else*/
      {
        printf(buffer);
      }
      delete buffer;
      return;
    }

    char szMessage[82];
    szMessage[0] = 0;
    szMessage[1] = 1;
    int msgLen = SStrCopy(&szMessage[2], buffer, 80);

    if (isInGame())
    {
      SNetSendMessage(BW::BWDATA_Players[playerID].stormID, szMessage, msgLen + 3);
    }
    else
    {
      szMessage[1] = 0x4C;
      SNetSendMessage(-1, &szMessage[1], msgLen + 2);
    } // isInGame
    delete buffer;
  }
  void sendText(const char* format, ...)
  {
    if ( !format ) return;
    char *buffer;
    vstretchyprintf(buffer, format);
    sendTextEx(-1, "%s", buffer);
    delete buffer;
  }
  //---------------------------------------------- QUEUE COMMAND -----------------------------------------------
  void __fastcall issueCommandFromMemory(BYTE *buffer, DWORD length)
  {
    CAPS caps;
    caps.dwSize = sizeof(CAPS);
    SNetGetProviderCaps(&caps);

    u32 maxBuffer = caps.maxmessagesize;
    if ( maxBuffer > 512 )
      maxBuffer = 512;

    if ( length + *BW::BWDATA_sgdwBytesInCmdQueue <= maxBuffer )
    {
      // Copy data to primary turn buffer
      memcpy(&BW::BWDATA_TurnBuffer[*BW::BWDATA_sgdwBytesInCmdQueue], buffer, length);
      *BW::BWDATA_sgdwBytesInCmdQueue += length;
      return;
    }
    
    // Verify game mode
    if ( *BW::BWDATA_gwGameMode == 4 )
      return;

    int turns;
    if ( SNetGetTurnsInTransit(&turns) ) // Buffer is full
    {
      int callDelay = 1;
      if ( *BW::BWDATA_NetMode )
      {
        callDelay = caps.dwCallDelay;
        if ( callDelay > 8 )
          callDelay = 8;
        else if ( callDelay < 2 )
          callDelay = 2;
      }
      // This statement will probably never be hit, but just in case
      if ( turns >= 16 - callDelay )
        return;

      // Send the turn and fill the new buffer
      BW::BWFXN_sendTurn();
      memcpy(&BW::BWDATA_TurnBuffer[*BW::BWDATA_sgdwBytesInCmdQueue], buffer, length);
      *BW::BWDATA_sgdwBytesInCmdQueue += length;
    }
    // assume no error, would fatal anyway
  }
  // --------------------------------------------- PROCESS COMMANDS ----------------------------------
  void executeCommandBuffer(int playerIndex, Util::MemoryFrame data, bool asReplay)
  {
    void *cmdBuffer = data.begin();
    u32 cmdSize = data.size();
    u32 replay = asReplay;

    u32 lastActiveHumanID = *BW::BWDATA_g_ActiveHumanID;
    u32 lastActiveNationID = *BW::BWDATA_g_ActiveNationID;
//    u32 lastActiveStormID = *BW::BWDATA_g_ActiveStormID;

    *BW::BWDATA_g_ActiveHumanID = playerIndex;
    *BW::BWDATA_g_ActiveNationID = playerIndex;

    __asm 
    {
      mov eax, replay;
      push eax;
      mov eax, cmdSize;
      push eax;
      mov eax, cmdBuffer;
      call BW::BWFXN_Game_RECV; // void __userpurge Game_RECV(char *a1<eax>, int dataLen, bool asReplay)
    }

    *BW::BWDATA_g_ActiveHumanID = lastActiveHumanID;
    *BW::BWDATA_g_ActiveNationID = lastActiveNationID;
//    *BW::BWDATA_g_ActiveStormID = lastActiveStormID;
  }
}
