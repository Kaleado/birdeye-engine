#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include "Ability.hpp"
#include "Thing.hpp"
#include "Cursor.hpp"
#include "Stats.hpp"

//!Number of weapons in the weapon bar.
const int NUM_WEAPONS = 5;

class Weapon;
class Ability;
class Player;

extern std::shared_ptr<Player> player;

/**
  Class representing the player. The player can have Primary, Sprint, and Movement Abilities:
  - Primary Ability: typically an offensive or crowd control ability to supplement the player's guns.
  - Sprint Ability: an ability that is used for fast movement between hordes of enemies or across the map.
  - Movement Ability: an ability for quick repositioning during combat, such as a dodge roll or a short blink.
 */
class Player : public Thing {
public:
    //!Player stats - check the corresponding class in Stats.hpp if you
    //!don't know what this means.
    Stats stats = {100, 1.0, 1.0, 1.0, 1.0, 1.0};

    //!Run when the player dies.
    void die();

    //!This function is executed every frame.
    void tick();

    //!Give the player a new weapon. This is mostly for debugging at the
    //!moment, since a weapon will typically be placed into a weapon
    //!slot, rather than just being 'given' to the player.
    void giveWeapon(std::shared_ptr<Weapon> weapon);

    //!Handle the given event. If you want to bind a key or mouse click
    //!or something, this is the place to do it.
    void handleInput(sf::Event event);

    //!Set the player's Primary Ability.
    void setPrimaryAbility(std::shared_ptr<Ability> abl);

    //!Set the player's Movement Ability.
    void setMovementAbility(std::shared_ptr<Ability> abl);

    //!Set the player's Sprint Ability.
    void setSprintAbility(std::shared_ptr<Ability> abl);

    //!Obvious.
    int getCurrentHp();

    //!Switches to the next weapon in the weapon bar.
    void nextWeapon();

    //!Switches to the previous weapon in the weapon bar.
    void previousWeapon();

    //!Switches to a particular weapon.
    void switchToWeapon(std::shared_ptr<Weapon> newWeapon);

    //!Deal damage to the player.
    void damage(int amount);

    //!Removes the weapon in the corresponding index of the weapon bar.
    void removeWeapon(int weaponIndex);

    //!Inserts a weapon into a particular slot of the weapon bar.
    //!Returns false if the weapon couldn't be inserted (if something was already present in that WeaponWidget), or true if everything was dandy.
    bool insertWeapon(int weaponIndex, std::shared_ptr<Weapon> weapon);

    Player(std::string path, sf::Vector2f position, double baseSpeed, sf::FloatRect hitboxAtZeroZero) : Thing(path, position, hitboxAtZeroZero) {
        _baseSpeed = baseSpeed;
        for(int i = 0; i < NUM_WEAPONS; ++i){
            _weapons[i] = nullptr;
        }
        this->_name = "Player";
    };
    Player(){};

private:

    //!Time that the player is invulnerable for.
    int _invulnTime=0;

    //!Changes the creature's sprite based on the direction they're facing.
    void _changeImageBasedOnFacing();

    //!Duh.
    void _unequipCurrentWeapon();

    //!These are the weapons that the player has in their weapon bar.
    std::array<std::shared_ptr<Weapon>, NUM_WEAPONS> _weapons;

    //!This is the current weapon that the player is using.
    std::shared_ptr<Weapon> _curWeapon;

    //!Index of the currently selected weapon in the _weapons array.
    int _curWeaponIndex=0;

    //!Primary, movement, and sprint abilities.
    std::shared_ptr<Ability> _primaryAbility;
    std::shared_ptr<Ability> _movementAbility;
    std::shared_ptr<Ability> _sprintAbility;

    //!Player stats.
    int _curHp=100;

    //!Maximum number of pixels per frame that the player can move.
    double _baseSpeed;
};

#endif
