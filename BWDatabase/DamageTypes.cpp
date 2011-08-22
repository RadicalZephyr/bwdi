#include "DamageTypes.h"

namespace BWDI
{
  namespace DamageTypes
  {
    DamageType damageTypeData[DamageTypeIDs::count];
    std::map<std::string, DamageTypeID> damageTypeMap;
    std::set< DamageTypeID > damageTypeSet;

    void fillDamageType(DamageTypeID id, const char* name)
    {
      DamageType &target = damageTypeData[id];
      target.name.set(name);
    }

    void init()
    {
      fillDamageType(DamageTypeIDs::Independent, "Independent");
      fillDamageType(DamageTypeIDs::Explosive, "Explosive");
      fillDamageType(DamageTypeIDs::Concussive, "Concussive");
      fillDamageType(DamageTypeIDs::Normal, "Normal");
      fillDamageType(DamageTypeIDs::Ignore_Armor, "Ignore Armor");
      fillDamageType(DamageTypeIDs::None, "None");

      damageTypeSet.insert(DamageTypeIDs::Independent);
      damageTypeSet.insert(DamageTypeIDs::Explosive);
      damageTypeSet.insert(DamageTypeIDs::Concussive);
      damageTypeSet.insert(DamageTypeIDs::Normal);
      damageTypeSet.insert(DamageTypeIDs::Ignore_Armor);
      damageTypeSet.insert(DamageTypeIDs::None);

      for(std::set<DamageTypeID>::iterator i = damageTypeSet.begin(); i != damageTypeSet.end(); i++)
      {
        damageTypeMap.insert(std::make_pair(std::string(damageTypeData[*i].name), *i));
      }
    }
  }

  namespace DamageTypes
  {
    DamageTypeID getIDByName(const std::string& name)
    {
      std::map<std::string, DamageTypeID>::iterator i = damageTypeMap.find(name);
      if (i == damageTypeMap.end()) return DamageTypeIDs::None;
      return (*i).second;
    }
  }
}
