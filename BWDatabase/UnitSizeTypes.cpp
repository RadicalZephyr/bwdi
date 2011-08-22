#include "UnitSizeTypes.h"

#include <BWDI/UnitSizeTypeID.h>

namespace BWDI
{
  namespace UnitSizeTypes
  {
    UnitSizeType unitSizeTypeData[UnitSizeTypeIDs::count];
    std::map<std::string, UnitSizeTypeID> unitSizeTypeMap;
    std::set< UnitSizeTypeID > unitSizeTypeSet;

    void fillUnitSizeType(UnitSizeTypeID id, const char* name)
    {
      UnitSizeType &target = unitSizeTypeData[id];
      target.name.set(name);
    }

    void init()
    {
      fillUnitSizeType(UnitSizeTypeIDs::Independent, "Independent");
      fillUnitSizeType(UnitSizeTypeIDs::Small, "Small");
      fillUnitSizeType(UnitSizeTypeIDs::Medium, "Medium");
      fillUnitSizeType(UnitSizeTypeIDs::Large, "Large");
      fillUnitSizeType(UnitSizeTypeIDs::None, "None");

      unitSizeTypeSet.insert(UnitSizeTypeIDs::Independent);
      unitSizeTypeSet.insert(UnitSizeTypeIDs::Small);
      unitSizeTypeSet.insert(UnitSizeTypeIDs::Medium);
      unitSizeTypeSet.insert(UnitSizeTypeIDs::Large);
      unitSizeTypeSet.insert(UnitSizeTypeIDs::None);

      for(std::set<UnitSizeTypeID>::iterator i = unitSizeTypeSet.begin(); i != unitSizeTypeSet.end(); i++)
      {
        unitSizeTypeMap.insert(std::make_pair(std::string(unitSizeTypeData[*i].name), *i));
      }
    }
    UnitSizeTypeID getIDByName(const std::string& name)
    {
      std::map<std::string, UnitSizeTypeID>::iterator i = unitSizeTypeMap.find(name);
      if (i == unitSizeTypeMap.end()) return UnitSizeTypeIDs::None;
      return (*i).second;
    }
  }
}

