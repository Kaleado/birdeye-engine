#include "Weapon.hpp"

bool ModTree::isLocked(){
  return _isLocked;
}

std::vector<std::shared_ptr<WeaponMod>>& ModTree::getModsOfQuality(ModQuality quality){
  return _mods[quality];
}

std::vector<std::shared_ptr<WeaponMod>>& ModTree::getAvailableMods(){
  return getModsOfQuality(_nextToChoose);
}
  
void ModTree::reset(){
  //do this later.
}

void ModTree::lock(){
  _isLocked = true;
}

void ModTree::unlock(){
  _isLocked = false;
}

//TODO: complete this so generate some actual mods.
void Weapon::fillWithMods(){
  std::vector<std::shared_ptr<WeaponMod>> commonMods;
  std::map<ModQuality, std::vector<std::shared_ptr<WeaponMod>>> mods;
  mods[MQ_COMMON] = commonMods;
  _modTree = ModTree{mods};
}

std::vector<std::shared_ptr<WeaponMod>>& Weapon::getModsOfQuality(ModQuality quality){
  return _modTree.getModsOfQuality(quality);
}

std::vector<std::shared_ptr<WeaponMod>>& Weapon::getAvailableMods(){
  return _modTree.getAvailableMods();
}


void Weapon::_finishReload(){
  _curAmmo = _maxAmmo;
}

void Weapon::pressPrimaryFire(sf::Vector2f target){
  weaponState = WS_FIRING_PRIMARY;
}

void Weapon::pressSecondaryFire(sf::Vector2f target){
  weaponState = WS_FIRING_SECONDARY;
}

void Weapon::releasePrimaryFire(sf::Vector2f target){
  weaponState = WS_IDLE;
}

void Weapon::_applyGlobalBonuses(){
  player->stats += globalStatBonuses;
}

void Weapon::_removeGlobalBonuses(){
  player->stats -= globalStatBonuses;
}

void Weapon::releaseSecondaryFire(sf::Vector2f target){
  weaponState = WS_IDLE;
}

void Weapon::onEquip(){
  //Add global bonuses on the weapon to the player.
  _applyGlobalBonuses();
}

void Weapon::onUnequip(){
  //Remove global bonuses on the weapon from the player.
  _removeGlobalBonuses();
}

void Weapon::onStow(){
  //Add local bonuses on the weapon to the player.
}

void Weapon::onUnstow(){
  //Remove local bonuses on the weapon from the player.
}
