#pragma once

#include <BWDI\ExplosionType.h>
#include <BWDI\ExplosionTypeID.h>

#include <string>
#include <set>
#include <map>

namespace BWDI
{
  namespace ExplosionTypes
  {
    class ExplosionTypeInternal : public ExplosionType
    {
    public:
    };

    extern ExplosionTypeInternal explosionTypeData[ExplosionTypeIDs::count];
    extern std::map<std::string, ExplosionTypeID> explosionTypeMap;
    extern std::set< ExplosionTypeID > explosionTypeSet;

    ExplosionTypeID getIDByName(const std::string& name);
    void init();
  }
}
