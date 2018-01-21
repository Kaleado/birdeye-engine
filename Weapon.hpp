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

enum ModQuality { MQ_COMMON, MQ_UNCOMMONM, MQ_RARE, MQ_EPIC, MQ_LEGENDARY, MQ_UNDEFINED };
enum WeaponState {  WS_STOWED, WS_IDLE, WS_FIRING_PRIMARY, WS_FIRING_SECONDARY};
class Weapon;
class WeaponMod;
class ModTree;

class ModTree {
protected:
  //The next mod quality the player can choose upon levelling the weapon.
  ModQuality _nextToChoose = MQ_COMMON;
  bool _isLocked;//Whether the player is _permitted_ to choose the next mod.
  //The mods in the tree.
  std::map<ModQuality, std::vector<std::shared_ptr<WeaponMod>>> _mods;
public:
  bool isLocked();
  std::vector<std::shared_ptr<WeaponMod>>& getModsOfQuality(ModQuality quality);
  std::vector<std::shared_ptr<WeaponMod>>& getAvailableMods();  
  void reset();
  void lock();
  void unlock();
  ModTree(){}
  ModTree(std::map<ModQuality, std::vector<std::shared_ptr<WeaponMod>>> mods) : _mods{mods}{}
};

/*
  Class representing a weapon and its firing modes. Create actual
  weapons by subclassing this (demonstrated below).
 */
class Weapon {
  friend class WeaponMod;
protected:
  ModTree _modTree;
  void _removeGlobalBonuses();//Clears the bonuses from the player's stats.
  void _applyGlobalBonuses();//Adds the bonuses to the player's stats.
  void _finishReload();  
  int _reloadTime;
  int _maxAmmo;
  int _curAmmo;
  bool _isActive;
public:
  Stats globalStatBonuses = {0, 0.0, 0.0, 0.0, 0.0, 0.0};
  std::vector<std::shared_ptr<WeaponMod>>& getModsOfQuality(ModQuality quality);
  std::vector<std::shared_ptr<WeaponMod>>& getAvailableMods();  
  void acquireMod(std::shared_ptr<WeaponMod> mod);//Acquires a mod that is assumed to exist in the weapon's mod tree.
  virtual void pressPrimaryFire(sf::Vector2f target);
  virtual void pressSecondaryFire(sf::Vector2f target);
  virtual void releasePrimaryFire(sf::Vector2f target);
  virtual void releaseSecondaryFire(sf::Vector2f target);
  virtual void tick() = 0;
  virtual void onEquip();
  virtual void onUnequip();
  virtual void onStow();
  virtual void onUnstow();
  virtual void fillWithMods();
  WeaponState weaponState=WS_STOWED;
  Weapon(int maxAmmo, int reloadTime) : _maxAmmo{maxAmmo}, _reloadTime{reloadTime} {}
};

#endif
