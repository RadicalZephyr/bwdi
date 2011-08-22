#pragma once

#include <Util\Types.h>

#include <memory.h>

namespace BW
{
  struct Bitmap
  {
    u16 wid;
    u16 ht;
    u8  *data;
  };

  struct FntChr
  {
    BYTE w, h, x, y;
    BYTE data[1];
  };

  struct FntHead
  {
    DWORD   magic;
    BYTE    low, high, Xmax, Ymax;
    FntChr  *chrs[1];
  };

  int     GetTextWidth(const char *pszString, BYTE bSize);  // Retrieves the width of the text string
  int     GetTextHeight(const char *pszString, BYTE bSize); // Retrieves the height of the text string
  bool    BlitText(const char *pszString, Bitmap *dst, int x, int y, BYTE bSize); // Draws a string of text to a destination bitmap buffer

  static void inline drawDot(int x, int y, int color)
  {
    Bitmap const* BWDATA_GameScreenBuffer = (Bitmap*) 0x006CEFF0;
    if(x >= 0 && x < 640 && y >= 0 && y < 480)
      BWDATA_GameScreenBuffer->data[y*640 + x] = color;
  }
  // efficient scanline code used by BWDI's drawing functions,
  // based on drawDot, but more efficient, especially with optimisation on
  static void inline drawScanLine(int x, int y, int width, int color)
  {
    Bitmap const* BWDATA_GameScreenBuffer = (Bitmap*) 0x006CEFF0;
    if(x+width >= 0 && x < 640 && y >= 0 && y < 480)
    {
      if(x + width > 640)
      {
        width = 640 - x;
      }
      if(x < 0)
      {
        width += x;
        x = 0;
      }
      memset(&(BWDATA_GameScreenBuffer->data[y*640 + x]), color, width);
    }
  }
  extern void drawBox(int x, int y, int w, int h, int color);
  extern void drawText(int x, int y, const char* ptext, int size);
}
