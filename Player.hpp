#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include "Ability.hpp"
#include "Thing.hpp"
#include "Cursor.hpp"
#include "Stats.hpp"

const int NUM_WEAPONS = 5;

class Weapon;
class Ability;
class Player;

extern std::shared_ptr<Player> player;

/*
  Class representing the player.
 */
class Player : public Thing {
public:
  //Player stats.
  Stats stats = {100, 1.0, 1.0, 1.0, 1.0, 1.0};
  
  void die();
  void tick();
  void giveWeapon(std::shared_ptr<Weapon> weapon);
  void handleInput(sf::Event event);
  void setPrimaryAbility(std::shared_ptr<Ability> abl);
  void setMovementAbility(std::shared_ptr<Ability> abl);
  void setSprintAbility(std::shared_ptr<Ability> abl);
  int getCurrentHp();
  void nextWeapon();
  void previousWeapon();
  void switchToWeapon(std::shared_ptr<Weapon> newWeapon);
  void damage(int amount);
  void removeWeapon(int weaponIndex);
  //Returns false if the weapon couldn't be inserted (if something was already present in that WeaponWidget), or true if everything was dandy.
  bool insertWeapon(int weaponIndex, std::shared_ptr<Weapon> weapon);
  Player(std::string path, sf::Vector2f position, double baseSpeed=5.0) : Thing(path, position) {
    _baseSpeed = baseSpeed;
    for(int i = 0; i < NUM_WEAPONS; ++i){
      _weapons[i] = nullptr;
    }
  };
  Player(){};
private:
  void _unequipCurrentWeapon();
  std::array<std::shared_ptr<Weapon>, NUM_WEAPONS> _weapons;
  std::shared_ptr<Weapon> _curWeapon;
  int _curWeaponIndex=0;//Index of the currently selected weapon in the _weapons array.
  std::shared_ptr<Ability> _primaryAbility;
  std::shared_ptr<Ability> _movementAbility;
  std::shared_ptr<Ability> _sprintAbility;

  //Player stats.
  int _curHp=100;
  double _baseSpeed;
};

#endif
