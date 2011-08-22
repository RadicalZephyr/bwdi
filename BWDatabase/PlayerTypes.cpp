#include "PlayerTypes.h"

namespace BWDI
{
  namespace PlayerTypes
  {
    PlayerType playerTypeData[PlayerTypeIDs::count];
    std::map<std::string, PlayerTypeID> playerTypeMap;
    std::set< PlayerTypeID > playerTypeSet;

    void fillPlayerType(PlayerTypeID id, const char* name)
    {
      PlayerType &target = playerTypeData[id];
      target.name.set(name);
    }

    void init()
    {
      fillPlayerType(PlayerTypeIDs::NotUsed, "NotUsed");
      fillPlayerType(PlayerTypeIDs::Computer, "Computer");
      fillPlayerType(PlayerTypeIDs::Human, "Human");
      fillPlayerType(PlayerTypeIDs::Rescuable, "Rescuable");
      fillPlayerType(PlayerTypeIDs::ComputerSlot, "ComputerSlot");
      fillPlayerType(PlayerTypeIDs::OpenSlot, "OpenSlot");
      fillPlayerType(PlayerTypeIDs::Neutral, "Neutral");
      fillPlayerType(PlayerTypeIDs::ClosedSlot, "ClosedSlot");
      fillPlayerType(PlayerTypeIDs::HumanDefeated, "HumanDefeated");
      fillPlayerType(PlayerTypeIDs::ComputerDefeated, "ComputerDefeated");
      fillPlayerType(PlayerTypeIDs::None, "None");
      playerTypeSet.insert(PlayerTypeIDs::NotUsed);
      playerTypeSet.insert(PlayerTypeIDs::Computer);
      playerTypeSet.insert(PlayerTypeIDs::Human);
      playerTypeSet.insert(PlayerTypeIDs::Rescuable);
      playerTypeSet.insert(PlayerTypeIDs::ComputerSlot);
      playerTypeSet.insert(PlayerTypeIDs::OpenSlot);
      playerTypeSet.insert(PlayerTypeIDs::Neutral);
      playerTypeSet.insert(PlayerTypeIDs::ClosedSlot);
      playerTypeSet.insert(PlayerTypeIDs::HumanDefeated);
      playerTypeSet.insert(PlayerTypeIDs::ComputerDefeated);
      playerTypeSet.insert(PlayerTypeIDs::None);
      for(std::set<PlayerTypeID>::iterator i = playerTypeSet.begin(); i != playerTypeSet.end(); i++)
      {
        playerTypeMap.insert(std::make_pair(std::string(playerTypeData[*i].name), *i));
      }
    }
    PlayerTypeID getIDByName(const std::string& name)
    {
      std::map<std::string, PlayerTypeID>::iterator i = playerTypeMap.find(name);
      if (i == playerTypeMap.end()) return PlayerTypeIDs::None;
      return (*i).second;
    }
  }
}
