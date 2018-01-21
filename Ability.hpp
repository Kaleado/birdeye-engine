#ifndef ABILITY_H
#define ABILITY_H

#include "Player.hpp"

enum AbilityState { AS_READY, AS_PRESSED, AS_RELEASED, AS_COOLDOWN};

class Ability {
public:
  virtual void press() = 0;//Do this when the button for the ability is pressed.
  virtual void release() = 0;//Do this when the button for the ability is released.
  virtual void tick() = 0;//Do this every frame.
protected:  
  int _cooldownCountdown;
  int _cooldownLength;
  AbilityState abilityState;
};

class HoldAbility : public Ability {
public:
  void press();//Do this when the button for the ability is pressed.
  void release();//Do this when the button for the ability is released.
  void tick();//Do this every frame.
protected:
  virtual void _whileActive(){};
  virtual void _activate(){};
  virtual void _deactivate(){};
  bool _isHeld=false;
};

class ChanneledAbility : public Ability {
public:
  void press();//Do this when the button for the ability is pressed.
  void release();//Do this when the button for the ability is released.
  void tick();//Do this every frame.
protected:
  virtual void _whileActive() = 0;
  int _channelCountdown;
  int _channelLength;
};

class ToggledAbility : public Ability {
public:
  void press();//Do this when the button for the ability is pressed.
  void release();//Do this when the button for the ability is released.
  void tick();//Do this every frame.
protected:
  bool _isActive=false;
  virtual void _activate(){};
  virtual void _deactivate(){};
  virtual void _whileActive(){};
};

class CastTimeAbility : public Ability {
public:
  void press();//Do this when the button for the ability is pressed.
  void release();//Do this when the button for the ability is released.
  void tick();//Do this every frame.
protected:
  int _castTimeCountdown;
  int _castTimeLength;
  virtual void _onUse() = 0;
};

class Sprint : public HoldAbility {
public:
  Sprint(double speedFactor) : _speedFactor{speedFactor} {};
protected:
  double _speedFactor;
  void _activate();
  void _deactivate();
};

#endif
