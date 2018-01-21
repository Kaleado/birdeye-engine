#include "Ability.hpp"

void HoldAbility::press(){
  _isHeld = true;
  _activate();
}

void HoldAbility::release(){
  _isHeld = false;
  _deactivate();
}

void HoldAbility::tick(){
  if(_isHeld){
    _whileActive();
  }
}

void ChanneledAbility::press(){
  //Does not need to do anything.
}

void ChanneledAbility::release(){
  if(abilityState == AS_READY){
    _channelCountdown = _channelLength;
    abilityState = AS_PRESSED;
  }
}

void ChanneledAbility::tick(){
  if(abilityState == AS_PRESSED){
    _whileActive();
    if(--_channelCountdown <= 0){
      _cooldownCountdown = _cooldownLength;
      abilityState = AS_COOLDOWN;      
    }
  }
  else if(abilityState == AS_COOLDOWN){
    if(--_cooldownCountdown <= 0){
      abilityState = AS_READY;
    }
  }
}

void ToggledAbility::press(){
}

void ToggledAbility::release(){
  _isActive = !_isActive;
  _isActive ? _activate() : _deactivate();
}

void ToggledAbility::tick(){
  if(_isActive){
    _whileActive();
  }
}

void CastTimeAbility::press(){
  //No need to do anything.
}

void CastTimeAbility::release(){
  if(abilityState == AS_READY){
    _castTimeCountdown = _castTimeLength;
  }
}

void CastTimeAbility::tick(){
  if(abilityState == AS_PRESSED){
    if(--_castTimeCountdown <= 0){
      _onUse();
      abilityState = AS_COOLDOWN;
      _cooldownCountdown = _cooldownLength;
    }
  }
  else if(abilityState == AS_COOLDOWN){
    if(--_cooldownCountdown <= 0){
      abilityState = AS_READY;
    }
  }
}

void Sprint::_activate(){
  player->stats.speedMultiplier += _speedFactor;
}

void Sprint::_deactivate(){
  player->stats.speedMultiplier -= _speedFactor;
}
