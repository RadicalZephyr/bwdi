#pragma once

/**
 *  In lobby, the slot states you can choose from
 */ 

namespace BW
{
  namespace SlotStateIDs
  {
    enum Enum : u8
    {
      Computer = 0,
      Open = 1,
      Closed = 2,
      RescuePassive = 3,
      EitherPreferComputer = 5,
      EitherPreferHuman = 6,
      Neutral = 7,
      Closed2 = 8,
      PlayerLeft = 10,
      ComputerLeft = 11
    };
  }
  typedef SlotStateIDs::Enum SlotStateID;
}
