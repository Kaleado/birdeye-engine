#include "WeaponMod.hpp"

std::string WeaponMod::getName(){
  return _name;
}

bool WeaponMod::isAcquired(){
  return _isAcquired;
}

bool WeaponMod::acquire(){
  if(!_isAcquired){
    _weapon->_removeGlobalBonuses();
    whenAcquired();
    _isAcquired = true;
    _weapon->_applyGlobalBonuses();
    return true;
  }
  return false;
}

void WeaponMod::remove(){
  whenRemoved();
  _isAcquired = false;
}

void GlobalMovementSpeed::whenAcquired(){
  _weapon->globalStatBonuses.speedMultiplier += _multiplier;
}

void GlobalMovementSpeed::whenRemoved(){
  _weapon->globalStatBonuses.speedMultiplier -= _multiplier;
}
