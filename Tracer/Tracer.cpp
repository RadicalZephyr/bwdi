// Tracer.cpp : Defines the entry point for the application.
//

//
// This is an Example AI with a GUI.
//

#include "stdafx.h"
#include "Tracer.h"

#include <BWDI.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
INT_PTR CALLBACK DlgMain(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI guiThread(LPVOID lpParameter);
HWND dialogHandle;

BWDI::StaticGameData *sgd;

char buffer[1000];

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
  CreateThread(NULL, NULL, guiThread, NULL, NULL, NULL);

  // init session
  BWDI::SessionInfo info;
  info.usingBWDIVersion = 0;
  strcpy_s(info.moduleName, sizeof(info.moduleName), "Tracer");
  info.allowMultipleSlots = true;
  info.allowProtoss = true;
  info.allowTerran = true;
  info.allowZerg = true;
  BWDI::SessionHandle session = BWDI::BWDICreate(&info);

  // position of global info output
  BWDI::Position statPos;

  while(true)
  {
    // synch with BWDI
    BWDI::SessionState sstate = BWDI::BWDIWaitForNextEvent();
    if(sstate == BWDI::SessionState_InternalError)
      return 1;

    // handle onMatchStart
    if(sstate == BWDI::SessionState_MatchStart)
    {
      BWDI::BWDIMessage("Tracer started");
      sgd = BWDI::BWDIGetStaticGameData();
    }

    // handle next frame
    if(sstate == BWDI::SessionState_MatchFrame)
    {
      statPos = BWDI::Position(1, -8);

      // grid
      if(IsDlgButtonChecked(dialogHandle, IDC_CHECK67) == BST_CHECKED)
      {
        BWDI::BuildPosition topLeft     (sgd->screenPosition / 32);
        BWDI::BuildPosition bottomRight (topLeft + sgd->screenSize / 32 + BWDI::Position(1, 1));
        BWDI::Position lineVector(0, sgd->screenSize.y);
        for(int x = topLeft.x; x < bottomRight.x; x++)
        {
          BWDI::Position lineBase(x*32, topLeft.y*32);
          BWDI::BWDIDrawLine(lineBase, lineBase + lineVector, BWDI::ColorIDs::Black, BWDI::CoordinateBases::Map);
        }
        lineVector = BWDI::Position(sgd->screenSize.x, 0);
        for(int y = topLeft.y; y < bottomRight.y; y++)
        {
          BWDI::Position lineBase(topLeft.x*32, y*32);
          BWDI::BWDIDrawLine(lineBase, lineBase + lineVector, BWDI::ColorIDs::Black, BWDI::CoordinateBases::Map);
        }
      }

      // regionID visualization
      if(IsDlgButtonChecked(dialogHandle, IDC_CHECK62) == BST_CHECKED)
      {
        BWDI::BuildPosition topLeft     (sgd->screenPosition / 8);
        BWDI::BuildPosition bottomRight (topLeft + sgd->screenSize / 8);
        for(int x = topLeft.x; x < bottomRight.x; x++)
        {
          for(int y = topLeft.y; y < bottomRight.y; y++)
          {
            BWDI::Position tilePos(x*8, y*8);
            BWDI::BWDIDrawLine(tilePos, tilePos + BWDI::Position(8, 0), sgd->regionID[y][x] & 0xFF, BWDI::CoordinateBases::Map);
          }
        }
      }

      // region center visualization
      if(IsDlgButtonChecked(dialogHandle, IDC_CHECK61) == BST_CHECKED)
      {
        for(uint i = 0; i < sgd->region.count; i++)
        {
          BWDI::Region &region = sgd->region.at(i);

          if( region.center.x < sgd->screenPosition.x ||
              region.center.x > sgd->screenPosition.x + sgd->screenSize.x ||
              region.center.y < sgd->screenPosition.y ||
              region.center.y > sgd->screenPosition.y + sgd->screenSize.y)
              continue;

          BWDI::BWDIDrawCircle(region.center, 3, BWDI::ColorIDs::Cyan, true, BWDI::CoordinateBases::Map);
          sprintf_s(buffer, sizeof(buffer), "nbrs: %d", region.neighbors.count);
          BWDI::BWDIDrawText(region.center, buffer, 1, BWDI::CoordinateBases::Map);
          sprintf_s(buffer, sizeof(buffer), "_dbg: %d%d%d%d", !!(region.flags&8), !!(region.flags&4), !!(region.flags&2), !!(region.flags&1));
          BWDI::BWDIDrawText(region.center + BWDI::Position(0, 9), buffer, 1, BWDI::CoordinateBases::Map);

          // neighbor lines
          for(uint n = 0; n < region.neighbors.count; n++)
          {
            uint neighborID = region.neighbors.at(n);

            BWDI::BWDIDrawLine(region.center, sgd->region.at(neighborID).center, BWDI::ColorIDs::Cyan, BWDI::CoordinateBases::Map);
          }
        }
      }

      // visibility visualization
      if(IsDlgButtonChecked(dialogHandle, IDC_CHECK44) == BST_CHECKED)
      {
        BWDI::BuildPosition topLeft     (sgd->screenPosition / 32);
        BWDI::BuildPosition bottomRight (topLeft + sgd->screenSize / 32);
        for(int x = topLeft.x; x < bottomRight.x; x++)
        {
          for(int y = topLeft.y; y < bottomRight.y; y++)
          {
            if(sgd->isVisible[y][x])
              continue;
            BWDI::Position tilePos(x*32, y*32);
            BWDI::BWDIDrawLine(tilePos + BWDI::Position(0, 32), tilePos + BWDI::Position(32, 0), BWDI::ColorIDs::Grey, BWDI::CoordinateBases::Map);
          }
        }
      }
      // exploration visualization
      if(IsDlgButtonChecked(dialogHandle, IDC_CHECK45) == BST_CHECKED)
      {
        BWDI::BuildPosition topLeft     (sgd->screenPosition / 32);
        BWDI::BuildPosition bottomRight (topLeft + sgd->screenSize / 32);
        for(int x = topLeft.x; x < bottomRight.x; x++)
        {
          for(int y = topLeft.y; y < bottomRight.y; y++)
          {
            if(sgd->isExplored[y][x])
              continue;
            BWDI::Position tilePos(x*32, y*32);
            BWDI::BWDIDrawLine(tilePos + BWDI::Position( 0, 16), tilePos + BWDI::Position(16,  0), BWDI::ColorIDs::Grey, BWDI::CoordinateBases::Map);
            BWDI::BWDIDrawLine(tilePos + BWDI::Position(16, 32), tilePos + BWDI::Position(32, 16), BWDI::ColorIDs::Grey, BWDI::CoordinateBases::Map);
          }
        }
      }
      // creep visualization
      if(IsDlgButtonChecked(dialogHandle, IDC_CHECK46) == BST_CHECKED)
      {
        BWDI::BuildPosition topLeft     (sgd->screenPosition / 32);
        BWDI::BuildPosition bottomRight (topLeft + sgd->screenSize / 32);
        for(int x = topLeft.x; x < bottomRight.x; x++)
        {
          for(int y = topLeft.y; y < bottomRight.y; y++)
          {
            if(!sgd->hasCreep[y][x])
              continue;
            BWDI::Position tilePos(x*32 + 16*(y%2), y*32);
            BWDI::BWDIDrawLine(tilePos + BWDI::Position(16, 0), tilePos + BWDI::Position(0, 32), BWDI::ColorIDs::Grey, BWDI::CoordinateBases::Map);
          }
        }
      }
      // buildability visualization
      if(IsDlgButtonChecked(dialogHandle, IDC_CHECK1) == BST_CHECKED)
      {
        BWDI::BuildPosition topLeft     (sgd->screenPosition / 32);
        BWDI::BuildPosition bottomRight (topLeft + sgd->screenSize / 32);
        for(int x = topLeft.x; x < bottomRight.x; x++)
        {
          for(int y = topLeft.y; y < bottomRight.y; y++)
          {
            if(sgd->isBuildable[y][x])
              continue;
            BWDI::Position tilePos(x*32, y*32);
            BWDI::BWDIDrawLine(tilePos, tilePos + BWDI::Position(32, 32), BWDI::ColorIDs::Grey, BWDI::CoordinateBases::Map);
          }
        }
      }
      // ground height visualization
      if(IsDlgButtonChecked(dialogHandle, IDC_CHECK47) == BST_CHECKED)
      {
        char label[3] = "x0";
        char colors[] = {0x15, 0x05, 0x1E, 0x1F, 0x03, 0x04};
        BWDI::BuildPosition topLeft     (sgd->screenPosition / 32);
        BWDI::BuildPosition bottomRight (topLeft + sgd->screenSize / 32);
        for(int x = topLeft.x; x < bottomRight.x; x++)
        {
          for(int y = topLeft.y; y < bottomRight.y; y++)
          {
            int h = sgd->groundHeight[y][x];
            label[0] = colors[h];
            label[1] = '0' + h;
            BWDI::BWDIDrawText(BWDI::Position(x, y) * 32, label, 1, BWDI::CoordinateBases::Map);
          }
        }
      }
      // walkability visualization
      if(IsDlgButtonChecked(dialogHandle, IDC_CHECK2) == BST_CHECKED)
      {
        char label[2] = "0";
        BWDI::BuildPosition topLeft     (sgd->screenPosition / 8);
        BWDI::BuildPosition bottomRight (topLeft + sgd->screenSize / 8);
        for(int x = topLeft.x; x < bottomRight.x; x++)
        {
          for(int y = topLeft.y; y < bottomRight.y; y++)
          {
            if(sgd->isWalkable[y][x])
              continue;
            BWDI::Position tilePos(x*8, y*8);
            BWDI::BWDIDrawLine(tilePos + BWDI::Position(0, 8), tilePos + BWDI::Position(8, 0), BWDI::ColorIDs::Grey, BWDI::CoordinateBases::Map);
          }
        }
      }

      // unit visualisation
      BWDI::Position textPos;
      for each(int unitID in sgd->units)
      {
        BWDI::UnitState &unit = sgd->units[unitID];
        textPos = unit.position + BWDI::Position(5, -10);

        if(IsDlgButtonChecked(dialogHandle, IDC_CHECK6) == BST_CHECKED)
          BWDI::BWDIDrawCircle(unit.position,  3, BWDI::ColorIDs::Green, false, BWDI::CoordinateBases::Map);

#define DrawStat_If(IDC_CHECK_NUM, TEXTPOS, COORD, ...) \
if(IsDlgButtonChecked(dialogHandle, IDC_CHECK_NUM) == BST_CHECKED) \
{ \
  sprintf_s(buffer, sizeof(buffer), __VA_ARGS__); \
  BWDI::BWDIDrawText(TEXTPOS += BWDI::Position(0, 9), buffer, 1, BWDI::CoordinateBases::COORD); \
}
        DrawStat_If(IDC_CHECK51, textPos, Map, "clr: %d",   unit.clearanceLevel);
        DrawStat_If(IDC_CHECK52, textPos, Map, "sID: %X",   unit.sightingID);
        DrawStat_If(IDC_CHECK53, textPos, Map, "acc: %d",   unit.isAccelerating);
        DrawStat_If(IDC_CHECK54, textPos, Map, "mov: %d",   unit.isMoving);
        DrawStat_If(IDC_CHECK55, textPos, Map, "idle: %d",  unit.isIdle);
        DrawStat_If(IDC_CHECK56, textPos, Map, "mov: %d",   unit.angle);
        DrawStat_If(IDC_CHECK57, textPos, Map, "v: %d/%d",  unit.velocity.x, unit.velocity.y);
        DrawStat_If(IDC_CHECK58, textPos, Map, "storm: %d", unit.isUnderStorm);
        DrawStat_If(IDC_CHECK59, textPos, Map, "type: %s",  sgd->unitTypes[unit.type].name.c_str());
        DrawStat_If(IDC_CHECK5,  textPos, Map, "player: %d",unit.player);
        DrawStat_If(IDC_CHECK7,  textPos, Map, "HP: %d",    unit.hitPoints);
        DrawStat_If(IDC_CHECK8,  textPos, Map, "sh: %d",    unit.shield);
        DrawStat_If(IDC_CHECK9 , textPos, Map, "enrg: %d",  unit.energy);
        DrawStat_If(IDC_CHECK10, textPos, Map, "res: %d",   unit.resources);
        DrawStat_If(IDC_CHECK11, textPos, Map, "kills: %d", unit.killCount);
        DrawStat_If(IDC_CHECK12, textPos, Map, "constr: %d",unit.isBeingConstructed);
        DrawStat_If(IDC_CHECK13, textPos, Map, "gathr: %d", unit.isBeingGathered);
        DrawStat_If(IDC_CHECK14, textPos, Map, "heal: %d",  unit.isBeingHealed);
        DrawStat_If(IDC_CHECK15, textPos, Map, "blind: %d", unit.isBlind);
        DrawStat_If(IDC_CHECK16, textPos, Map, "brake: %d", unit.isBraking);
        DrawStat_If(IDC_CHECK17, textPos, Map, "burrow: %d",unit.isBurrowed);
        DrawStat_If(IDC_CHECK18, textPos, Map, "cgas: %d",  unit.isCarryingGas);
        DrawStat_If(IDC_CHECK19, textPos, Map, "cmins: %d", unit.isCarryingMinerals);
        DrawStat_If(IDC_CHECK20, textPos, Map, "cloak: %d", unit.isCloaked);
        DrawStat_If(IDC_CHECK21, textPos, Map, "compl: %d", unit.isCompleted);
        DrawStat_If(IDC_CHECK22, textPos, Map, "constr: %d",unit.isConstructing);
        DrawStat_If(IDC_CHECK23, textPos, Map, "matrix: %d",unit.isDefenseMatrixed);
        DrawStat_If(IDC_CHECK24, textPos, Map, "ensnr: %d", unit.isEnsnared);
        DrawStat_If(IDC_CHECK25, textPos, Map, "follow: %d",unit.isFollowing);
        DrawStat_If(IDC_CHECK26, textPos, Map, "ggas: %d",  unit.isGatheringGas);
        DrawStat_If(IDC_CHECK27, textPos, Map, "gmins: %d", unit.isGatheringMinerals);
        DrawStat_If(IDC_CHECK28, textPos, Map, "irrad: %d", unit.isIrradiated);
        DrawStat_If(IDC_CHECK29, textPos, Map, "lift: %d",  unit.isLifted);
        DrawStat_If(IDC_CHECK30, textPos, Map, "lock: %d",  unit.isLockedDown);
        DrawStat_If(IDC_CHECK31, textPos, Map, "mael: %d",  unit.isMaelstrommed);
        DrawStat_If(IDC_CHECK32, textPos, Map, "morph: %d", unit.isMorphing);
        DrawStat_If(IDC_CHECK33, textPos, Map, "para: %d",  unit.isParasited);
        DrawStat_If(IDC_CHECK34, textPos, Map, "patr: %d",  unit.isPatrolling);
        DrawStat_If(IDC_CHECK35, textPos, Map, "plag: %d",  unit.isPlagued);
        DrawStat_If(IDC_CHECK36, textPos, Map, "repr: %d",  unit.isRepairing);
        DrawStat_If(IDC_CHECK37, textPos, Map, "resr: %d",  unit.isResearching);
        DrawStat_If(IDC_CHECK38, textPos, Map, "sel: %d",   unit.isSelected);
        DrawStat_If(IDC_CHECK39, textPos, Map, "stas: %d",  unit.isStasised);
        DrawStat_If(IDC_CHECK40, textPos, Map, "stim: %d",  unit.isStimmed);
        DrawStat_If(IDC_CHECK41, textPos, Map, "train: %d", unit.isTraining);
        DrawStat_If(IDC_CHECK42, textPos, Map, "unpow: %d", unit.isUnpowered);
        DrawStat_If(IDC_CHECK43, textPos, Map, "upgr: %d",  unit.isUpgrading);
        DrawStat_If(IDC_CHECK60, textPos, Map, "_dbg: %d",  unit._debug);

      } // for each unit

      // map info
      DrawStat_If(IDC_CHECK48, statPos, Screen, "mapFilename: %s",  sgd->mapFilename.c_str());
      DrawStat_If(IDC_CHECK48, statPos, Screen, "mapName: %s",  sgd->mapName.c_str());
      DrawStat_If(IDC_CHECK48, statPos, Screen, "mapHash: %d",  sgd->mapHash);
      DrawStat_If(IDC_CHECK48, statPos, Screen, "mapSize: %d,%d",  sgd->mapSize.x, sgd->mapSize.y);

      // units info
      DrawStat_If(IDC_CHECK49, statPos, Screen, "units.count: %d",  sgd->units.count);
      DrawStat_If(IDC_CHECK49, statPos, Screen, "unitsAdded.count: %d",  sgd->unitsAdded.count);
      DrawStat_If(IDC_CHECK49, statPos, Screen, "unitsRemoved.count: %d",  sgd->unitsRemoved.count);

      //DrawStat_If(IDC_CHECK50, statPos, "bullets.count",  sgd->bullets.count);

      BWDI::BWDIDrawText(statPos += BWDI::Position(0, 9), "end.", 1, BWDI::CoordinateBases::Screen);
    }
  }
  return 0;
}

// Message handler for about box.
INT_PTR CALLBACK DlgMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  dialogHandle = hDlg;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

DWORD WINAPI guiThread(LPVOID lpParameter)
{
  DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), NULL, DlgMain);
  return 0;
}
