#pragma once
namespace BW
{
  /** Game Types. */
  namespace GameTypeIDs
  {
  enum Enum
    {
      Melee      = 2,
      FFA        = 3,
      One_On_One = 4,
      CTF        = 5,
      Greed      = 6,
      Slaughter  = 7,
      SD         = 8,
      Ladder     = 9,
      UMS        = 10,
      Team_Melee = 11,
      Team_FFA   = 12,
      Team_CTF   = 13,
      TvB        = 15
    };
  }
  typedef GameTypeIDs::Enum GameTypeID;
};
