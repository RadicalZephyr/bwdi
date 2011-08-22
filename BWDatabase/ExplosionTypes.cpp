#include "ExplosionTypes.h"

#include <string>
#include <map>
#include <set>

namespace BWDI
{
  namespace ExplosionTypes
  {
    ExplosionTypeInternal explosionTypeData[ExplosionTypeIDs::count];
    std::map<std::string, ExplosionTypeID> explosionTypeMap;
    std::set< ExplosionTypeID > explosionTypeSet;

    void fillExplosionType(ExplosionTypeID id, const char* name)
    {
      ExplosionTypeInternal &target = explosionTypeData[id];
      target.name.set(name);
    }

    void init()
    {
      fillExplosionType(ExplosionTypeIDs::None, "None");
      fillExplosionType(ExplosionTypeIDs::Normal, "Normal");
      fillExplosionType(ExplosionTypeIDs::Radial_Splash, "Radial Splash");
      fillExplosionType(ExplosionTypeIDs::Enemy_Splash, "Enemy Splash");
      fillExplosionType(ExplosionTypeIDs::Lockdown, "Lockdown");
      fillExplosionType(ExplosionTypeIDs::Nuclear_Missile, "Nuclear Missile");
      fillExplosionType(ExplosionTypeIDs::Parasite, "Parasite");
      fillExplosionType(ExplosionTypeIDs::Broodlings, "Broodlings");
      fillExplosionType(ExplosionTypeIDs::EMP_Shockwave, "EMP Shockwave");
      fillExplosionType(ExplosionTypeIDs::Irradiate, "Irradiate");
      fillExplosionType(ExplosionTypeIDs::Ensnare, "Ensnare");
      fillExplosionType(ExplosionTypeIDs::Plague, "Plague");
      fillExplosionType(ExplosionTypeIDs::Stasis_Field, "Stasis Field");
      fillExplosionType(ExplosionTypeIDs::Dark_Swarm, "Dark Swarm");
      fillExplosionType(ExplosionTypeIDs::Consume, "Consume");
      fillExplosionType(ExplosionTypeIDs::Yamato_Gun, "Yamato Gun");
      fillExplosionType(ExplosionTypeIDs::Restoration, "Restoration");
      fillExplosionType(ExplosionTypeIDs::Disruption_Web, "Disruption Web");
      fillExplosionType(ExplosionTypeIDs::Corrosive_Acid, "Corrosive Acid");
      fillExplosionType(ExplosionTypeIDs::Mind_Control, "Mind Control");
      fillExplosionType(ExplosionTypeIDs::Feedback, "Feedback");
      fillExplosionType(ExplosionTypeIDs::Optical_Flare, "Optical Flare");
      fillExplosionType(ExplosionTypeIDs::Maelstrom, "Maelstrom");
      fillExplosionType(ExplosionTypeIDs::Air_Splash, "Air Splash");

      explosionTypeSet.insert(ExplosionTypeIDs::None);
      explosionTypeSet.insert(ExplosionTypeIDs::Normal);
      explosionTypeSet.insert(ExplosionTypeIDs::Radial_Splash);
      explosionTypeSet.insert(ExplosionTypeIDs::Enemy_Splash);
      explosionTypeSet.insert(ExplosionTypeIDs::Lockdown);
      explosionTypeSet.insert(ExplosionTypeIDs::Nuclear_Missile);
      explosionTypeSet.insert(ExplosionTypeIDs::Parasite);
      explosionTypeSet.insert(ExplosionTypeIDs::Broodlings);
      explosionTypeSet.insert(ExplosionTypeIDs::EMP_Shockwave);
      explosionTypeSet.insert(ExplosionTypeIDs::Irradiate);
      explosionTypeSet.insert(ExplosionTypeIDs::Ensnare);
      explosionTypeSet.insert(ExplosionTypeIDs::Plague);
      explosionTypeSet.insert(ExplosionTypeIDs::Stasis_Field);
      explosionTypeSet.insert(ExplosionTypeIDs::Dark_Swarm);
      explosionTypeSet.insert(ExplosionTypeIDs::Consume);
      explosionTypeSet.insert(ExplosionTypeIDs::Yamato_Gun);
      explosionTypeSet.insert(ExplosionTypeIDs::Restoration);
      explosionTypeSet.insert(ExplosionTypeIDs::Disruption_Web);
      explosionTypeSet.insert(ExplosionTypeIDs::Corrosive_Acid);
      explosionTypeSet.insert(ExplosionTypeIDs::Mind_Control);
      explosionTypeSet.insert(ExplosionTypeIDs::Feedback);
      explosionTypeSet.insert(ExplosionTypeIDs::Optical_Flare);
      explosionTypeSet.insert(ExplosionTypeIDs::Maelstrom);
      explosionTypeSet.insert(ExplosionTypeIDs::Air_Splash);

      for(std::set<ExplosionTypeID>::iterator i = explosionTypeSet.begin(); i != explosionTypeSet.end(); i++)
      {
        explosionTypeMap.insert(std::make_pair(std::string(explosionTypeData[*i].name), *i));
      }
    }

    ExplosionTypeID getIDByName(const std::string& name)
    {
      std::map<std::string, ExplosionTypeID>::iterator i = explosionTypeMap.find(name);
      if (i == explosionTypeMap.end()) return ExplosionTypeIDs::None;
      return (*i).second;
    }
  }
}
