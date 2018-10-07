#ifndef WEAPONMOD_H
#define WEAPONMOD_H

#include "Weapon.hpp"

/**
  Class representing a modification to a weapon, e.g. faster firing
  speed, fires rockets instead of bullets, etcetera.  Subclass this to
  make more mods.
  
  TO BE HONEST I DON'T THINK THIS CLASS IS REALLY WELL WRITTEN.
 */
class WeaponMod {
public:
  //!Duh.
  std::string getName();

  //!Returns whether the player has chosen to acquire this mod.
  bool isAcquired();

  //!Acquires this mod and makes its effects active on the weapon.
  bool acquire();

  //!Un-acquires the mod, removing its effects on the weapon.
  void remove();

  //!Executed every frame.
  virtual void tick(){}

  //!Handles and responds to input every frame.
  virtual void handleInput(sf::Event event){};

  //!This should apply the mod effects - used when the mod is first installed on the weapon.
  virtual void whenAcquired()=0;

  //!This should remove the mod effects - used when the mod is removed from the weapon.
  virtual void whenRemoved()=0;
  WeaponMod(std::string name, std::shared_ptr<Weapon> weapon) : _name{name}, _weapon{weapon} {}
protected:
  std::string _name;
  bool _isAcquired=false;
  std::shared_ptr<Weapon> _weapon;
};

//!An example mod.
class GlobalMovementSpeed : public WeaponMod {
public:
  //!This should apply the mod effects.
  void whenAcquired();

  //!This should remove the mod effects.
  void whenRemoved();
  
  GlobalMovementSpeed(std::shared_ptr<Weapon> weapon, double multiplier) : WeaponMod{"GlobalMovementSpeed", weapon} {
    _multiplier = multiplier;
  }
private:
  double _multiplier;
};

#endif
