#pragma once
/**
 *  In Broodwar memory, there are several chains of units.
 *  These are IDs we assign to each one. ChainID is used in
 *  UnitMirror to identify to which chain the unit slot corresponds
 */

namespace BWDI
{
  namespace UnitChainIDs
  {
    enum Enum
    {
      Unused = 0,
      Hidden,
      Visible,
      ScannerSweep
    };
  }
  typedef UnitChainIDs::Enum UnitChainID;
}
