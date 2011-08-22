#include "TechTypes.h"

#include <BWDI/TechType.h>
#include <BWDI/TechTypeID.h>
#include <BWDI/RaceID.h>
#include <BWDI/UnitTypeID.h>
#include <BWDI/WeaponTypeID.h>

namespace BWDI
{
  namespace TechTypes
  {

    TechTypeInternal techTypeData[TechTypeIDs::count];
    std::map<std::string, TechTypeID> techTypeMap;
    std::set< TechTypeID > techTypeSet;

    void fillTechType(TechTypeID id, const char* name, int mineralPrice, int gasPrice, int energyUsed, int/*UnitTypeID*/ whatResearches, RaceID race, int/*WeaponTypeID*/ weapon, int/*UnitTypeID*/ whatUses1, int /*UnitTypeID*/ whatUses2=NULL, int /*UnitTypeID*/ whatUses3=NULL, int /*UnitType*/ whatUses4=NULL)
    {
      TechTypeInternal &target = techTypeData[id];
      target.name.set(name);
      target.mineralPrice=mineralPrice;
      target.gasPrice=gasPrice;
      target.energyUsed=energyUsed;
      target.whatResearches=(UnitTypeID)whatResearches;
      target.race=(RaceID)race;
      target.weapon=(WeaponTypeID)weapon;
      if (whatUses1!=NULL && whatUses1 != UnitTypeIDs::None)
      {
        target.whatUses.insert((UnitTypeID)whatUses1);
      }
      if (whatUses2!=NULL && whatUses2!= UnitTypeIDs::None)
      {
        target.whatUses.insert((UnitTypeID)whatUses2);
      }
      if (whatUses3!=NULL && whatUses3!= UnitTypeIDs::None)
      {
        target.whatUses.insert((UnitTypeID)whatUses3);
      }
      if (whatUses4!=NULL && whatUses4!= UnitTypeIDs::None)
      {
        target.whatUses.insert((UnitTypeID)whatUses4);
      }
      target.valid = true;
    }

    void init()
    {
      fillTechType(TechTypeIDs::Stim_Packs, "Stim Packs",100,100,0,UnitTypeIDs::Terran_Academy,RaceIDs::Terran,WeaponTypeIDs::None,UnitTypeIDs::Terran_Marine,UnitTypeIDs::Terran_Firebat);
      fillTechType(TechTypeIDs::Lockdown, "Lockdown",200,200,100,UnitTypeIDs::Terran_Covert_Ops,RaceIDs::Terran,WeaponTypeIDs::Lockdown,UnitTypeIDs::Terran_Ghost);
      fillTechType(TechTypeIDs::EMP_Shockwave, "EMP Shockwave",200,200,100,UnitTypeIDs::Terran_Science_Facility,RaceIDs::Terran,WeaponTypeIDs::EMP_Shockwave,UnitTypeIDs::Terran_Science_Vessel);
      fillTechType(TechTypeIDs::Spider_Mines, "Spider Mines",100,100,0,UnitTypeIDs::Terran_Machine_Shop,RaceIDs::Terran,WeaponTypeIDs::Spider_Mines,UnitTypeIDs::Terran_Vulture);
      fillTechType(TechTypeIDs::Scanner_Sweep, "Scanner Sweep",0,0,50,UnitTypeIDs::None,RaceIDs::Terran,WeaponTypeIDs::None,UnitTypeIDs::Terran_Comsat_Station);
      fillTechType(TechTypeIDs::Tank_Siege_Mode, "Tank Siege Mode",150,150,0,UnitTypeIDs::Terran_Machine_Shop,RaceIDs::Terran,WeaponTypeIDs::None,UnitTypeIDs::Terran_Siege_Tank_Tank_Mode,UnitTypeIDs::Terran_Siege_Tank_Siege_Mode);
      fillTechType(TechTypeIDs::Defensive_Matrix, "Defensive Matrix",0,0,100,UnitTypeIDs::None,RaceIDs::Terran,WeaponTypeIDs::None,UnitTypeIDs::Terran_Science_Vessel);
      fillTechType(TechTypeIDs::Irradiate, "Irradiate",200,200,75,UnitTypeIDs::Terran_Science_Facility,RaceIDs::Terran,WeaponTypeIDs::Irradiate,UnitTypeIDs::Terran_Science_Vessel);
      fillTechType(TechTypeIDs::Yamato_Gun, "Yamato Gun",100,100,150,UnitTypeIDs::Terran_Physics_Lab,RaceIDs::Terran,WeaponTypeIDs::Yamato_Gun,UnitTypeIDs::Terran_Battlecruiser);
      fillTechType(TechTypeIDs::Cloaking_Field, "Cloaking Field",150,150,25,UnitTypeIDs::Terran_Control_Tower,RaceIDs::Terran,WeaponTypeIDs::None,UnitTypeIDs::Terran_Wraith);
      fillTechType(TechTypeIDs::Personnel_Cloaking, "Personnel Cloaking",100,100,25,UnitTypeIDs::Terran_Covert_Ops,RaceIDs::Terran,WeaponTypeIDs::None,UnitTypeIDs::Terran_Ghost);
      fillTechType(TechTypeIDs::Burrowing, "Burrowing",100,100,0,UnitTypeIDs::Zerg_Hatchery,RaceIDs::Zerg,WeaponTypeIDs::None,UnitTypeIDs::Zerg_Drone,UnitTypeIDs::Zerg_Zergling,UnitTypeIDs::Zerg_Hydralisk,UnitTypeIDs::Zerg_Defiler);
      fillTechType(TechTypeIDs::Infestation, "Infestation",0,0,0,UnitTypeIDs::None,RaceIDs::Zerg,WeaponTypeIDs::None,UnitTypeIDs::Zerg_Queen);
      fillTechType(TechTypeIDs::Spawn_Broodlings, "Spawn Broodlings",100,100,150,UnitTypeIDs::Zerg_Queens_Nest,RaceIDs::Zerg,WeaponTypeIDs::Spawn_Broodlings,UnitTypeIDs::Zerg_Queen);
      fillTechType(TechTypeIDs::Dark_Swarm, "Dark Swarm",0,0,100,UnitTypeIDs::None,RaceIDs::Zerg,WeaponTypeIDs::Dark_Swarm,UnitTypeIDs::Zerg_Defiler);
      fillTechType(TechTypeIDs::Plague, "Plague",200,200,150,UnitTypeIDs::Zerg_Defiler_Mound,RaceIDs::Zerg,WeaponTypeIDs::Plague,UnitTypeIDs::Zerg_Defiler);
      fillTechType(TechTypeIDs::Consume, "Consume",100,100,0,UnitTypeIDs::Zerg_Defiler_Mound,RaceIDs::Zerg,WeaponTypeIDs::Consume,UnitTypeIDs::Zerg_Defiler);
      fillTechType(TechTypeIDs::Ensnare, "Ensnare",100,100,75,UnitTypeIDs::Zerg_Queens_Nest,RaceIDs::Zerg,WeaponTypeIDs::Ensnare,UnitTypeIDs::Zerg_Queen);
      fillTechType(TechTypeIDs::Parasite, "Parasite",0,0,75,UnitTypeIDs::None,RaceIDs::Zerg,WeaponTypeIDs::Parasite,UnitTypeIDs::Zerg_Queen);
      fillTechType(TechTypeIDs::Psionic_Storm, "Psionic Storm",200,200,75,UnitTypeIDs::Protoss_Templar_Archives,RaceIDs::Protoss,WeaponTypeIDs::Psionic_Storm,UnitTypeIDs::Protoss_High_Templar);
      fillTechType(TechTypeIDs::Hallucination, "Hallucination",150,150,100,UnitTypeIDs::Protoss_Templar_Archives,RaceIDs::Protoss,WeaponTypeIDs::None,UnitTypeIDs::Protoss_High_Templar);
      fillTechType(TechTypeIDs::Recall, "Recall",150,150,150,UnitTypeIDs::Protoss_Arbiter_Tribunal,RaceIDs::Protoss,WeaponTypeIDs::None,UnitTypeIDs::Protoss_Arbiter);
      fillTechType(TechTypeIDs::Stasis_Field, "Stasis Field",150,150,100,UnitTypeIDs::Protoss_Arbiter_Tribunal,RaceIDs::Protoss,WeaponTypeIDs::Stasis_Field,UnitTypeIDs::Protoss_Arbiter);
      fillTechType(TechTypeIDs::Archon_Warp, "Archon Warp",0,0,0,UnitTypeIDs::None,RaceIDs::Protoss,WeaponTypeIDs::None,UnitTypeIDs::Protoss_High_Templar);
      fillTechType(TechTypeIDs::Restoration, "Restoration",100,100,50,UnitTypeIDs::Terran_Academy,RaceIDs::Terran,WeaponTypeIDs::Restoration,UnitTypeIDs::Terran_Medic);
      fillTechType(TechTypeIDs::Disruption_Web, "Disruption Web",200,200,125,UnitTypeIDs::Protoss_Fleet_Beacon,RaceIDs::Protoss,WeaponTypeIDs::Disruption_Web,UnitTypeIDs::Protoss_Corsair);
      fillTechType(TechTypeIDs::Mind_Control, "Mind Control",200,200,150,UnitTypeIDs::Protoss_Templar_Archives,RaceIDs::Protoss,WeaponTypeIDs::Mind_Control,UnitTypeIDs::Protoss_Dark_Archon);
      fillTechType(TechTypeIDs::Dark_Archon_Meld, "Dark Archon Meld",0,0,0,UnitTypeIDs::None,RaceIDs::Protoss,WeaponTypeIDs::None,UnitTypeIDs::Protoss_Dark_Templar);
      fillTechType(TechTypeIDs::Feedback, "Feedback",0,0,50,UnitTypeIDs::None,RaceIDs::Protoss,WeaponTypeIDs::Feedback,UnitTypeIDs::Protoss_Dark_Archon);
      fillTechType(TechTypeIDs::Optical_Flare, "Optical Flare",100,100,75,UnitTypeIDs::Terran_Academy,RaceIDs::Terran,WeaponTypeIDs::Optical_Flare,UnitTypeIDs::Terran_Medic);
      fillTechType(TechTypeIDs::Maelstrom, "Maelstrom",100,100,100,UnitTypeIDs::Protoss_Templar_Archives,RaceIDs::Protoss,WeaponTypeIDs::Maelstrom,UnitTypeIDs::Protoss_Dark_Archon);
      fillTechType(TechTypeIDs::Lurker_Aspect, "Lurker Aspect",200,200,0,UnitTypeIDs::Zerg_Hydralisk_Den,RaceIDs::Zerg,WeaponTypeIDs::None,UnitTypeIDs::Zerg_Lurker);
      fillTechType(TechTypeIDs::Healing, "Healing",0,0,1,UnitTypeIDs::None,RaceIDs::Terran,WeaponTypeIDs::None,UnitTypeIDs::Terran_Medic);
      fillTechType(TechTypeIDs::None, "None",0,0,0,UnitTypeIDs::None,RaceIDs::None,WeaponTypeIDs::None,UnitTypeIDs::None);
      fillTechType(TechTypeIDs::Nuclear_Strike, "Nuclear Strike",0,0,0,UnitTypeIDs::None,RaceIDs::Terran,WeaponTypeIDs::Nuclear_Strike,UnitTypeIDs::Terran_Ghost);
      techTypeSet.insert(TechTypeIDs::Stim_Packs);
      techTypeSet.insert(TechTypeIDs::Lockdown);
      techTypeSet.insert(TechTypeIDs::EMP_Shockwave);
      techTypeSet.insert(TechTypeIDs::Spider_Mines);
      techTypeSet.insert(TechTypeIDs::Scanner_Sweep);
      techTypeSet.insert(TechTypeIDs::Tank_Siege_Mode);
      techTypeSet.insert(TechTypeIDs::Defensive_Matrix);
      techTypeSet.insert(TechTypeIDs::Irradiate);
      techTypeSet.insert(TechTypeIDs::Yamato_Gun);
      techTypeSet.insert(TechTypeIDs::Cloaking_Field);
      techTypeSet.insert(TechTypeIDs::Personnel_Cloaking);
      techTypeSet.insert(TechTypeIDs::Burrowing);
      techTypeSet.insert(TechTypeIDs::Infestation);
      techTypeSet.insert(TechTypeIDs::Spawn_Broodlings);
      techTypeSet.insert(TechTypeIDs::Dark_Swarm);
      techTypeSet.insert(TechTypeIDs::Plague);
      techTypeSet.insert(TechTypeIDs::Consume);
      techTypeSet.insert(TechTypeIDs::Ensnare);
      techTypeSet.insert(TechTypeIDs::Parasite);
      techTypeSet.insert(TechTypeIDs::Psionic_Storm);
      techTypeSet.insert(TechTypeIDs::Hallucination);
      techTypeSet.insert(TechTypeIDs::Recall);
      techTypeSet.insert(TechTypeIDs::Stasis_Field);
      techTypeSet.insert(TechTypeIDs::Archon_Warp);
      techTypeSet.insert(TechTypeIDs::Restoration);
      techTypeSet.insert(TechTypeIDs::Disruption_Web);
      techTypeSet.insert(TechTypeIDs::Mind_Control);
      techTypeSet.insert(TechTypeIDs::Dark_Archon_Meld);
      techTypeSet.insert(TechTypeIDs::Feedback);
      techTypeSet.insert(TechTypeIDs::Optical_Flare);
      techTypeSet.insert(TechTypeIDs::Maelstrom);
      techTypeSet.insert(TechTypeIDs::Lurker_Aspect);
      techTypeSet.insert(TechTypeIDs::Healing);
      techTypeSet.insert(TechTypeIDs::None);
      techTypeSet.insert(TechTypeIDs::Nuclear_Strike);

      for(std::set<TechTypeID>::iterator i = techTypeSet.begin(); i != techTypeSet.end(); i++)
      {
        techTypeMap.insert(std::make_pair(std::string(techTypeData[*i].name), *i));
      }
    }
  }
  namespace TechTypes
  {
    TechTypeID getIDByName(const std::string& name)
    {
      std::map<std::string, TechTypeID>::iterator i = techTypeMap.find(name);
      if (i == techTypeMap.end()) return TechTypeIDs::None;
      return (*i).second;
    }
    std::set<TechTypeID>& allTechTypes()
    {
      return techTypeSet;
    }
  }
}

