#include "Draw.h"

#include "Offsets.h"

namespace BW
{
  BYTE textColorTable[] = { 
     0,  0,  0,  1,  2,  3,  4,  5,  8,  0,  0,  0,  0,  0,  9, 10, 
    11, 12,  0,  0,  0, 13, 14, 15, 16, 17,  0, 18, 19, 20, 21, 23
  };

BYTE fontColors[24][8] = {
  { 0xC0, 0x9B, 0x9A, 0x95, 0x43, 0x00, 0x00, 0x28 }, 
  { 0x56, 0xA7, 0x6D, 0x65, 0x5C, 0x00, 0x00, 0x8A }, 
  { 0x41, 0xFF, 0x53, 0x97, 0x47, 0x00, 0x00, 0x8A }, 
  { 0x40, 0x96, 0x49, 0x90, 0x42, 0x00, 0x00, 0x8A }, 
  { 0xA8, 0xAE, 0x17, 0x5E, 0xAA, 0x00, 0x00, 0x8A }, 
  { 0xB5, 0x75, 0xBA, 0xB9, 0xB7, 0x00, 0x00, 0x8A }, 
  { 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08 }, 
  { 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08 }, 
  { 0x8A, 0x6F, 0x17, 0x5E, 0xAA, 0x8A, 0x8A, 0x8A }, 
  { 0x28, 0xA5, 0xA2, 0x2D, 0xA0, 0x8A, 0x8A, 0x8A }, 
  { 0x8A, 0x9F, 0x9E, 0x9D, 0xB7, 0x8A, 0x8A, 0x8A }, 
  { 0x8A, 0xA4, 0xA3, 0xA1, 0x0E, 0x8A, 0x8A, 0x8A }, 
  { 0x8A, 0x9C, 0x1C, 0x1A, 0x13, 0x8A, 0x8A, 0x8A }, 
  { 0x8A, 0x13, 0x12, 0x11, 0x57, 0x8A, 0x8A, 0x8A }, 
  { 0x8A, 0x54, 0x51, 0x4E, 0x4A, 0x8A, 0x8A, 0x8A }, 
  { 0x8A, 0x87, 0xA6, 0x81, 0x93, 0x8A, 0x8A, 0x8A }, 
  { 0xB5, 0xB9, 0xB8, 0xB7, 0xB6, 0x8A, 0x8A, 0x8A }, 
  { 0x8A, 0x88, 0x84, 0x81, 0x60, 0x8A, 0x8A, 0x8A }, 
  { 0x8A, 0x86, 0x72, 0x70, 0x69, 0x8A, 0x8A, 0x8A }, 
  { 0x8A, 0x33, 0x7C, 0x7A, 0xA0, 0x8A, 0x8A, 0x8A }, 
  { 0x8A, 0x4D, 0x26, 0x23, 0x22, 0x8A, 0x8A, 0x8A }, 
  { 0x8A, 0x9A, 0x97, 0x95, 0x91, 0x8A, 0x8A, 0x8A }, 
  { 0x8A, 0x88, 0x84, 0x81, 0x60, 0x8A, 0x8A, 0x8A }, 
  { 0x8A, 0x80, 0x34, 0x31, 0x2E, 0x8A, 0x8A, 0x8A }
};

  // ----------------- GET WIDTH ---------------------
  int GetTextWidth(const char *pszString, BYTE bSize)
  {
    // verify valid size index
    if ( bSize > 3 || !pszString )
      return 0;

    // localize pointer
    FntHead *font = BWDATA_FontBase[bSize];
    if ( !font )
      return 0;

    // Reference an unsigned character array
    const BYTE *pbChars = (BYTE*)pszString;

    // Retrieve size
    int dwSize = 0;
    for ( int i = 0; pbChars[i] != 0; ++i )
    {
      switch ( pbChars[i] )
      {
      case 9:
        dwSize += font->Xmax * 2;
        continue;
      case ' ':
        dwSize += font->Xmax >> 1;
        continue;
      }

      // must be valid character
      if ( pbChars[i] > font->high || pbChars[i] < font->low)
        continue;

      // localize character pointer
      FntChr *chr = font->chrs[pbChars[i] - font->low];
      if ( chr == (FntChr*)font )
        continue;

      // increase the size
      dwSize += chr->w;
    }
    return dwSize;
  }
  // ----------------- GET WIDTH ---------------------
  int GetTextHeight(const char *pszString, BYTE bSize)
  {
    // verify valid size index
    if ( bSize > 3 || !pszString )
      return 0;

    // localize pointer
    FntHead *font = BWDATA_FontBase[bSize];
    if ( !font )
      return 0;

    // Reference an unsigned character array
    const BYTE *pbChars = (BYTE*)pszString;

    // Retrieve size
    int dwSize = font->Ymax;
    for ( int i = 0; pbChars[i] != 0; ++i )
    {
      switch ( pbChars[i] )
      {
      case 10:
        dwSize += font->Ymax;
        break;
      }
    }
    return dwSize;
  }
  // ----------------- BLIT TEXT ---------------------
  bool BlitText(const char *pszString, Bitmap *dst, int x, int y, BYTE bSize)
  {
    // verify valid size index
    if ( bSize > 3 || !dst || !pszString )
      return false;

    // localize pointer
    FntHead *font = BWDATA_FontBase[bSize];
    if ( !font || !dst->data )
      return false;

    // Reference an unsigned character array
    const BYTE *pbChars = (BYTE*)pszString;

    char lastColor = 0; // grey
    char color     = textColorTable[7]; // green
    int  Xoffset   = 0;
    int  Yoffset   = 0;
    for ( int c = 0; pbChars[c] != 0; c++ )
    {
      // make sure char is valid
      if ( pbChars[c] == 1 )
      {
        color = lastColor;
        continue;
      }
      else if ( pbChars[c] < 33 )
      {
        switch ( pbChars[c] )
        {
        case 9:
          Xoffset += font->Xmax * 2;
          continue;
        case 10:
          Xoffset += x;
          Xoffset -= (Xoffset % (dst->wid));
          Yoffset += font->Ymax;
          continue;
        case 11:
        case 20:
          color = -1;
          continue;
        case 12:
          break;
        case 13:
        case 26:
          continue;
        case 18:
          Xoffset += dst->wid - GetTextWidth(pszString, bSize) - x;
          continue;
        case 19:
          Xoffset += dst->wid / 2 - GetTextWidth(pszString, bSize) / 2 - x;
          continue;
        case ' ':
          Xoffset += font->Xmax >> 1;
          continue;
        default:
          lastColor = color;
          color     = textColorTable[pbChars[c]];
          continue;
        }
      }

      if ( pbChars[c] > font->high || pbChars[c] < font->low)
        continue;

      // localize character pointer
      FntChr *chr = font->chrs[pbChars[c] - font->low];
      if ( chr == (FntChr*)font )
        continue;

      // begin drawing process
      int pos = 0;
      for ( int i = 0; pos < chr->h * chr->w; ++i )
      {
        pos += chr->data[i] >> 3;
        int dstY = chr->y + pos/chr->w;
        int dstX = chr->x + pos%chr->w;
        int offs = y * dst->wid + x + Yoffset * dst->wid;
        int final = offs + (dstY * dst->wid) + dstX + Xoffset;
        if ( final > 0 && final < dst->wid * dst->ht && color < 24 && (dstX + x + Xoffset) > 0 && (dstX + x + Xoffset) < dst->wid && (dstY + y + Yoffset) > 0 && (dstY + y + Yoffset) < dst->ht )
          dst->data[final] = fontColors[color][chr->data[i] & 0x07];
        pos++;
      }
      Xoffset += chr->w;
    }
    return true;
  }
  //----------------------------------- DRAW FUNCTIONS -------------------------------------
  bool inScreen(int x, int y)
  {
    return x >= 0
      && y >= 0
      && x < 640
      && y < 480;
  }
  void drawBox(int _x, int _y, int _w, int _h, int color)
  {
    static s16 x;
    static s16 y;
    static u16 w;
    static u16 h;
    x = (s16)_x;
    y = (s16)_y;
    w = (u16)_w;
    h = (u16)_h;
    if (x + w <= 0 || y + h <= 0 || x >= 639 || y >= 479)
      return;
    if (x + w > 639) w = 639 - x;
    if (y + h > 479) h = 479 - y;
    if (x < 0) {w += x; x = 0;}
    if (y < 0) {h += y; y = 0;}

    static u8*            BWDATA_DrawColor                          = (u8*) 0x006CF4AC;
    *BWDATA_DrawColor = (u8)color;
/*
    __asm
    {
      mov eax, drawRegisters.eax
      mov ebx, drawRegisters.ebx
      mov ecx, drawRegisters.ecx
      mov edx, drawRegisters.edx
    }*/
    static int (__stdcall* BWFXN_DrawMinimapBox)(s16 x, s16 y, u16 w, u16 h) = (int(__stdcall*)(s16,s16,u16,u16))0x004E1D20;
    BWFXN_DrawMinimapBox(x, y, w, h);
  }

  void drawText(int _x, int _y, const char* ptext, int size)
  {
    POINT pt = { _x, _y };
    if (pt.x + BW::GetTextWidth(ptext, size)  < 0 || 
        pt.y + BW::GetTextHeight(ptext, size) < 0 || 
        pt.x > BW::BWDATA_GameScreenBuffer->wid   || 
        pt.y > BW::BWDATA_GameScreenBuffer->ht)
      return;

    BW::BlitText(ptext, BW::BWDATA_GameScreenBuffer, pt.x, pt.y, size);
  }
};
