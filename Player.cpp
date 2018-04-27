#include "Player.hpp"
#include "Weapon.hpp"


void Player::die(){
  std::cout << "You died.";
  cull();
}

void Player::damage(int amount){
  if(_invulnTime > 0){
    return;
  }
  _invulnTime = FRAMERATE;
  _curHp -= amount;
  if(_curHp <= 0){
    //Handle game over, etc. here.
    die();
  }
}

int Player::getCurrentHp(){
  return _curHp;
}

void Player::_changeImageBasedOnFacing(){
  std::string newPath;
  float facingDegrees = getVectorAngleDegrees(_facing);
  //Change sprite based on the eight directions.
  if(-22.5 < facingDegrees && facingDegrees < 22.5){
    //Right
    newPath = "player-right.png";
  }
  else if(22.5 < facingDegrees && facingDegrees < 67.5){
    //Down-right
    newPath = "player-downright.png";
  }
  else if(67.5 < facingDegrees && facingDegrees < 112.5){
    //Down
    newPath = "player-down.png";
  }
  else if(112.5 < facingDegrees && facingDegrees < 157.5){
    //Down-left
    newPath = "player-downleft.png";
  }
  else if(-67.5 < facingDegrees && facingDegrees < -22.5){
    //Up-right
    newPath = "player-upright.png";
  }
  else if(-112.5 < facingDegrees && facingDegrees < -67.5){
    //Up
    newPath = "player-up.png";
  }
  else if(-157.5 < facingDegrees && facingDegrees < -112.5){
    //Up-left
    newPath = "player-upleft.png";
  }
  else {
    //Left
    newPath = "player-left.png";
  }
  if(_path != newPath){
    _path = newPath;
    _isLoaded = false;
  }  
}

void Player::handleInput(sf::Event event){
  double velocity = _baseSpeed * stats.speedMultiplier;

  if(event.type == sf::Event::MouseMoved){
    _sprite.setOrigin(16, 16);
    // float rads = std::atan2(localPosition.y - _position.y, localPosition.x - _position.x);
    // float degrees = rads*180/(3.141592653589793238);
    // _rotation = degrees;
    _facing = getUnitVectorBetween(_position, cursor->getWorldPosition());
    _changeImageBasedOnFacing();
  }

  if(event.type == sf::Event::KeyPressed){
    if(event.key.code == sf::Keyboard::E && _primaryAbility){
      _primaryAbility->press();
    }
    if(event.key.code == sf::Keyboard::Space && _movementAbility){
      _movementAbility->press();
    }
    if(event.key.code == sf::Keyboard::LShift && _sprintAbility){
      _sprintAbility->press();
    }
  }
  if(event.type == sf::Event::KeyReleased){
    //Switch to previous weapon.
    if(event.key.code == sf::Keyboard::Q){
      previousWeapon();
    }
    if(event.key.code == sf::Keyboard::E){
      nextWeapon();
    }
    if(event.key.code == sf::Keyboard::R && _primaryAbility){
      _primaryAbility->release();
    }
    if(event.key.code == sf::Keyboard::Space && _movementAbility){
      _movementAbility->release();
    }
    if(event.key.code == sf::Keyboard::LShift && _sprintAbility){
      _sprintAbility->release();
    }
  }

  if(event.type == sf::Event::KeyReleased){
    if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S){
      this->setYVelocity(0);
    }

    if(event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D){
      this->setXVelocity(0);
    }

  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
    this->setYVelocity(-velocity);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
    this->setXVelocity(-velocity);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
    this->setYVelocity(velocity);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
    this->setXVelocity(velocity);
  }

  if(event.type == sf::Event::MouseButtonPressed){
    int mx = event.mouseButton.x;
    int my = event.mouseButton.y;
    if(event.mouseButton.button == sf::Mouse::Left){
      //Left clicked - primary fire.
      _curWeapon->pressPrimaryFire(sf::Vector2f(mx, my));
    }
    if(event.mouseButton.button == sf::Mouse::Right){
      //Right clicked - secondary fire.
      _curWeapon->pressSecondaryFire(sf::Vector2f(mx, my));
    }
  }

  if(event.type == sf::Event::MouseButtonReleased){
    int mx = event.mouseButton.x;
    int my = event.mouseButton.y;
    if(event.mouseButton.button == sf::Mouse::Left){
      //Left clicked - primary fire.
      _curWeapon->releasePrimaryFire(sf::Vector2f(mx, my));
    }
    if(event.mouseButton.button == sf::Mouse::Right){
      //Right clicked - secondary fire.
      _curWeapon->releaseSecondaryFire(sf::Vector2f(mx, my));
    }
  }

}

void Player::giveWeapon(std::shared_ptr<Weapon> weapon){
  for(int i = 0; i < NUM_WEAPONS; ++i){
    if(_weapons[i] == nullptr){
      _weapons[i] = weapon;
      _curWeapon = weapon;
      _curWeaponIndex = i;
      return;
    }
  }
}

void Player::tick(){
  if(_invulnTime > 0){
    --_invulnTime;
  }
  double drag = 0.5;
  _velocity = {_velocity.x*drag, _velocity.y*drag };
  _curWeapon->tick();
  if(_primaryAbility){_primaryAbility->tick();}
  if(_movementAbility){_movementAbility->tick();}
  if(_sprintAbility){_sprintAbility->tick();}
}

void Player::setPrimaryAbility(std::shared_ptr<Ability> abl){
  _primaryAbility = abl;
}

void Player::setMovementAbility(std::shared_ptr<Ability> abl){
  _movementAbility = abl;
}

void Player::setSprintAbility(std::shared_ptr<Ability> abl){
  _sprintAbility = abl;
}

void Player::switchToWeapon(std::shared_ptr<Weapon> newWeapon){
  if(_curWeapon){
    _curWeapon->weaponState = WS_STOWED;
    _curWeapon->onStow();
  }
  _curWeapon = newWeapon;
  if(_curWeapon){
    _curWeapon->weaponState = WS_IDLE;
    _curWeapon->onUnstow();
  }
}

void Player::nextWeapon(){
  _curWeaponIndex = ++_curWeaponIndex % NUM_WEAPONS;
  while(_weapons[_curWeaponIndex] == nullptr){
    _curWeaponIndex = ++_curWeaponIndex % NUM_WEAPONS;
  }
  switchToWeapon(_weapons[_curWeaponIndex]);
}

void Player::previousWeapon(){
  _curWeaponIndex = (--_curWeaponIndex < 0 ? NUM_WEAPONS - 1 : _curWeaponIndex) % NUM_WEAPONS;
  while(_weapons[_curWeaponIndex] == nullptr){
    _curWeaponIndex = (--_curWeaponIndex < 0 ? NUM_WEAPONS - 1 : _curWeaponIndex) % NUM_WEAPONS;
  }
  switchToWeapon(_weapons[_curWeaponIndex]);
}

//Called by WeaponWidget when dragging a weapon off the widget.
void Player::removeWeapon(int weaponIndex){
  std::shared_ptr<Weapon>& removedWeapon = _weapons[weaponIndex];
  if(removedWeapon != nullptr && removedWeapon->weaponState != WS_STOWED){
    _unequipCurrentWeapon();
  }
  _weapons[weaponIndex] = nullptr;
}

//Called by WeaponWidget when dragging a weapon into an empty space.
bool Player::insertWeapon(int weaponIndex, std::shared_ptr<Weapon> weapon){
  if(_weapons[weaponIndex] != nullptr){
    return false;
  }
  else {
    _weapons[weaponIndex] = weapon;
    return true;
  }
}

void Player::_unequipCurrentWeapon(){
  _curWeapon->onUnequip();
  _curWeapon = nullptr;
  _curWeaponIndex = -1;
}
