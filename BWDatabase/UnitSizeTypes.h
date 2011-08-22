#pragma once
#include <string>
#include <map>
#include <set>

#include <BWDI\UnitSizeType.h>
#include <BWDI\UnitSizeTypeID.h>

namespace BWDI
{
  namespace UnitSizeTypes
  {
    extern UnitSizeType unitSizeTypeData[UnitSizeTypeIDs::count];
    extern std::map<std::string, UnitSizeTypeID> unitSizeTypeMap;
    extern std::set< UnitSizeTypeID > unitSizeTypeSet;

    UnitSizeTypeID getIDByName(std::string& name);
    void init();
  }
}
