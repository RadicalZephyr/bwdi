#pragma once
#include <string>
#include <map>
#include <set>

#include <BWDI\WeaponType.h>

namespace BWDI
{
  namespace WeaponTypes
  {
    class WeaponTypeInternal : public WeaponType
    {
      std::set<UnitTypeID> whatUses;
    public:
    };

    extern WeaponTypeInternal weaponTypeData[WeaponTypeIDs::count];
    extern std::map<std::string, WeaponTypeID> weaponTypeMap;
    extern std::set< WeaponTypeID > weaponTypeSet;
    extern std::set< WeaponTypeID > specialWeaponTypeSet;
    extern std::set< WeaponTypeID > normalWeaponTypeSet;

    extern void init();
  }
}
