#pragma once
/***********************************************************************
 *  The BulletMirror struct is a local proxy for the BW::Bulletstruct, with
 *  variables for lifetime detection
 *
 *******/

#include "BulletChainId.h"

#include <BW\Position.h>

#include <Util\Types.h>

#include <Bridge\SharedStuff.h>

#include <BWDI\BulletID.h>

namespace BWDI
{
  struct BulletMirror
  {
    // chain holds the chain in which this unit slot was found to
    // detect chain changes
    BulletChainID chain;

    // if this bullet is known, this is it's KnownBullet entry
    BulletID        knownBulletIndex;
    BulletState*    knownBullet;       // saving, to not to have to recompute
  };
}
