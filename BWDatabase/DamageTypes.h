#pragma once

#include <BWDI\DamageType.h>
#include <BWDI\DamageTypeID.h>

#include <string>
#include <map>
#include <set>

namespace BWDI
{
  namespace DamageTypes
  {
    extern DamageType damageTypeData[DamageTypeIDs::count];
    extern std::map<std::string, DamageTypeID> damageTypeMap;
    extern std::set< DamageTypeID > damageTypeSet;

    DamageTypeID getIDByName(const std::string& name);
    void init();
  }
}
