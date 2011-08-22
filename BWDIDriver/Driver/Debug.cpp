#include "Debug.h"

#include <BW\Offsets.h>
#include <BW\Broodwar.h>
#include <BW\Pathing.h>

#include <BWDI\ColorID.h>

#include "Shape.h"

namespace BWDI
{
  void dbgDrawText(BW::Position pos, const char* text)
  {
    pos -= BW::getScreenPos();
    BW::drawText(pos.x, pos.y, text, 1);
  }

  void drawMapLine(BW::Position pos1, BW::Position pos2, int color)
  {
    pos1 -= BW::getScreenPos();
    pos2 -= BW::getScreenPos();
    drawLine(pos1.x, pos1.y, pos2.x, pos2.y, color);
  }

  void dbgDraw()
  {
    /*
    int offset = 0;
    // debug contours
    if(BW::BWDATA_SAIPathing)
    {
      BW::contourHub &hub = BW::BWDATA_SAIPathing->contoursMain[0];
//      for(uint i = 0; i < BW::BWDATA_SAIPathing->regionCount; i++)
      {
        BW::Position pos1;
        BW::Position pos2;
        BW::contour *contour = hub.contours[0];
        for(int s = 0; s < hub.contourCount[0]; s++)
        {
          offset = (offset+1) % 3;
          pos1.y = pos2.y = contour[s].v[0] + offset-2;
          pos1.x = contour[s].v[1];
          pos2.x = contour[s].v[2];
          drawMapLine(pos1, pos2, ColorIDs::Cyan);
        }
      }
    }
    */
    /*
    // debug map tile data
    char textBuffer[1024];
    for(int y = 0; y < BW::BWDATA_MapSize->y; y++)
    {
      for(int x = 0; x < BW::BWDATA_MapSize->x; x++)
      {
        sprintf_s(textBuffer, sizeof(textBuffer), "%d", BW::BWDATA_SAIPathing->mapTileRegionId[y][x] & 0x1FFF);
        dbgDrawText(BW::Position(x*32, y*32), textBuffer);
        sprintf_s(textBuffer, sizeof(textBuffer), "%d", BW::BWDATA_SAIPathing->mapTileRegionId[y][x] >> 13);
        dbgDrawText(BW::Position(x*32, y*32+9), textBuffer);
      }
    }
    */
  }
};
