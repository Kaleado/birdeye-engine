#ifndef WEAPONMOD_H
#define WEAPONMOD_H

#include "Weapon.hpp"

/*
  Class representing a modification to a weapon, e.g. faster firing
  speed, fires rockets instead of bullets, etcetera.
  Subclass this to make more mods.
 */
class WeaponMod {
public:
  std::string getName();
  bool isAcquired();//Whether the player has chosen to acquire this mod.
  bool acquire();
  void remove();
  virtual void tick(){}
  virtual void handleInput(sf::Event event){};//Handles and responds to input every frame.
  virtual void whenAcquired()=0;//This should apply the mod effects - used when the mod is first installed on the weapon.
  virtual void whenRemoved()=0;//This should remove the mod effects - used when the mod is removed from the weapon.
  WeaponMod(std::string name, std::shared_ptr<Weapon> weapon) : _name{name}, _weapon{weapon} {}
protected:
  std::string _name;
  bool _isAcquired=false;
  std::shared_ptr<Weapon> _weapon;
};

class GlobalMovementSpeed : public WeaponMod {
public:
  void whenAcquired();//This should apply the mod effects.
  void whenRemoved();//This should remove the mod effects.
  GlobalMovementSpeed(std::shared_ptr<Weapon> weapon, double multiplier) : WeaponMod{"GlobalMovementSpeed", weapon} {
    _multiplier = multiplier;
  }
private:
  double _multiplier;
};

#endif
