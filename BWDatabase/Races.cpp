#include "Races.h"

#include <BWDI\UnitTypeID.h>

namespace BWDI
{
  namespace Races
  {
    void fillRace(Race &race, const char* name, UnitTypeID worker, UnitTypeID center, UnitTypeID refinery, UnitTypeID transport, UnitTypeID supplyProvider)
    {
      race.name.set(name);
      race.worker = worker;
      race.center = center;
      race.refinery = refinery;
      race.transport = transport;
      race.supplyProvider = supplyProvider;
    }

    Race raceData[RaceIDs::count];
    std::map<std::string, RaceID> raceMap;
    std::set< RaceID > raceSet;

    void init()
    {
      fillRace(raceData[RaceIDs::Zerg], "Zerg", UnitTypeIDs::Zerg_Drone, UnitTypeIDs::Zerg_Hatchery, UnitTypeIDs::Zerg_Extractor, UnitTypeIDs::Zerg_Overlord, UnitTypeIDs::Zerg_Overlord);
      fillRace(raceData[RaceIDs::Terran], "Terran", UnitTypeIDs::Terran_SCV, UnitTypeIDs::Terran_Command_Center, UnitTypeIDs::Terran_Refinery, UnitTypeIDs::Terran_Dropship, UnitTypeIDs::Terran_Supply_Depot);
      fillRace(raceData[RaceIDs::Protoss], "Protoss", UnitTypeIDs::Protoss_Probe, UnitTypeIDs::Protoss_Nexus, UnitTypeIDs::Protoss_Assimilator, UnitTypeIDs::Protoss_Shuttle, UnitTypeIDs::Protoss_Pylon);

      raceSet.clear();
      raceSet.insert(RaceIDs::Zerg);
      raceSet.insert(RaceIDs::Terran);
      raceSet.insert(RaceIDs::Protoss);

      raceMap.clear();
      for(std::set<RaceID>::iterator i = raceSet.begin(); i != raceSet.end(); i++)
      {
        raceMap.insert(std::make_pair(std::string(raceData[*i].name), *i));
      }
    }
  }
}
