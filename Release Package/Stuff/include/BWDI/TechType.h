#pragma once

#include <BWDI\RaceID.h>
#include <BWDI\UnitTypeID.h>
#include <BWDI\WeaponTypeID.h>

#include <Util\StaticString.h>

namespace BWDI
{
  struct TechType
  {
    int id;
    RaceID race;
    int mineralPrice;
    int gasPrice;
    int energyUsed;
    UnitTypeID whatResearches;
    WeaponTypeID weapon;
    Util::StaticString<32> name;
    // const std::set<const UnitType*>& whatUses() const;
  };
}
