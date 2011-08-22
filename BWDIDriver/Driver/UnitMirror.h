#pragma once
/***********************************************************************
 *  The UnitMirror struct is a local proxy for the BW::Unit struct, with
 *  variables for lifetime detection
 *
 *******/

#include "UnitChainID.h"

#include <BW\Position.h>

#include <Util\Types.h>

#include <Bridge\SharedStuff.h>

#include <BWDI\UnitID.h>

namespace BWDI
{
  struct UnitMirror
  {
    // chain holds the chain in which this unit slot was found to
    // detect chain changes
    UnitChainID chain;

    // is true several frames before the unit gets removed from the chain
    bool          isDying;

    // is true then the unit is visible or cloaked but was been spotted
    bool          isNoticed;

    // position is needed to detect changes, for noticing the unit (isNoticed).
    BW::Position  position;

    // if this unit is known, this is it's personal KnownUnit entry
    UnitState*    knownUnit;       // saving, to not to have to recompute
    UnitID        knownUnitIndex;  // needed for removing from units
  };
}
