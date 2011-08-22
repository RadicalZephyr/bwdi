#pragma once

#include <BWDI\TechType.h>
#include <BWDI\TechTypeID.h>

#include <string>
#include <map>
#include <set>


namespace BWDI
{
  namespace TechTypes
  {
    class TechTypeInternal : public TechType
    {
    public:
      std::set<UnitTypeID> whatUses;
      bool valid;
    };

    extern TechTypeInternal techTypeData[TechTypeIDs::count];
    extern std::map<std::string, TechTypeID> techTypeMap;
    extern std::set< TechTypeID > techTypeSet;

    TechTypeID getIDByName(const std::string& name);
    void init();
  }
}
