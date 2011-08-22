#pragma once
#include <BWDI\UnitType.h>
#include <BWDI\UnitTypeID.h>

#include <string>
#include <map>
#include <set>

namespace BWDI
{
  namespace UnitTypes
  {
    class UnitTypeInternal : public UnitType
    {
    public:
      std::map< UnitTypeID, int > requiredUnits;
      std::set< TechTypeID > abilities;
      std::set< UpgradeTypeID > upgrades;
    };

    extern UnitTypeInternal unitTypeData[UnitTypeIDs::count];
    extern std::map<std::string, UnitTypeID> unitTypeMap;
    extern std::set< UnitTypeID > unitTypeSet;

    UnitTypeID getIDByName(std::string& name);
    void init();
  }
}
