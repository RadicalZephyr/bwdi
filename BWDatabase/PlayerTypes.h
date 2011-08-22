#include <string>
#include <map>
#include <set>

#include <BWDI/PlayerType.h>
#include <BWDI/PlayerTypeID.h>

#pragma once

#include <string>
#include <map>
#include <set>

#include <BWDI/PlayerType.h>

namespace BWDI
{
  namespace PlayerTypes
  {
    extern PlayerType playerTypeData[PlayerTypeIDs::count];
    extern std::map<std::string, PlayerTypeID> playerTypeMap;
    extern std::set< PlayerTypeID > playerTypeSet;

    void init();
    PlayerTypeID getIDByName(const std::string& name);
  }
}
