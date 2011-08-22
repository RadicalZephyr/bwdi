#pragma once
/**
 *  the race data table
 */

#include <BWDI\Race.h>
#include <BWDI\RaceID.h>

#include <string>
#include <map>
#include <set>

namespace BWDI
{
  namespace Races
  {
    extern Race raceData[RaceIDs::count];
    extern std::map<std::string, RaceID> raceMap;
    extern std::set< RaceID > raceSet;

    extern RaceID &getIDByName(std::string& name);
    extern void init();
  }
}
