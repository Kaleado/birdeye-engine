#ifndef ABILITY_H
#define ABILITY_H

#include "Player.hpp"

/**
  Represents the current state of an ability.
  - AS_READY: the ability is ready and can be used again.
  - AS_PRESSED: the key corresponding to the ability is currently held down.
  - AS_RELEASED: the key corresponding to the ability has just been released.
  - AS_COOLDOWN: the ability is currently on cooldown and cannot be used
    until the cooldown expires.
 */
enum AbilityState { AS_READY, AS_PRESSED, AS_RELEASED, AS_COOLDOWN};

/**
  Class representing an ability that the player can use. This class is
  subclassed by the classes below to provide different methods of
  activation, a la World of Warcraft or Overwatch. In fact, most of
  these ability types are copied from those used internally in
  Overwatch. To add a new ability, you typically want to subclass the
  classes below, unless your ability behaves in a _very_ unique way.
 */
class Ability {
public:
  //!Do this when the button for the ability is pressed.
  virtual void press() = 0;

  //!Do this when the button for the ability is released.
  virtual void release() = 0;

  //!Do this every frame.
  virtual void tick() = 0;
protected:  
  int _cooldownCountdown;
  int _cooldownLength;
  AbilityState abilityState;
};

//!An ability whose assigned key must be held down to use.
class HoldAbility : public Ability {
public:
  //!Do this when the button for the ability is pressed.
  void press();

  //!Do this when the button for the ability is released.
  void release();

  //!Do this every frame.
  void tick();
protected:
  virtual void _whileActive(){};
  virtual void _activate(){};
  virtual void _deactivate(){};
  bool _isHeld=false;
};

/**
   An ability that is activated instantly, and then whose effects
   linger for a fixed period of 'channeling' time afterwards.
*/
class ChanneledAbility : public Ability {
public:
  //!Do this when the button for the ability is pressed.
  void press();

  //!Do this when the button for the ability is released.
  void release();

  //!Do this every frame.
  void tick();
protected:
  virtual void _whileActive() = 0;
  int _channelCountdown;
  int _channelLength;
};

/**
   An ability that can be instantly toggled on and off by pressing the key.
*/
class ToggledAbility : public Ability {
public:
  //!Do this when the button for the ability is pressed.
  void press();

  //!Do this when the button for the ability is released.
  void release();

  //!Do this every frame.
  void tick();
protected:
  bool _isActive=false;
  virtual void _activate(){};
  virtual void _deactivate(){};
  virtual void _whileActive(){};
};

/**
   An ability that is activated after a short 'cast time'.
*/
class CastTimeAbility : public Ability {
public:
  //!Do this when the button for the ability is pressed.
  void press();

  //!Do this when the button for the ability is released.
  void release();

  //!Do this every frame.
  void tick();
protected:
  int _castTimeCountdown;
  int _castTimeLength;
  virtual void _onUse() = 0;
};

/**
   This is really just to demonstrate how to add a new ability. In this
   case, this is a 'sprint' ability that speeds the player up whilst
   the key is held down.
*/
class Sprint : public HoldAbility {
public:
  Sprint(double speedFactor) : _speedFactor{speedFactor} {};
protected:
  double _speedFactor;
  void _activate();
  void _deactivate();
};

#endif
