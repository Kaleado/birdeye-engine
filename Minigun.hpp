#ifndef MINIGUN_H
#define MINIGUN_H

/**
  A minigun that slows the player whilst firing, but ramps up in
  firing speed to absurd rates.
 */
template <typename BulletType>
class Minigun : public Weapon {
protected:
  int _fireDelay;
  int _minFireDelay;
  int _maxFireDelay;
  int _fireDelayDecreaseRate;
  int _shotDamage;
  int _shotVelocity;
  double _speedMultiplier;
public:
  void tick();
  Minigun(int maxAmmo, int reloadTime, int maxFireDelay, int minFireDelay, int fireDelayDecreaseRate,
          int shotDamage, int shotVelocity, double speedMultiplier) : Weapon(maxAmmo, reloadTime) {
    _fireDelayDecreaseRate = fireDelayDecreaseRate;
    _maxFireDelay = maxFireDelay;
    _minFireDelay = minFireDelay;
    _fireDelay = maxFireDelay;
    _shotDamage = shotDamage;
    _shotVelocity = shotVelocity;
    _speedMultiplier = speedMultiplier;
  };
};

template <typename BulletType>
void Minigun<BulletType>::tick(){
  static int cooldown = 0;
  
  if(weaponState == WS_STOWED){
    _fireDelay = _maxFireDelay;
    if(_reloadTime > 0 && --_reloadTime == 0){
      _finishReload();
    }
  }

  if(weaponState == WS_FIRING_PRIMARY && --cooldown <= 0){
    _fireDelay = std::max(_fireDelay - _fireDelayDecreaseRate, _minFireDelay);
    //Add a particle (the expelled casing).
    auto playerPos = player->getPosition();
    std::shared_ptr<AmmoCasing> casing = std::make_shared<AmmoCasing>("pistol-particle.png", playerPos, 0.5, 0, randDouble() * -5, 0.5, 0.9, FRAMERATE*0.5);
    playfield->addThing(casing);
    
    //Fire the bullet.
    double deviation = 180;
    //auto dir = player->getWorldRotation() + 90 + (-0.5 + static_cast<double>(std::rand())/RAND_MAX) * deviation;
    auto dir = player->getWorldRotation() + 180 + (randDouble()*2 - 1) * deviation;
    //cursor->kick(dir, 6);
    camera.kick(dir, 9);
    auto target = cursor->getWorldPosition();
    auto pos = player->getPosition();
    //std::shared_ptr<Bullet> bullet = std::make_shared<FriendlyBullet>("bullet-final.png", pos, _shotDamage, sf::Vector2f{0,0}, 180);
    float opp = target.y - pos.y;
    float adj = target.x - pos.x;
    float hyp = std::sqrt(opp*opp + adj*adj);

    float vx = (adj/hyp)*_shotVelocity + randDouble()*3;
    float vy = (opp/hyp)*_shotVelocity + randDouble()*3;
    
    std::shared_ptr<Bullet> bullet = std::make_shared<BulletType>(pos, _shotDamage, sf::Vector2f{vx,vy}, 180);    
    playfield->addThing(bullet);
    cooldown = _fireDelay;
  }

  if(weaponState == WS_IDLE){
    _fireDelay = _maxFireDelay;
  }
  
}


#endif
