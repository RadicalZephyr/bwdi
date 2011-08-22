#include "UpgradeTypes.h"

#include <BWDI\UpgradeType.h>
#include <BWDI\UpgradeTypeID.h>

namespace BWDI
{
  UpgradeTypeInternal upgradeTypeData[UpgradeTypeIDs::count];
  std::map<std::string, UpgradeTypeID> upgradeTypeMap;
  std::set< UpgradeTypeID > upgradeTypeSet;

  void fillUpgradeType(UpgradeTypeID id, const char* name, int mineralPriceBase, int mineralPriceFactor, int gasPriceBase, int gasPriceFactor, int upgradeTimeBase, int upgradeTimeFactor, BWDI::UnitTypeID whatUpgrades, RaceID race, BWDI::UnitTypeID whatUses, int maxRepeats)
  {
    UpgradeTypeInternal &target = upgradeTypeData[id];
    target.name.set(name);
    target.mineralPriceBase = mineralPriceBase;
    target.mineralPriceFactor = mineralPriceFactor;
    target.gasPriceBase = gasPriceBase;
    target.gasPriceFactor = gasPriceFactor;
    target.upgradeTimeBase = upgradeTimeBase;
    target.upgradeTimeFactor = upgradeTimeFactor;
    target.whatUpgrades = whatUpgrades;
    target.race = race;
    if (whatUses!=NULL && whatUses!= UnitTypeIDs::None)
    {
      target.whatUses.insert(whatUses);
    }
    target.maxRepeats = maxRepeats;
    target.valid = true;
  }
  namespace UpgradeTypes
  {
    void init()
    {
      fillUpgradeType(UpgradeTypeIDs::Terran_Infantry_Armor, "Terran Infantry Armor", 100, 75, 100, 75, 4000, 480, UnitTypeIDs::Terran_Engineering_Bay, RaceIDs::Terran, UnitTypeIDs::None, 3);
      fillUpgradeType(UpgradeTypeIDs::Terran_Vehicle_Plating, "Terran Vehicle Plating", 100, 75, 100, 75, 4000, 480, UnitTypeIDs::Terran_Armory, RaceIDs::Terran, UnitTypeIDs::None, 3);
      fillUpgradeType(UpgradeTypeIDs::Terran_Ship_Plating, "Terran Ship Plating", 150, 75, 150, 75, 4000, 480, UnitTypeIDs::Terran_Armory, RaceIDs::Terran, UnitTypeIDs::None, 3);
      fillUpgradeType(UpgradeTypeIDs::Zerg_Carapace, "Zerg Carapace", 150, 75, 150, 75, 4000, 480, UnitTypeIDs::Zerg_Evolution_Chamber, RaceIDs::Zerg, UnitTypeIDs::None, 3);
      fillUpgradeType(UpgradeTypeIDs::Zerg_Flyer_Carapace, "Zerg Flyer Carapace", 150, 75, 150, 75, 4000, 480, UnitTypeIDs::Zerg_Spire, RaceIDs::Zerg, UnitTypeIDs::None, 3);
      fillUpgradeType(UpgradeTypeIDs::Protoss_Armor, "Protoss Armor", 100, 75, 100, 75, 4000, 480, UnitTypeIDs::Protoss_Forge, RaceIDs::Protoss, UnitTypeIDs::None, 3);
      fillUpgradeType(UpgradeTypeIDs::Protoss_Plating, "Protoss Plating", 150, 75, 150, 75, 4000, 480, UnitTypeIDs::Protoss_Cybernetics_Core, RaceIDs::Protoss, UnitTypeIDs::None, 3);
      fillUpgradeType(UpgradeTypeIDs::Terran_Infantry_Weapons, "Terran Infantry Weapons", 100, 75, 100, 75, 4000, 480, UnitTypeIDs::Terran_Engineering_Bay, RaceIDs::Terran, UnitTypeIDs::None, 3);
      fillUpgradeType(UpgradeTypeIDs::Terran_Vehicle_Weapons, "Terran Vehicle Weapons", 100, 75, 100, 75, 4000, 480, UnitTypeIDs::Terran_Armory, RaceIDs::Terran, UnitTypeIDs::None, 3);
      fillUpgradeType(UpgradeTypeIDs::Terran_Ship_Weapons, "Terran Ship Weapons", 100, 50, 100, 50, 4000, 480, UnitTypeIDs::Terran_Armory, RaceIDs::Terran, UnitTypeIDs::None, 3);
      fillUpgradeType(UpgradeTypeIDs::Zerg_Melee_Attacks, "Zerg Melee Attacks", 100, 50, 100, 50, 4000, 480, UnitTypeIDs::Zerg_Evolution_Chamber, RaceIDs::Zerg, UnitTypeIDs::None, 3);
      fillUpgradeType(UpgradeTypeIDs::Zerg_Missile_Attacks, "Zerg Missile Attacks", 100, 50, 100, 50, 4000, 480, UnitTypeIDs::Zerg_Evolution_Chamber, RaceIDs::Zerg, UnitTypeIDs::None, 3);
      fillUpgradeType(UpgradeTypeIDs::Zerg_Flyer_Attacks, "Zerg Flyer Attacks", 100, 75, 100, 75, 4000, 480, UnitTypeIDs::Zerg_Spire, RaceIDs::Zerg, UnitTypeIDs::None, 3);
      fillUpgradeType(UpgradeTypeIDs::Protoss_Ground_Weapons, "Protoss Ground Weapons", 100, 50, 100, 50, 4000, 480, UnitTypeIDs::Protoss_Forge, RaceIDs::Protoss, UnitTypeIDs::None, 3);
      fillUpgradeType(UpgradeTypeIDs::Protoss_Air_Weapons, "Protoss Air Weapons", 100, 75, 100, 75, 4000, 480, UnitTypeIDs::Protoss_Cybernetics_Core, RaceIDs::Protoss, UnitTypeIDs::None, 3);
      fillUpgradeType(UpgradeTypeIDs::Protoss_Plasma_Shields, "Protoss Plasma Shields", 200, 100, 200, 100, 4000, 480, UnitTypeIDs::Protoss_Forge, RaceIDs::Protoss, UnitTypeIDs::None, 3);
      fillUpgradeType(UpgradeTypeIDs::U_238_Shells, "U-238 Shells", 150, 0, 150, 0, 1500, 0, UnitTypeIDs::Terran_Academy, RaceIDs::Terran, UnitTypeIDs::Terran_Marine, 1);
      fillUpgradeType(UpgradeTypeIDs::Ion_Thrusters, "Ion Thrusters", 100, 0, 100, 0, 1500, 0, UnitTypeIDs::Terran_Machine_Shop, RaceIDs::Terran, UnitTypeIDs::Terran_Vulture, 1);
      fillUpgradeType(UpgradeTypeIDs::Titan_Reactor, "Titan Reactor", 150, 0, 150, 0, 2500, 0, UnitTypeIDs::Terran_Science_Facility, RaceIDs::Terran, UnitTypeIDs::Terran_Science_Vessel, 1);
      fillUpgradeType(UpgradeTypeIDs::Ocular_Implants, "Ocular Implants", 100, 0, 100, 0, 2500, 0, UnitTypeIDs::Terran_Covert_Ops, RaceIDs::Terran, UnitTypeIDs::Terran_Ghost, 1);
      fillUpgradeType(UpgradeTypeIDs::Moebius_Reactor, "Moebius Reactor", 150, 0, 150, 0, 2500, 0, UnitTypeIDs::Terran_Covert_Ops, RaceIDs::Terran, UnitTypeIDs::Terran_Ghost, 1);
      fillUpgradeType(UpgradeTypeIDs::Apollo_Reactor, "Apollo Reactor", 200, 0, 200, 0, 2500, 0, UnitTypeIDs::Terran_Control_Tower, RaceIDs::Terran, UnitTypeIDs::Terran_Wraith, 1);
      fillUpgradeType(UpgradeTypeIDs::Colossus_Reactor, "Colossus Reactor", 150, 0, 150, 0, 2500, 0, UnitTypeIDs::Terran_Physics_Lab, RaceIDs::Terran, UnitTypeIDs::Terran_Battlecruiser, 1);
      fillUpgradeType(UpgradeTypeIDs::Ventral_Sacs, "Ventral Sacs", 200, 0, 200, 0, 2400, 0, UnitTypeIDs::Zerg_Lair, RaceIDs::Zerg, UnitTypeIDs::Zerg_Overlord, 1);
      fillUpgradeType(UpgradeTypeIDs::Antennae, "Antennae", 150, 0, 150, 0, 2000, 0, UnitTypeIDs::Zerg_Lair, RaceIDs::Zerg, UnitTypeIDs::Zerg_Overlord, 1);
      fillUpgradeType(UpgradeTypeIDs::Pneumatized_Carapace, "Pneumatized Carapace", 150, 0, 150, 0, 2000, 0, UnitTypeIDs::Zerg_Lair, RaceIDs::Zerg, UnitTypeIDs::Zerg_Overlord, 1);
      fillUpgradeType(UpgradeTypeIDs::Metabolic_Boost, "Metabolic Boost", 100, 0, 100, 0, 1500, 0, UnitTypeIDs::Zerg_Spawning_Pool, RaceIDs::Zerg, UnitTypeIDs::Zerg_Zergling, 1);
      fillUpgradeType(UpgradeTypeIDs::Adrenal_Glands, "Adrenal Glands", 200, 0, 200, 0, 1500, 0, UnitTypeIDs::Zerg_Spawning_Pool, RaceIDs::Zerg, UnitTypeIDs::Zerg_Zergling, 1);
      fillUpgradeType(UpgradeTypeIDs::Muscular_Augments, "Muscular Augments", 150, 0, 150, 0, 1500, 0, UnitTypeIDs::Zerg_Hydralisk_Den, RaceIDs::Zerg, UnitTypeIDs::Zerg_Hydralisk, 1);
      fillUpgradeType(UpgradeTypeIDs::Grooved_Spines, "Grooved Spines", 150, 0, 150, 0, 1500, 0, UnitTypeIDs::Zerg_Hydralisk_Den, RaceIDs::Zerg, UnitTypeIDs::Zerg_Hydralisk, 1);
      fillUpgradeType(UpgradeTypeIDs::Gamete_Meiosis, "Gamete Meiosis", 150, 0, 150, 0, 2500, 0, UnitTypeIDs::Zerg_Queens_Nest, RaceIDs::Zerg, UnitTypeIDs::Zerg_Queen, 1);
      fillUpgradeType(UpgradeTypeIDs::Metasynaptic_Node, "Metasynaptic Node", 150, 0, 150, 0, 2500, 0, UnitTypeIDs::Zerg_Defiler_Mound, RaceIDs::Zerg, UnitTypeIDs::Zerg_Defiler, 1);
      fillUpgradeType(UpgradeTypeIDs::Singularity_Charge, "Singularity Charge", 150, 0, 150, 0, 2500, 0, UnitTypeIDs::Protoss_Cybernetics_Core, RaceIDs::Protoss, UnitTypeIDs::Protoss_Dragoon, 1);
      fillUpgradeType(UpgradeTypeIDs::Leg_Enhancements, "Leg Enhancements", 150, 0, 150, 0, 2000, 0, UnitTypeIDs::Protoss_Citadel_of_Adun, RaceIDs::Protoss, UnitTypeIDs::Protoss_Zealot, 1);
      fillUpgradeType(UpgradeTypeIDs::Scarab_Damage, "Scarab Damage", 200, 0, 200, 0, 2500, 0, UnitTypeIDs::Protoss_Robotics_Support_Bay, RaceIDs::Protoss, UnitTypeIDs::Protoss_Scarab, 1);
      fillUpgradeType(UpgradeTypeIDs::Reaver_Capacity, "Reaver Capacity", 200, 0, 200, 0, 2500, 0, UnitTypeIDs::Protoss_Robotics_Support_Bay, RaceIDs::Protoss, UnitTypeIDs::Protoss_Reaver, 1);
      fillUpgradeType(UpgradeTypeIDs::Gravitic_Drive, "Gravitic Drive", 200, 0, 200, 0, 2500, 0, UnitTypeIDs::Protoss_Robotics_Support_Bay, RaceIDs::Protoss, UnitTypeIDs::Protoss_Shuttle, 1);
      fillUpgradeType(UpgradeTypeIDs::Sensor_Array, "Sensor Array", 150, 0, 150, 0, 2000, 0, UnitTypeIDs::Protoss_Observatory, RaceIDs::Protoss, UnitTypeIDs::Protoss_Observer, 1);
      fillUpgradeType(UpgradeTypeIDs::Gravitic_Boosters, "Gravitic Boosters", 150, 0, 150, 0, 2000, 0, UnitTypeIDs::Protoss_Observatory, RaceIDs::Protoss, UnitTypeIDs::Protoss_Observer, 1);
      fillUpgradeType(UpgradeTypeIDs::Khaydarin_Amulet, "Khaydarin Amulet", 150, 0, 150, 0, 2500, 0, UnitTypeIDs::Protoss_Templar_Archives, RaceIDs::Protoss, UnitTypeIDs::Protoss_High_Templar, 1);
      fillUpgradeType(UpgradeTypeIDs::Apial_Sensors, "Apial Sensors", 100, 0, 100, 0, 2500, 0, UnitTypeIDs::Protoss_Templar_Archives, RaceIDs::Protoss, UnitTypeIDs::Protoss_Scout, 1);
      fillUpgradeType(UpgradeTypeIDs::Gravitic_Thrusters, "Gravitic Thrusters", 200, 0, 200, 0, 2500, 0, UnitTypeIDs::Protoss_Fleet_Beacon, RaceIDs::Protoss, UnitTypeIDs::Protoss_Scout, 1);
      fillUpgradeType(UpgradeTypeIDs::Carrier_Capacity, "Carrier Capacity", 100, 0, 100, 0, 1500, 0, UnitTypeIDs::Protoss_Fleet_Beacon, RaceIDs::Protoss, UnitTypeIDs::Protoss_Carrier, 1);
      fillUpgradeType(UpgradeTypeIDs::Khaydarin_Core, "Khaydarin Core", 150, 0, 150, 0, 2500, 0, UnitTypeIDs::Protoss_Arbiter_Tribunal, RaceIDs::Protoss, UnitTypeIDs::Protoss_Arbiter, 1);
      fillUpgradeType(UpgradeTypeIDs::Argus_Jewel, "Argus Jewel", 100, 0, 100, 0, 2500, 0, UnitTypeIDs::Protoss_Fleet_Beacon, RaceIDs::Protoss, UnitTypeIDs::Protoss_Corsair, 1);
      fillUpgradeType(UpgradeTypeIDs::Argus_Talisman, "Argus Talisman", 150, 0, 150, 0, 2500, 0, UnitTypeIDs::Protoss_Templar_Archives, RaceIDs::Protoss, UnitTypeIDs::Protoss_Dark_Archon, 1);
      fillUpgradeType(UpgradeTypeIDs::Caduceus_Reactor, "Caduceus Reactor", 150, 0, 150, 0, 2500, 0, UnitTypeIDs::Terran_Academy, RaceIDs::Terran, UnitTypeIDs::Terran_Medic, 1);
      fillUpgradeType(UpgradeTypeIDs::Chitinous_Plating, "Chitinous Plating", 150, 0, 150, 0, 2000, 0, UnitTypeIDs::Zerg_Ultralisk_Cavern, RaceIDs::Zerg, UnitTypeIDs::Zerg_Ultralisk, 1);
      fillUpgradeType(UpgradeTypeIDs::Anabolic_Synthesis, "Anabolic Synthesis", 200, 0, 200, 0, 2000, 0, UnitTypeIDs::Zerg_Ultralisk_Cavern, RaceIDs::Zerg, UnitTypeIDs::Zerg_Ultralisk, 1);
      fillUpgradeType(UpgradeTypeIDs::Charon_Booster, "Charon Booster", 100, 0, 100, 0, 2000, 0, UnitTypeIDs::Terran_Machine_Shop, RaceIDs::Terran, UnitTypeIDs::Terran_Goliath, 1);
      fillUpgradeType(UpgradeTypeIDs::None, "None", 0, 0, 0, 0, 0, 0, UnitTypeIDs::None, RaceIDs::None, UnitTypeIDs::None, 0);

      upgradeTypeData[UpgradeTypeIDs::Terran_Infantry_Armor].whatUses.insert(UnitTypeIDs::Terran_Firebat);
      upgradeTypeData[UpgradeTypeIDs::Terran_Infantry_Armor].whatUses.insert(UnitTypeIDs::Terran_Ghost);
      upgradeTypeData[UpgradeTypeIDs::Terran_Infantry_Armor].whatUses.insert(UnitTypeIDs::Terran_Marine);
      upgradeTypeData[UpgradeTypeIDs::Terran_Infantry_Armor].whatUses.insert(UnitTypeIDs::Terran_Medic);
      upgradeTypeData[UpgradeTypeIDs::Terran_Infantry_Armor].whatUses.insert(UnitTypeIDs::Terran_SCV);
      upgradeTypeData[UpgradeTypeIDs::Terran_Vehicle_Plating].whatUses.insert(UnitTypeIDs::Terran_Goliath);
      upgradeTypeData[UpgradeTypeIDs::Terran_Vehicle_Plating].whatUses.insert(UnitTypeIDs::Terran_Siege_Tank_Siege_Mode);
      upgradeTypeData[UpgradeTypeIDs::Terran_Vehicle_Plating].whatUses.insert(UnitTypeIDs::Terran_Siege_Tank_Tank_Mode);
      upgradeTypeData[UpgradeTypeIDs::Terran_Vehicle_Plating].whatUses.insert(UnitTypeIDs::Terran_Vulture);
      upgradeTypeData[UpgradeTypeIDs::Terran_Ship_Plating].whatUses.insert(UnitTypeIDs::Terran_Battlecruiser);
      upgradeTypeData[UpgradeTypeIDs::Terran_Ship_Plating].whatUses.insert(UnitTypeIDs::Terran_Dropship);
      upgradeTypeData[UpgradeTypeIDs::Terran_Ship_Plating].whatUses.insert(UnitTypeIDs::Terran_Science_Vessel);
      upgradeTypeData[UpgradeTypeIDs::Terran_Ship_Plating].whatUses.insert(UnitTypeIDs::Terran_Valkyrie);
      upgradeTypeData[UpgradeTypeIDs::Terran_Ship_Plating].whatUses.insert(UnitTypeIDs::Terran_Wraith);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Carapace].whatUses.insert(UnitTypeIDs::Zerg_Broodling);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Carapace].whatUses.insert(UnitTypeIDs::Zerg_Defiler);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Carapace].whatUses.insert(UnitTypeIDs::Zerg_Drone);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Carapace].whatUses.insert(UnitTypeIDs::Zerg_Hydralisk);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Carapace].whatUses.insert(UnitTypeIDs::Zerg_Infested_Terran);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Carapace].whatUses.insert(UnitTypeIDs::Zerg_Larva);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Carapace].whatUses.insert(UnitTypeIDs::Zerg_Lurker);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Carapace].whatUses.insert(UnitTypeIDs::Zerg_Ultralisk);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Carapace].whatUses.insert(UnitTypeIDs::Zerg_Zergling);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Flyer_Carapace].whatUses.insert(UnitTypeIDs::Zerg_Devourer);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Flyer_Carapace].whatUses.insert(UnitTypeIDs::Zerg_Guardian);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Flyer_Carapace].whatUses.insert(UnitTypeIDs::Zerg_Mutalisk);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Flyer_Carapace].whatUses.insert(UnitTypeIDs::Zerg_Overlord);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Flyer_Carapace].whatUses.insert(UnitTypeIDs::Zerg_Queen);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Flyer_Carapace].whatUses.insert(UnitTypeIDs::Zerg_Scourge);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Armor].whatUses.insert(UnitTypeIDs::Protoss_Archon);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Armor].whatUses.insert(UnitTypeIDs::Protoss_Dark_Archon);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Armor].whatUses.insert(UnitTypeIDs::Protoss_Dark_Templar);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Armor].whatUses.insert(UnitTypeIDs::Protoss_Dragoon);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Armor].whatUses.insert(UnitTypeIDs::Protoss_High_Templar);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Armor].whatUses.insert(UnitTypeIDs::Protoss_Probe);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Armor].whatUses.insert(UnitTypeIDs::Protoss_Reaver);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Armor].whatUses.insert(UnitTypeIDs::Protoss_Zealot);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plating].whatUses.insert(UnitTypeIDs::Protoss_Arbiter);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plating].whatUses.insert(UnitTypeIDs::Protoss_Carrier);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plating].whatUses.insert(UnitTypeIDs::Protoss_Corsair);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plating].whatUses.insert(UnitTypeIDs::Protoss_Interceptor);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plating].whatUses.insert(UnitTypeIDs::Protoss_Observer);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plating].whatUses.insert(UnitTypeIDs::Protoss_Scout);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plating].whatUses.insert(UnitTypeIDs::Protoss_Shuttle);
      upgradeTypeData[UpgradeTypeIDs::Terran_Infantry_Weapons].whatUses.insert(UnitTypeIDs::Terran_Firebat);
      upgradeTypeData[UpgradeTypeIDs::Terran_Infantry_Weapons].whatUses.insert(UnitTypeIDs::Terran_Ghost);
      upgradeTypeData[UpgradeTypeIDs::Terran_Infantry_Weapons].whatUses.insert(UnitTypeIDs::Terran_Marine);
      upgradeTypeData[UpgradeTypeIDs::Terran_Vehicle_Weapons].whatUses.insert(UnitTypeIDs::Terran_Goliath);
      upgradeTypeData[UpgradeTypeIDs::Terran_Vehicle_Weapons].whatUses.insert(UnitTypeIDs::Terran_Siege_Tank_Siege_Mode);
      upgradeTypeData[UpgradeTypeIDs::Terran_Vehicle_Weapons].whatUses.insert(UnitTypeIDs::Terran_Siege_Tank_Tank_Mode);
      upgradeTypeData[UpgradeTypeIDs::Terran_Vehicle_Weapons].whatUses.insert(UnitTypeIDs::Terran_Vulture);
      upgradeTypeData[UpgradeTypeIDs::Terran_Ship_Weapons].whatUses.insert(UnitTypeIDs::Terran_Battlecruiser);
      upgradeTypeData[UpgradeTypeIDs::Terran_Ship_Weapons].whatUses.insert(UnitTypeIDs::Terran_Valkyrie);
      upgradeTypeData[UpgradeTypeIDs::Terran_Ship_Weapons].whatUses.insert(UnitTypeIDs::Terran_Wraith);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Melee_Attacks].whatUses.insert(UnitTypeIDs::Zerg_Broodling);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Melee_Attacks].whatUses.insert(UnitTypeIDs::Zerg_Ultralisk);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Melee_Attacks].whatUses.insert(UnitTypeIDs::Zerg_Zergling);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Missile_Attacks].whatUses.insert(UnitTypeIDs::Zerg_Hydralisk);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Missile_Attacks].whatUses.insert(UnitTypeIDs::Zerg_Lurker);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Flyer_Attacks].whatUses.insert(UnitTypeIDs::Zerg_Devourer);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Flyer_Attacks].whatUses.insert(UnitTypeIDs::Zerg_Guardian);
      upgradeTypeData[UpgradeTypeIDs::Zerg_Flyer_Attacks].whatUses.insert(UnitTypeIDs::Zerg_Mutalisk);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Ground_Weapons].whatUses.insert(UnitTypeIDs::Protoss_Dark_Templar);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Ground_Weapons].whatUses.insert(UnitTypeIDs::Protoss_Dragoon);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Ground_Weapons].whatUses.insert(UnitTypeIDs::Protoss_Zealot);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Air_Weapons].whatUses.insert(UnitTypeIDs::Protoss_Arbiter);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Air_Weapons].whatUses.insert(UnitTypeIDs::Protoss_Corsair);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Air_Weapons].whatUses.insert(UnitTypeIDs::Protoss_Interceptor);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Air_Weapons].whatUses.insert(UnitTypeIDs::Protoss_Scout);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Arbiter);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Arbiter_Tribunal);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Archon);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Assimilator);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Carrier);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Citadel_of_Adun);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Corsair);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Cybernetics_Core);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Dark_Archon);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Dark_Templar);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Dragoon);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Fleet_Beacon);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Forge);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Gateway);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_High_Templar);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Interceptor);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Nexus);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Observatory);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Observer);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Photon_Cannon);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Probe);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Pylon);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Reaver);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Robotics_Facility);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Robotics_Support_Bay);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Scarab);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Scout);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Shield_Battery);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Shuttle);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Stargate);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Templar_Archives);
      upgradeTypeData[UpgradeTypeIDs::Protoss_Plasma_Shields].whatUses.insert(UnitTypeIDs::Protoss_Zealot);

      upgradeTypeSet.insert(UpgradeTypeIDs::Terran_Infantry_Armor);
      upgradeTypeSet.insert(UpgradeTypeIDs::Terran_Vehicle_Plating);
      upgradeTypeSet.insert(UpgradeTypeIDs::Terran_Ship_Plating);
      upgradeTypeSet.insert(UpgradeTypeIDs::Zerg_Carapace);
      upgradeTypeSet.insert(UpgradeTypeIDs::Zerg_Flyer_Carapace);
      upgradeTypeSet.insert(UpgradeTypeIDs::Protoss_Armor);
      upgradeTypeSet.insert(UpgradeTypeIDs::Protoss_Plating);
      upgradeTypeSet.insert(UpgradeTypeIDs::Terran_Infantry_Weapons);
      upgradeTypeSet.insert(UpgradeTypeIDs::Terran_Vehicle_Weapons);
      upgradeTypeSet.insert(UpgradeTypeIDs::Terran_Ship_Weapons);
      upgradeTypeSet.insert(UpgradeTypeIDs::Zerg_Melee_Attacks);
      upgradeTypeSet.insert(UpgradeTypeIDs::Zerg_Missile_Attacks);
      upgradeTypeSet.insert(UpgradeTypeIDs::Zerg_Flyer_Attacks);
      upgradeTypeSet.insert(UpgradeTypeIDs::Protoss_Ground_Weapons);
      upgradeTypeSet.insert(UpgradeTypeIDs::Protoss_Air_Weapons);
      upgradeTypeSet.insert(UpgradeTypeIDs::Protoss_Plasma_Shields);
      upgradeTypeSet.insert(UpgradeTypeIDs::U_238_Shells);
      upgradeTypeSet.insert(UpgradeTypeIDs::Ion_Thrusters);
      upgradeTypeSet.insert(UpgradeTypeIDs::Titan_Reactor);
      upgradeTypeSet.insert(UpgradeTypeIDs::Ocular_Implants);
      upgradeTypeSet.insert(UpgradeTypeIDs::Moebius_Reactor);
      upgradeTypeSet.insert(UpgradeTypeIDs::Apollo_Reactor);
      upgradeTypeSet.insert(UpgradeTypeIDs::Colossus_Reactor);
      upgradeTypeSet.insert(UpgradeTypeIDs::Ventral_Sacs);
      upgradeTypeSet.insert(UpgradeTypeIDs::Antennae);
      upgradeTypeSet.insert(UpgradeTypeIDs::Pneumatized_Carapace);
      upgradeTypeSet.insert(UpgradeTypeIDs::Metabolic_Boost);
      upgradeTypeSet.insert(UpgradeTypeIDs::Adrenal_Glands);
      upgradeTypeSet.insert(UpgradeTypeIDs::Muscular_Augments);
      upgradeTypeSet.insert(UpgradeTypeIDs::Grooved_Spines);
      upgradeTypeSet.insert(UpgradeTypeIDs::Gamete_Meiosis);
      upgradeTypeSet.insert(UpgradeTypeIDs::Metasynaptic_Node);
      upgradeTypeSet.insert(UpgradeTypeIDs::Singularity_Charge);
      upgradeTypeSet.insert(UpgradeTypeIDs::Leg_Enhancements);
      upgradeTypeSet.insert(UpgradeTypeIDs::Scarab_Damage);
      upgradeTypeSet.insert(UpgradeTypeIDs::Reaver_Capacity);
      upgradeTypeSet.insert(UpgradeTypeIDs::Gravitic_Drive);
      upgradeTypeSet.insert(UpgradeTypeIDs::Sensor_Array);
      upgradeTypeSet.insert(UpgradeTypeIDs::Gravitic_Boosters);
      upgradeTypeSet.insert(UpgradeTypeIDs::Khaydarin_Amulet);
      upgradeTypeSet.insert(UpgradeTypeIDs::Apial_Sensors);
      upgradeTypeSet.insert(UpgradeTypeIDs::Gravitic_Thrusters);
      upgradeTypeSet.insert(UpgradeTypeIDs::Carrier_Capacity);
      upgradeTypeSet.insert(UpgradeTypeIDs::Khaydarin_Core);
      upgradeTypeSet.insert(UpgradeTypeIDs::Argus_Jewel);
      upgradeTypeSet.insert(UpgradeTypeIDs::Argus_Talisman);
      upgradeTypeSet.insert(UpgradeTypeIDs::Caduceus_Reactor);
      upgradeTypeSet.insert(UpgradeTypeIDs::Chitinous_Plating);
      upgradeTypeSet.insert(UpgradeTypeIDs::Anabolic_Synthesis);
      upgradeTypeSet.insert(UpgradeTypeIDs::Charon_Booster);
      upgradeTypeSet.insert(UpgradeTypeIDs::None);

      for(std::set<UpgradeTypeID>::iterator i = upgradeTypeSet.begin(); i != upgradeTypeSet.end(); i++)
      {
        upgradeTypeMap.insert(std::make_pair(upgradeTypeData[*i].name, *i));
      }
    }
  }
  namespace UpgradeTypes
  {
    UpgradeTypeID getIDByName(const std::string& name)
    {
      std::map<std::string, UpgradeTypeID>::iterator i = upgradeTypeMap.find(name);
      if (i == upgradeTypeMap.end()) return UpgradeTypeIDs::None;
      return (*i).second;
    }
  }
}
