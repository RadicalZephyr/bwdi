#pragma once
#include <string>
#include <set>
#include <map>

#include <BWDI\Race.h>
#include <BWDI\UpgradeType.h>
#include <BWDI\UpgradeTypeID.h>
namespace BWDI
{
  class UpgradeTypeInternal : public UpgradeType
  {
    public:
      std::set<UnitTypeID> whatUses;
      bool valid;
  };
  extern UpgradeTypeInternal upgradeTypeData[UpgradeTypeIDs::count];
  extern std::map<std::string, UpgradeTypeID> upgradeTypeMap;
  extern std::set< UpgradeTypeID > upgradeTypeSet;
  namespace UpgradeTypes
  {
    UpgradeTypeID getIDByName(const std::string& name);
    void init();
  }
}
