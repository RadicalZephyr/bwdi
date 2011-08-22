#pragma once
/**
 *  In Broodwar memory, there are several chains of bullets.
 *  These are IDs we assign to each one. ChainID is used in
 *  BulletMirror to identify to which chain the bullet slot corresponds
 */

namespace BWDI
{
  namespace BulletChainIDs
  {
    enum Enum
    {
      Unused,
      Visible
    };
  }
  typedef BulletChainIDs::Enum BulletChainID;
}
