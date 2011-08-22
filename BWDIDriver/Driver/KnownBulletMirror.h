#pragma once
/***********************************************************************
 *  The KnownBulletMirror struct is a proxy of the BWAPI::KnownBullet struct,
 *  with additional private data the AI must not to know
 *
 *******/

#include <Util\Types.h>

namespace BWDI
{
  struct KnownBulletMirror
  {
    int bwBulletIndex;  // look up the bw bullet, when processing a command
  };
}
