#ifndef SNIPERRIFLE_H
#define SNIPERRIFLE_H

/**
  A semi-automatic sniper rifle that can zoom in to long-distance targets.
 */
template <typename BulletType>
class SniperRifle : public Weapon {
protected:
  bool _hasReleasedLeftMouse=true;
  bool _isZooming=false;
  bool _beenFired=false;
  int _shotDamage;
  int _shotVelocity;
public:
  void pressPrimaryFire(sf::Vector2f target);
  void releasePrimaryFire(sf::Vector2f target);
  void pressSecondaryFire(sf::Vector2f target);
  void tick();
  SniperRifle(int maxAmmo, int reloadTime, int shotDamage, int shotVelocity) : Weapon(maxAmmo, reloadTime) {
    _shotDamage = shotDamage;
    _shotVelocity = shotVelocity;
  };
};

template <typename BulletType>
void SniperRifle<BulletType>::tick(){
  static int cooldown = 0;
  cooldown <= 0 ? cooldown : --cooldown;
  auto cursorPos = cursor->getWorldPosition();
  switch(weaponState){
  case WS_STOWED:
    if(_reloadTime > 0 && --_reloadTime == 0){
      _finishReload();
    }
    break;
  case WS_FIRING_PRIMARY:
    if(cooldown <= 0 && _hasReleasedLeftMouse){
      auto target = cursorPos;
      auto playerPos = player->getWorldPosition();
      auto velocityVector = getUnitVectorBetween(playerPos, target);
      velocityVector.x *= _shotVelocity;
      velocityVector.y *= _shotVelocity;
      std::shared_ptr<Bullet> bullet = std::make_shared<BulletType>(true, playerPos, _shotDamage,
                                                                    velocityVector, FRAMERATE*5);
      playfield->addThing(bullet);
      //Add a particle (the expelled casing).
      std::shared_ptr<AmmoCasing> casing = std::make_shared<AmmoCasing>("res/pistol-particle.png", playerPos, 0.5, 0, randDouble() * -5, 0.5, 0.9, FRAMERATE*3);
      playfield->addThing(casing);

      double deviation = 5;
      auto facingDegrees = getVectorAngleDegrees(getVectorBetween(player->getWorldPosition(),
                                                                  cursor->getWorldPosition()));
      auto dir = facingDegrees + 180 + (randDouble()*2 - 1) * deviation;
      //cursor->kick(dir, 80);
      camera.kick(dir, 80);

      cooldown = FRAMERATE/2;
      _hasReleasedLeftMouse = false;
    }
    break;
  case WS_FIRING_SECONDARY:
    _isZooming = true;
    break;
  case WS_IDLE:
    _isZooming = false;
    break;
  }

  if(_isZooming){
    auto focusPoint = getVectorBetween(player->getWorldPosition(), cursorPos);
    focusPoint.x /= 2;
    focusPoint.y /= 2;
    focusPoint.x += player->getWorldPosition().x;
    focusPoint.y += player->getWorldPosition().y;
    camera.setFocusPosition(focusPoint);
  }
  else{
    camera.setFocusPosition(player->getWorldPosition());
  }

}

template <typename BulletType>
void SniperRifle<BulletType>::pressPrimaryFire(sf::Vector2f target){
  Weapon::pressPrimaryFire(target);
}

template <typename BulletType>
void SniperRifle<BulletType>::releasePrimaryFire(sf::Vector2f target){
  Weapon::releasePrimaryFire(target);
  if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
    weaponState = WS_FIRING_SECONDARY;
  }
  _hasReleasedLeftMouse = true;
}

template <typename BulletType>
void SniperRifle<BulletType>::pressSecondaryFire(sf::Vector2f target){
  Weapon::pressSecondaryFire(target);
}

#endif
