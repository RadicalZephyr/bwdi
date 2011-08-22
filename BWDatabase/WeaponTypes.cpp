#include "WeaponTypes.h"

#include <BWDI\WeaponType.h>
#include <BWDI\WeaponTypeID.h>
#include <BWDI\UnitTypeID.h>
#include <BWDI\TechTypeID.h>
#include <BWDI\UpgradeTypeID.h>
#include <BWDI\DamageTypeID.h>
#include <BWDI\ExplosionTypeID.h>

namespace BWDI
{
  namespace WeaponTypes
  {
    WeaponTypeInternal weaponTypeData[WeaponTypeIDs::count];
    std::map<std::string, WeaponTypeID> weaponTypeMap;
    std::set< WeaponTypeID > weaponTypeSet;
    std::set< WeaponTypeID > specialWeaponTypeSet;
    std::set< WeaponTypeID > normalWeaponTypeSet;
    void fillWeaponType(WeaponTypeID id, const char* name, TechTypeID techType, int damageAmount, int damageBonus, int damageCooldown, int damageFactor, UpgradeTypeID upgradeType, DamageTypeID damageType, ExplosionTypeID explosionType, int minRange, int maxRange, int innerSplashRadius, int medianSplashRadius, int outerSplashRadius, bool targetsAir, bool targetsGround, bool targetsMechanical, bool targetsOrganic, bool targetsNonBuilding, bool targetsNonRobotic, bool targetsTerrain, bool targetsOrgOrMech, bool targetsOwn, UnitTypeID whatUses)
    {
      WeaponType &target = weaponTypeData[id];
      target.name.set(name);
      target.techType = techType;
      target.damageAmount = damageAmount;
      target.damageBonus = damageBonus;
      target.damageCooldown = damageCooldown;
      target.damageFactor = damageFactor;
      target.upgradeType = upgradeType;
      target.damageType = damageType;
      target.explosionType = explosionType;
      target.minRange = minRange;
      target.maxRange = maxRange;
      target.innerSplashRadius = innerSplashRadius;
      target.medianSplashRadius = medianSplashRadius;
      target.outerSplashRadius = outerSplashRadius;
      target.targetsAir = targetsAir;
      target.targetsGround = targetsGround;
      target.targetsMechanical = targetsMechanical;
      target.targetsOrganic = targetsOrganic;
      target.targetsNonBuilding = targetsNonBuilding;
      target.targetsNonRobotic = targetsNonRobotic;
      target.targetsTerrain = targetsTerrain;
      target.targetsOrgOrMech = targetsOrgOrMech;
      target.targetsOwn = targetsOwn;
      target.whatUses = whatUses;
      target.valid = true;
    }
    void init()
    {
      fillWeaponType(WeaponTypeIDs::Gauss_Rifle, "Gauss Rifle", TechTypeIDs::None, 6, 1, 15, 1, UpgradeTypeIDs::Terran_Infantry_Weapons, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 128, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Terran_Marine);
      fillWeaponType(WeaponTypeIDs::C_10_Canister_Rifle, "C-10 Canister Rifle", TechTypeIDs::None, 10, 1, 22, 1, UpgradeTypeIDs::Terran_Infantry_Weapons, DamageTypeIDs::Concussive, ExplosionTypeIDs::Normal, 0, 224, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Terran_Ghost);
      fillWeaponType(WeaponTypeIDs::Fragmentation_Grenade, "Fragmentation Grenade", TechTypeIDs::None, 20, 2, 30, 1, UpgradeTypeIDs::Terran_Vehicle_Weapons, DamageTypeIDs::Concussive, ExplosionTypeIDs::Normal, 0, 160, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Terran_Vulture);
      fillWeaponType(WeaponTypeIDs::Spider_Mines, "Spider Mines", TechTypeIDs::Spider_Mines, 125, 0, 22, 1, UpgradeTypeIDs::None, DamageTypeIDs::Explosive, ExplosionTypeIDs::Radial_Splash, 0, 10, 50, 75, 100, 0, 1, 0, 0, 1, 0, 0, 0, 0, UnitTypeIDs::Terran_Vulture_Spider_Mine);
      fillWeaponType(WeaponTypeIDs::Twin_Autocannons, "Twin Autocannons", TechTypeIDs::None, 12, 1, 22, 1, UpgradeTypeIDs::Terran_Vehicle_Weapons, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 192, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Terran_Goliath);
      fillWeaponType(WeaponTypeIDs::Hellfire_Missile_Pack, "Hellfire Missile Pack", TechTypeIDs::None, 10, 2, 22, 2, UpgradeTypeIDs::Terran_Vehicle_Weapons, DamageTypeIDs::Explosive, ExplosionTypeIDs::Normal, 0, 160, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Terran_Goliath);
      fillWeaponType(WeaponTypeIDs::Arclite_Cannon, "Arclite Cannon", TechTypeIDs::None, 30, 3, 37, 1, UpgradeTypeIDs::Terran_Vehicle_Weapons, DamageTypeIDs::Explosive, ExplosionTypeIDs::Normal, 0, 224, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Terran_Siege_Tank_Tank_Mode);
      fillWeaponType(WeaponTypeIDs::Fusion_Cutter, "Fusion Cutter", TechTypeIDs::None, 5, 1, 15, 1, UpgradeTypeIDs::None, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 10, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Terran_SCV);
      fillWeaponType(WeaponTypeIDs::Gemini_Missiles, "Gemini Missiles", TechTypeIDs::None, 20, 2, 22, 1, UpgradeTypeIDs::Terran_Ship_Weapons, DamageTypeIDs::Explosive, ExplosionTypeIDs::Normal, 0, 160, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Terran_Wraith);
      fillWeaponType(WeaponTypeIDs::Burst_Lasers, "Burst Lasers", TechTypeIDs::None, 8, 1, 30, 1, UpgradeTypeIDs::Terran_Ship_Weapons, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 160, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Terran_Wraith);
      fillWeaponType(WeaponTypeIDs::ATS_Laser_Battery, "ATS Laser Battery", TechTypeIDs::None, 25, 3, 30, 1, UpgradeTypeIDs::Terran_Ship_Weapons, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 192, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Terran_Battlecruiser);
      fillWeaponType(WeaponTypeIDs::ATA_Laser_Battery, "ATA Laser Battery", TechTypeIDs::None, 25, 3, 30, 1, UpgradeTypeIDs::Terran_Ship_Weapons, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 192, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Terran_Battlecruiser);
      fillWeaponType(WeaponTypeIDs::Flame_Thrower, "Flame Thrower", TechTypeIDs::None, 8, 1, 22, 1, UpgradeTypeIDs::Terran_Infantry_Weapons, DamageTypeIDs::Concussive, ExplosionTypeIDs::Enemy_Splash, 0, 32, 15, 20, 25, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Terran_Firebat);
      fillWeaponType(WeaponTypeIDs::Arclite_Shock_Cannon, "Arclite Shock Cannon", TechTypeIDs::None, 70, 5, 75, 1, UpgradeTypeIDs::Terran_Vehicle_Weapons, DamageTypeIDs::Explosive, ExplosionTypeIDs::Radial_Splash, 64, 384, 10, 25, 40, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Terran_Siege_Tank_Siege_Mode);
      fillWeaponType(WeaponTypeIDs::Longbolt_Missile, "Longbolt Missile", TechTypeIDs::None, 20, 0, 15, 1, UpgradeTypeIDs::None, DamageTypeIDs::Explosive, ExplosionTypeIDs::Normal, 0, 224, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Terran_Missile_Turret);
      fillWeaponType(WeaponTypeIDs::Yamato_Gun, "Yamato Gun", TechTypeIDs::Yamato_Gun, 260, 0, 15, 1, UpgradeTypeIDs::None, DamageTypeIDs::Explosive, ExplosionTypeIDs::Yamato_Gun, 0, 320, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Terran_Battlecruiser);
      fillWeaponType(WeaponTypeIDs::Nuclear_Strike, "Nuclear Strike", TechTypeIDs::Nuclear_Strike, 600, 0, 1, 1, UpgradeTypeIDs::None, DamageTypeIDs::Explosive, ExplosionTypeIDs::Nuclear_Missile, 0, 3, 128, 192, 256, 1, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Terran_Ghost);
      fillWeaponType(WeaponTypeIDs::Lockdown, "Lockdown", TechTypeIDs::Lockdown, 0, 0, 1, 1, UpgradeTypeIDs::None, DamageTypeIDs::Concussive, ExplosionTypeIDs::Lockdown, 0, 256, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, UnitTypeIDs::Terran_Ghost);
      fillWeaponType(WeaponTypeIDs::EMP_Shockwave, "EMP Shockwave", TechTypeIDs::EMP_Shockwave, 0, 0, 1, 1, UpgradeTypeIDs::None, DamageTypeIDs::Concussive, ExplosionTypeIDs::EMP_Shockwave, 0, 256, 64, 64, 64, 1, 1, 0, 0, 0, 0, 1, 0, 0, UnitTypeIDs::Terran_Science_Vessel);
      fillWeaponType(WeaponTypeIDs::Irradiate, "Irradiate", TechTypeIDs::Irradiate, 250, 0, 75, 1, UpgradeTypeIDs::None, DamageTypeIDs::Ignore_Armor, ExplosionTypeIDs::Irradiate, 0, 288, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, UnitTypeIDs::Terran_Science_Vessel);
      fillWeaponType(WeaponTypeIDs::Claws, "Claws", TechTypeIDs::None, 5, 1, 8, 1, UpgradeTypeIDs::Zerg_Melee_Attacks, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 15, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Zerg_Zergling);
      fillWeaponType(WeaponTypeIDs::Needle_Spines, "Needle Spines", TechTypeIDs::None, 10, 1, 15, 1, UpgradeTypeIDs::Zerg_Missile_Attacks, DamageTypeIDs::Explosive, ExplosionTypeIDs::Normal, 0, 128, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Zerg_Hydralisk);
      fillWeaponType(WeaponTypeIDs::Kaiser_Blades, "Kaiser Blades", TechTypeIDs::None, 20, 3, 15, 1, UpgradeTypeIDs::Zerg_Melee_Attacks, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 25, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Zerg_Ultralisk);
      fillWeaponType(WeaponTypeIDs::Toxic_Spores, "Toxic Spores", TechTypeIDs::None, 4, 1, 15, 1, UpgradeTypeIDs::Zerg_Melee_Attacks, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Zerg_Broodling);
      fillWeaponType(WeaponTypeIDs::Spines, "Spines", TechTypeIDs::None, 5, 0, 22, 1, UpgradeTypeIDs::None, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 32, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Zerg_Drone);
      fillWeaponType(WeaponTypeIDs::Acid_Spore, "Acid Spore", TechTypeIDs::None, 20, 2, 30, 1, UpgradeTypeIDs::Zerg_Flyer_Attacks, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 256, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Zerg_Guardian);
      fillWeaponType(WeaponTypeIDs::Glave_Wurm, "Glave Wurm", TechTypeIDs::None, 9, 1, 30, 1, UpgradeTypeIDs::Zerg_Flyer_Attacks, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 96, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Zerg_Mutalisk);
      fillWeaponType(WeaponTypeIDs::Seeker_Spores, "Seeker Spores", TechTypeIDs::None, 15, 0, 15, 1, UpgradeTypeIDs::None, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 224, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Zerg_Spore_Colony);
      fillWeaponType(WeaponTypeIDs::Subterranean_Tentacle, "Subterranean Tentacle", TechTypeIDs::None, 40, 0, 32, 1, UpgradeTypeIDs::None, DamageTypeIDs::Explosive, ExplosionTypeIDs::Normal, 0, 224, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Zerg_Sunken_Colony);
      fillWeaponType(WeaponTypeIDs::Suicide_Infested_Terran, "Suicide Infested Terran", TechTypeIDs::None, 500, 0, 1, 1, UpgradeTypeIDs::None, DamageTypeIDs::Explosive, ExplosionTypeIDs::Radial_Splash, 0, 3, 20, 40, 60, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Zerg_Infested_Terran);
      fillWeaponType(WeaponTypeIDs::Suicide_Scourge, "Suicide Scourge", TechTypeIDs::None, 110, 0, 1, 1, UpgradeTypeIDs::None, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Zerg_Scourge);
      fillWeaponType(WeaponTypeIDs::Parasite, "Parasite", TechTypeIDs::Parasite, 0, 0, 1, 1, UpgradeTypeIDs::None, DamageTypeIDs::Independent, ExplosionTypeIDs::Parasite, 0, 384, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0,UnitTypeIDs::Zerg_Queen);
      fillWeaponType(WeaponTypeIDs::Spawn_Broodlings, "Spawn Broodlings", TechTypeIDs::Spawn_Broodlings, 0, 0, 1, 1, UpgradeTypeIDs::None, DamageTypeIDs::Independent, ExplosionTypeIDs::Broodlings, 0, 288, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0,UnitTypeIDs::Zerg_Queen);
      fillWeaponType(WeaponTypeIDs::Ensnare, "Ensnare", TechTypeIDs::Ensnare, 0, 0, 1, 1, UpgradeTypeIDs::None, DamageTypeIDs::Independent, ExplosionTypeIDs::Ensnare, 0, 288, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0,UnitTypeIDs::Zerg_Queen);
      fillWeaponType(WeaponTypeIDs::Dark_Swarm, "Dark Swarm", TechTypeIDs::Dark_Swarm, 0, 0, 1, 1, UpgradeTypeIDs::None, DamageTypeIDs::Independent, ExplosionTypeIDs::Dark_Swarm, 0, 288, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Zerg_Defiler);
      fillWeaponType(WeaponTypeIDs::Plague, "Plague", TechTypeIDs::Plague, 300, 0, 1, 1, UpgradeTypeIDs::None, DamageTypeIDs::Independent, ExplosionTypeIDs::Plague, 0, 288, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0,UnitTypeIDs::Zerg_Defiler);
      fillWeaponType(WeaponTypeIDs::Consume, "Consume", TechTypeIDs::Consume, 0, 0, 1, 1, UpgradeTypeIDs::None, DamageTypeIDs::Independent, ExplosionTypeIDs::Consume, 0, 16, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1,UnitTypeIDs::Zerg_Defiler);
      fillWeaponType(WeaponTypeIDs::Particle_Beam, "Particle Beam", TechTypeIDs::None, 5, 0, 22, 1, UpgradeTypeIDs::None, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 32, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Protoss_Probe);
      fillWeaponType(WeaponTypeIDs::Psi_Blades, "Psi Blades", TechTypeIDs::None, 8, 1, 22, 1, UpgradeTypeIDs::Protoss_Ground_Weapons, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 15, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Protoss_Zealot);
      fillWeaponType(WeaponTypeIDs::Phase_Disruptor, "Phase Disruptor", TechTypeIDs::None, 20, 2, 30, 1, UpgradeTypeIDs::Protoss_Ground_Weapons, DamageTypeIDs::Explosive, ExplosionTypeIDs::Normal, 0, 128, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Protoss_Dragoon);
      fillWeaponType(WeaponTypeIDs::Psionic_Shockwave, "Psionic Shockwave", TechTypeIDs::None, 30, 3, 20, 1, UpgradeTypeIDs::Protoss_Ground_Weapons, DamageTypeIDs::Normal, ExplosionTypeIDs::Enemy_Splash, 0, 64, 3, 15, 30, 1, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Protoss_Archon);
      fillWeaponType(WeaponTypeIDs::Dual_Photon_Blasters, "Dual Photon Blasters", TechTypeIDs::None, 8, 1, 30, 1, UpgradeTypeIDs::Protoss_Air_Weapons, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 128, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Protoss_Scout);
      fillWeaponType(WeaponTypeIDs::Anti_Matter_Missiles, "Anti-Matter Missiles", TechTypeIDs::None, 14, 1, 22, 2, UpgradeTypeIDs::Protoss_Air_Weapons, DamageTypeIDs::Explosive, ExplosionTypeIDs::Normal, 0, 128, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Protoss_Scout);
      fillWeaponType(WeaponTypeIDs::Phase_Disruptor_Cannon, "Phase Disruptor Cannon", TechTypeIDs::None, 10, 1, 45, 1, UpgradeTypeIDs::Protoss_Air_Weapons, DamageTypeIDs::Explosive, ExplosionTypeIDs::Normal, 0, 160, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Protoss_Arbiter);
      fillWeaponType(WeaponTypeIDs::Pulse_Cannon, "Pulse Cannon", TechTypeIDs::None, 6, 1, 1, 1, UpgradeTypeIDs::Protoss_Air_Weapons, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 128, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Protoss_Interceptor);
      fillWeaponType(WeaponTypeIDs::STS_Photon_Cannon, "STS Photon Cannon", TechTypeIDs::None, 20, 0, 22, 1, UpgradeTypeIDs::None, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 224, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Protoss_Photon_Cannon);
      fillWeaponType(WeaponTypeIDs::STA_Photon_Cannon, "STA Photon Cannon", TechTypeIDs::None, 20, 0, 22, 1, UpgradeTypeIDs::None, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 224, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Protoss_Photon_Cannon);
      fillWeaponType(WeaponTypeIDs::Scarab, "Scarab", TechTypeIDs::None, 100, 25, 1, 1, UpgradeTypeIDs::Scarab_Damage, DamageTypeIDs::Normal, ExplosionTypeIDs::Enemy_Splash, 0, 128, 20, 40, 60, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Protoss_Scarab);
      fillWeaponType(WeaponTypeIDs::Stasis_Field, "Stasis Field", TechTypeIDs::Stasis_Field, 0, 1, 1, 1, UpgradeTypeIDs::None, DamageTypeIDs::Independent, ExplosionTypeIDs::Stasis_Field, 0, 288, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, UnitTypeIDs::Protoss_Arbiter);
      fillWeaponType(WeaponTypeIDs::Psionic_Storm, "Psionic Storm", TechTypeIDs::Psionic_Storm, 14, 1, 45, 1, UpgradeTypeIDs::None, DamageTypeIDs::Ignore_Armor, ExplosionTypeIDs::Radial_Splash, 0, 288, 48, 48, 48, 1, 1, 0, 0, 1, 0, 1, 0, 0,UnitTypeIDs::Protoss_High_Templar);
      fillWeaponType(WeaponTypeIDs::Neutron_Flare, "Neutron Flare", TechTypeIDs::None, 5, 1, 8, 1, UpgradeTypeIDs::Protoss_Air_Weapons, DamageTypeIDs::Explosive, ExplosionTypeIDs::Air_Splash, 0, 160, 5, 50, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Protoss_Corsair);
      fillWeaponType(WeaponTypeIDs::Disruption_Web, "Disruption Web", TechTypeIDs::Disruption_Web, 0, 0, 22, 1, UpgradeTypeIDs::None, DamageTypeIDs::Ignore_Armor, ExplosionTypeIDs::Disruption_Web, 0, 288, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Protoss_Corsair);
      fillWeaponType(WeaponTypeIDs::Restoration, "Restoration", TechTypeIDs::Restoration, 20, 0, 22, 1, UpgradeTypeIDs::None, DamageTypeIDs::Ignore_Armor, ExplosionTypeIDs::Restoration, 0, 192, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, UnitTypeIDs::Terran_Medic);
      fillWeaponType(WeaponTypeIDs::Halo_Rockets, "Halo Rockets", TechTypeIDs::None, 6, 1, 64, 2, UpgradeTypeIDs::Terran_Ship_Weapons, DamageTypeIDs::Explosive, ExplosionTypeIDs::Air_Splash, 0, 192, 5, 50, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Terran_Valkyrie);
      fillWeaponType(WeaponTypeIDs::Corrosive_Acid, "Corrosive Acid", TechTypeIDs::None, 25, 2, 100, 1, UpgradeTypeIDs::Zerg_Flyer_Attacks, DamageTypeIDs::Explosive, ExplosionTypeIDs::Corrosive_Acid, 0, 192, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Zerg_Devourer);
      fillWeaponType(WeaponTypeIDs::Mind_Control, "Mind Control", TechTypeIDs::Mind_Control, 8, 1, 22, 1, UpgradeTypeIDs::None, DamageTypeIDs::Normal, ExplosionTypeIDs::Mind_Control, 0, 256, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, UnitTypeIDs::Protoss_Dark_Archon);
      fillWeaponType(WeaponTypeIDs::Feedback, "Feedback", TechTypeIDs::Feedback, 8, 1, 22, 1, UpgradeTypeIDs::None, DamageTypeIDs::Ignore_Armor, ExplosionTypeIDs::Feedback, 0, 320, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, UnitTypeIDs::Protoss_Dark_Archon);
      fillWeaponType(WeaponTypeIDs::Optical_Flare, "Optical Flare", TechTypeIDs::Optical_Flare, 8, 1, 22, 1, UpgradeTypeIDs::None, DamageTypeIDs::Independent, ExplosionTypeIDs::Optical_Flare, 0, 288, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Terran_Medic);
      fillWeaponType(WeaponTypeIDs::Maelstrom, "Maelstrom", TechTypeIDs::Maelstrom, 0, 1, 1, 1, UpgradeTypeIDs::None, DamageTypeIDs::Independent, ExplosionTypeIDs::Maelstrom, 0, 320, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, UnitTypeIDs::Protoss_Dark_Archon);
      fillWeaponType(WeaponTypeIDs::Subterranean_Spines, "Subterranean Spines", TechTypeIDs::None, 20, 2, 37, 1, UpgradeTypeIDs::Zerg_Missile_Attacks, DamageTypeIDs::Normal, ExplosionTypeIDs::Enemy_Splash, 0, 192, 20, 20, 20, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Zerg_Lurker);
      fillWeaponType(WeaponTypeIDs::Warp_Blades, "Warp Blades", TechTypeIDs::None, 40, 3, 30, 1, UpgradeTypeIDs::Protoss_Ground_Weapons, DamageTypeIDs::Normal, ExplosionTypeIDs::Normal, 0, 15, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::Protoss_Dark_Templar);
      fillWeaponType(WeaponTypeIDs::None, "None", TechTypeIDs::None, 0, 0, 0, 0, UpgradeTypeIDs::None, DamageTypeIDs::None, ExplosionTypeIDs::None, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, UnitTypeIDs::None);

      weaponTypeSet.insert(WeaponTypeIDs::Gauss_Rifle);
      weaponTypeSet.insert(WeaponTypeIDs::C_10_Canister_Rifle);
      weaponTypeSet.insert(WeaponTypeIDs::Fragmentation_Grenade);
      weaponTypeSet.insert(WeaponTypeIDs::Spider_Mines);
      weaponTypeSet.insert(WeaponTypeIDs::Twin_Autocannons);
      weaponTypeSet.insert(WeaponTypeIDs::Hellfire_Missile_Pack);
      weaponTypeSet.insert(WeaponTypeIDs::Arclite_Cannon);
      weaponTypeSet.insert(WeaponTypeIDs::Fusion_Cutter);
      weaponTypeSet.insert(WeaponTypeIDs::Gemini_Missiles);
      weaponTypeSet.insert(WeaponTypeIDs::Burst_Lasers);
      weaponTypeSet.insert(WeaponTypeIDs::ATS_Laser_Battery);
      weaponTypeSet.insert(WeaponTypeIDs::ATA_Laser_Battery);
      weaponTypeSet.insert(WeaponTypeIDs::Flame_Thrower);
      weaponTypeSet.insert(WeaponTypeIDs::Arclite_Shock_Cannon);
      weaponTypeSet.insert(WeaponTypeIDs::Longbolt_Missile);
      weaponTypeSet.insert(WeaponTypeIDs::Claws);
      weaponTypeSet.insert(WeaponTypeIDs::Needle_Spines);
      weaponTypeSet.insert(WeaponTypeIDs::Kaiser_Blades);
      weaponTypeSet.insert(WeaponTypeIDs::Toxic_Spores);
      weaponTypeSet.insert(WeaponTypeIDs::Spines);
      weaponTypeSet.insert(WeaponTypeIDs::Acid_Spore);
      weaponTypeSet.insert(WeaponTypeIDs::Glave_Wurm);
      weaponTypeSet.insert(WeaponTypeIDs::Seeker_Spores);
      weaponTypeSet.insert(WeaponTypeIDs::Subterranean_Tentacle);
      weaponTypeSet.insert(WeaponTypeIDs::Suicide_Infested_Terran);
      weaponTypeSet.insert(WeaponTypeIDs::Suicide_Scourge);
      weaponTypeSet.insert(WeaponTypeIDs::Particle_Beam);
      weaponTypeSet.insert(WeaponTypeIDs::Psi_Blades);
      weaponTypeSet.insert(WeaponTypeIDs::Phase_Disruptor);
      weaponTypeSet.insert(WeaponTypeIDs::Psionic_Shockwave);
      weaponTypeSet.insert(WeaponTypeIDs::Dual_Photon_Blasters);
      weaponTypeSet.insert(WeaponTypeIDs::Anti_Matter_Missiles);
      weaponTypeSet.insert(WeaponTypeIDs::Phase_Disruptor_Cannon);
      weaponTypeSet.insert(WeaponTypeIDs::Pulse_Cannon);
      weaponTypeSet.insert(WeaponTypeIDs::STS_Photon_Cannon);
      weaponTypeSet.insert(WeaponTypeIDs::STA_Photon_Cannon);
      weaponTypeSet.insert(WeaponTypeIDs::Scarab);
      weaponTypeSet.insert(WeaponTypeIDs::Neutron_Flare);
      weaponTypeSet.insert(WeaponTypeIDs::Halo_Rockets);
      weaponTypeSet.insert(WeaponTypeIDs::Corrosive_Acid);
      weaponTypeSet.insert(WeaponTypeIDs::Subterranean_Spines);
      weaponTypeSet.insert(WeaponTypeIDs::Warp_Blades);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Gauss_Rifle);
      normalWeaponTypeSet.insert(WeaponTypeIDs::C_10_Canister_Rifle);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Fragmentation_Grenade);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Spider_Mines);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Twin_Autocannons);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Hellfire_Missile_Pack);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Arclite_Cannon);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Fusion_Cutter);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Gemini_Missiles);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Burst_Lasers);
      normalWeaponTypeSet.insert(WeaponTypeIDs::ATS_Laser_Battery);
      normalWeaponTypeSet.insert(WeaponTypeIDs::ATA_Laser_Battery);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Flame_Thrower);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Arclite_Shock_Cannon);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Longbolt_Missile);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Claws);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Needle_Spines);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Kaiser_Blades);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Toxic_Spores);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Spines);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Acid_Spore);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Glave_Wurm);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Seeker_Spores);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Subterranean_Tentacle);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Suicide_Infested_Terran);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Suicide_Scourge);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Particle_Beam);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Psi_Blades);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Phase_Disruptor);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Psionic_Shockwave);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Dual_Photon_Blasters);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Anti_Matter_Missiles);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Phase_Disruptor_Cannon);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Pulse_Cannon);
      normalWeaponTypeSet.insert(WeaponTypeIDs::STS_Photon_Cannon);
      normalWeaponTypeSet.insert(WeaponTypeIDs::STA_Photon_Cannon);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Scarab);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Neutron_Flare);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Halo_Rockets);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Corrosive_Acid);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Subterranean_Spines);
      normalWeaponTypeSet.insert(WeaponTypeIDs::Warp_Blades);
      weaponTypeSet.insert(WeaponTypeIDs::Yamato_Gun);
      weaponTypeSet.insert(WeaponTypeIDs::Nuclear_Strike);
      weaponTypeSet.insert(WeaponTypeIDs::Lockdown);
      weaponTypeSet.insert(WeaponTypeIDs::EMP_Shockwave);
      weaponTypeSet.insert(WeaponTypeIDs::Irradiate);
      weaponTypeSet.insert(WeaponTypeIDs::Parasite);
      weaponTypeSet.insert(WeaponTypeIDs::Spawn_Broodlings);
      weaponTypeSet.insert(WeaponTypeIDs::Ensnare);
      weaponTypeSet.insert(WeaponTypeIDs::Dark_Swarm);
      weaponTypeSet.insert(WeaponTypeIDs::Plague);
      weaponTypeSet.insert(WeaponTypeIDs::Consume);
      weaponTypeSet.insert(WeaponTypeIDs::Stasis_Field);
      weaponTypeSet.insert(WeaponTypeIDs::Psionic_Storm);
      weaponTypeSet.insert(WeaponTypeIDs::Disruption_Web);
      weaponTypeSet.insert(WeaponTypeIDs::Restoration);
      weaponTypeSet.insert(WeaponTypeIDs::Mind_Control);
      weaponTypeSet.insert(WeaponTypeIDs::Feedback);
      weaponTypeSet.insert(WeaponTypeIDs::Optical_Flare);
      weaponTypeSet.insert(WeaponTypeIDs::Maelstrom);
      specialWeaponTypeSet.insert(WeaponTypeIDs::Yamato_Gun);
      specialWeaponTypeSet.insert(WeaponTypeIDs::Nuclear_Strike);
      specialWeaponTypeSet.insert(WeaponTypeIDs::Lockdown);
      specialWeaponTypeSet.insert(WeaponTypeIDs::EMP_Shockwave);
      specialWeaponTypeSet.insert(WeaponTypeIDs::Irradiate);
      specialWeaponTypeSet.insert(WeaponTypeIDs::Parasite);
      specialWeaponTypeSet.insert(WeaponTypeIDs::Spawn_Broodlings);
      specialWeaponTypeSet.insert(WeaponTypeIDs::Ensnare);
      specialWeaponTypeSet.insert(WeaponTypeIDs::Dark_Swarm);
      specialWeaponTypeSet.insert(WeaponTypeIDs::Plague);
      specialWeaponTypeSet.insert(WeaponTypeIDs::Consume);
      specialWeaponTypeSet.insert(WeaponTypeIDs::Stasis_Field);
      specialWeaponTypeSet.insert(WeaponTypeIDs::Psionic_Storm);
      specialWeaponTypeSet.insert(WeaponTypeIDs::Disruption_Web);
      specialWeaponTypeSet.insert(WeaponTypeIDs::Restoration);
      specialWeaponTypeSet.insert(WeaponTypeIDs::Mind_Control);
      specialWeaponTypeSet.insert(WeaponTypeIDs::Feedback);
      specialWeaponTypeSet.insert(WeaponTypeIDs::Optical_Flare);
      specialWeaponTypeSet.insert(WeaponTypeIDs::Maelstrom);

      weaponTypeSet.insert(WeaponTypeIDs::None);
      for(std::set<WeaponTypeID>::iterator i = weaponTypeSet.begin(); i != weaponTypeSet.end(); i++)
      {
        weaponTypeMap.insert(std::make_pair(std::string(weaponTypeData[*i].name), *i));
      }
    }
  }
}
