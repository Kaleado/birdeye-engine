#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Render.hpp"
#include "Player.hpp"
#include "Thing.hpp"
#include "Cursor.hpp"
#include "Playfield.hpp"
#include "Bullet.hpp"

//!Mods currently have different quality levels.
enum ModQuality { MQ_COMMON, MQ_UNCOMMONM, MQ_RARE, MQ_EPIC, MQ_LEGENDARY, MQ_UNDEFINED };

/**
  The current state of a given weapon:
  - WS_STOWED: the weapon is equipped, but not currently active.
  - WS_IDLE: the weapon is currently active and ready to fire.
  - WS_FIRING_PRIMARY: the weapon is being fired with the primary fire button.
  - WS_FIRING_SECONDARY: the weapon is being fired with the secondary fire button.
 */
enum WeaponState {  WS_STOWED, WS_IDLE, WS_FIRING_PRIMARY, WS_FIRING_SECONDARY};
class Weapon;
class WeaponMod;
class ModTree;

/**
  A private data encapsulation class that encapsulates the mods
  attached to a weapon, as well as the progression system surrounding
  it. This class should not be exposed.
 */
class ModTree {
protected:
  //!The next mod quality the player can choose upon levelling the weapon.
  ModQuality _nextToChoose = MQ_COMMON;

  //!Whether the player is _permitted_ to choose the next mod.
  bool _isLocked;
  
  //!The mods in the tree.
  std::map<ModQuality, std::vector<std::shared_ptr<WeaponMod>>> _mods;
public:
  bool isLocked();
  std::vector<std::shared_ptr<WeaponMod>>& getModsOfQuality(ModQuality quality);
  std::vector<std::shared_ptr<WeaponMod>>& getAvailableMods();  
  void reset();
  void lock();
  void unlock();
  ModTree() = default;
  ModTree(std::map<ModQuality, std::vector<std::shared_ptr<WeaponMod>>> mods) : _mods{mods}{}
};

/**
  Class representing a weapon and its firing modes. Create actual
  weapons by subclassing this (demonstrated in Smg.hpp, etc.).
 */
class Weapon {
  friend class WeaponMod;
protected:
  ModTree _modTree;

  //!Clears the bonuses from the player's stats.
  void _removeGlobalBonuses();

  //!Adds the bonuses to the player's stats.
  void _applyGlobalBonuses();

  //!Complete the reload process and refill the gun with ammo.
  void _finishReload();
  
  int _reloadTime;//!Number of frames to reload the gun.
  int _maxAmmo;
  int _curAmmo;
  bool _isActive=false;
public:
  //!Stat bonuses. Check Stats.hpp if this doesn't make sense.
  Stats globalStatBonuses = {0, 0.0, 0.0, 0.0, 0.0, 0.0};

  //!Returns a vector containing the mods of a given quality.
  std::vector<std::shared_ptr<WeaponMod>>& getModsOfQuality(ModQuality quality);

  //!Gets the mods that are currently available for the player to
  //!acquire (i.e. excluding mods that have been acquired or are beyond
  //!the current quality level).
  std::vector<std::shared_ptr<WeaponMod>>& getAvailableMods();

  //!Acquires a mod that is assumed to exist in the weapon's mod tree.
  void acquireMod(std::shared_ptr<WeaponMod> mod);

  //!Handles when the player presses/releases the primary/secondary fire buttons.
  virtual void pressPrimaryFire(sf::Vector2f target);
  virtual void pressSecondaryFire(sf::Vector2f target);
  virtual void releasePrimaryFire(sf::Vector2f target);
  virtual void releaseSecondaryFire(sf::Vector2f target);

  //!Executed every frame - implement weapon logic in this function.
  virtual void tick() = 0;

  //!Executed when the weapon is (un)equipped in the player's weapon bar.
  virtual void onEquip();
  virtual void onUnequip();

  //!Executed when the player switches to and away from the weapon.
  virtual void onStow();
  virtual void onUnstow();

  //!Fills the weapon with randomly-selected mods.
  virtual void fillWithMods();

  WeaponState weaponState=WS_STOWED;

  Weapon() = default;
  Weapon(int maxAmmo, int reloadTime) : _maxAmmo{maxAmmo}, _reloadTime{reloadTime}, _curAmmo{maxAmmo} {}
};

#endif
