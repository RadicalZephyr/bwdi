#pragma once
#include "Race.h"
#include "RaceID.h"
#include "TechTypeID.h"
#include "UpgradeTypeID.h"
#include "UnitSizeTypeID.h"
#include "WeaponTypeID.h"

#include <Util\StaticString.h>

namespace BWDI
{
  struct UnitType
  {
    struct BuildRequisite
    {
      UnitTypeID unitType;
      int count;
    };

    int id;
    Util::StaticString<32> name;
    Util::StaticString<32> subLabel;
    RaceID race;

    BuildRequisite whatBuilds;
    TechTypeID requiredTech;
    UpgradeTypeID armorUpgrade;

    int maxHitPoints;
    int maxShields;
    int maxEnergy;
    int armor;

    int mineralPrice;
    int gasPrice;
    int buildTime;

    int supplyRequired;
    int supplyProvided;
    int spaceRequired;
    int spaceProvided;
    int buildScore;
    int destroyScore;

    UnitSizeTypeID unitSizeType;
    int tileWidth;
    int tileHeight;
    int dimensionLeft;
    int dimensionUp;
    int dimensionRight;
    int dimensionDown;

    int seekRange;
    int sightRange;
    WeaponTypeID groundWeapon;
    int maxGroundHits;
    WeaponTypeID airWeapon;
    int maxAirHits;

    double topSpeed;
    int acceleration;
    int haltDistance;
    int turnRadius;

    bool canProduce;
    bool canAttack;
    bool canMove;
    bool isFlyer;
    bool regeneratesHP;
    bool isSpellcaster;
    bool hasPermanentCloak;
    bool isInvincible;
    bool isOrganic;
    bool isMechanical;
    bool isRobotic;
    bool isDetector;
    bool isResourceContainer;
    bool isResourceDepot;
    bool isWorker;
    bool requiresPsi;
    bool requiresCreep;
    bool isTwoUnitsInOneEgg;
    bool isBurrowable;
    bool isCloakable;
    bool isBuilding;
    bool isAddon;
    bool isFlyingBuilding;
    bool isNeutral;
    bool isRefinery;

    bool valid;
  };
}
