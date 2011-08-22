#pragma once
#include <BWDI\Position.h>
#include <BWDI\CoordinateBase.h>
#include <Util\TypeHead.h>

namespace Bridge
{
  namespace DrawShape
  {
#pragma pack(push, 1)
#define UNIQUE_ID __LINE__
    struct Line : Util::TypeHead<UNIQUE_ID>
    {
      BWDI::CoordinateBase base;
      BWDI::Position from;
      BWDI::Position to;
      int color;
    };

    struct Ellipse : Util::TypeHead<UNIQUE_ID>
    {
      BWDI::CoordinateBase base;
      BWDI::Position pos;
      int sizex;
      int sizey;
      int color;
      bool isSolid;
    };

    struct Circle : Util::TypeHead<UNIQUE_ID>
    {
      BWDI::CoordinateBase base;
      BWDI::Position center;
      float radius;
      int color;
      bool isSolid;
    };

    struct Rectangle : Util::TypeHead<UNIQUE_ID>
    {
      BWDI::CoordinateBase base;
      BWDI::Position pos;
      BWDI::Position size;
      int color;
      bool isSolid;
    };

    struct Dot : Util::TypeHead<UNIQUE_ID>
    {
      BWDI::CoordinateBase base;
      BWDI::Position pos;
      int color;
    };

    struct Text : Util::TypeHead<UNIQUE_ID>
    {
      BWDI::CoordinateBase base;
      BWDI::Position pos;
      int size;
    };

    struct Triangle : Util::TypeHead<UNIQUE_ID>
    {
      BWDI::CoordinateBase base;
      BWDI::Position posa;
      BWDI::Position posb;
      BWDI::Position posc;
      int color;
      bool isSolid;
    };
#undef UNIQUE_ID
#pragma pack(pop)
  }
}
