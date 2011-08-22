#pragma once
/**
 *  the race data table
 */

#include <BWDI\OrderTypeID.h>

#include <string>
#include <map>
#include <set>

#include <Util\StaticString.h>

namespace BWDI
{
  struct OrderType
  {
    Util::StaticString<32> name;
  };
  namespace OrderTypes
  {
    extern OrderType actionTypeData[OrderTypeIDs::count];

    extern void init();
    extern OrderTypeID &getIDByName(std::string& name);
  }
}
