#pragma once

#include "WeaponTypeID.h"
#include "UnitTypeID.h"
#include "TechTypeID.h"
#include "UpgradeTypeID.h"
#include "DamageTypeID.h"
#include "ExplosionTypeID.h"

#include <Util\StaticString.h>

namespace BWDI
{
  struct WeaponType
  {
    int id;
    bool valid;
    Util::StaticString<32> name;
    TechTypeID techType;
    UnitTypeID whatUses;
    int damageAmount;
    int damageBonus;
    int damageCooldown;
    int damageFactor;
    UpgradeTypeID upgradeType;
    DamageTypeID damageType;
    ExplosionTypeID explosionType;
    int minRange;
    int maxRange;
    int innerSplashRadius;
    int medianSplashRadius;
    int outerSplashRadius;
    bool targetsAir;
    bool targetsGround;
    bool targetsMechanical;
    bool targetsOrganic;
    bool targetsNonBuilding;
    bool targetsNonRobotic;
    bool targetsTerrain;
    bool targetsOrgOrMech;
    bool targetsOwn;
  };
}
