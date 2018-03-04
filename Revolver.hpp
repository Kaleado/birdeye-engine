#ifndef REVOLVER_H
#define REVOLVER_H

/**
  A powerful revolver with a lengthy trigger pull.
 */
template <typename BulletType>
class Revolver : public Weapon {
protected:
  bool _isCocking = false;
  int _cockDelay=10;
  int _cockTimer;
  int _shotDamage;
  int _shotVelocity;
public:
  void tick();
  void releasePrimaryFire(sf::Vector2f target);
  Revolver(int maxAmmo, int reloadTime, int shotDamage, int shotVelocity) : Weapon(maxAmmo, reloadTime) {
    _shotDamage = shotDamage;
    _shotVelocity = shotVelocity;
    _cockTimer = _cockDelay;
  };
};

template <typename BulletType>
void Revolver<BulletType>::tick(){
  static int cooldown = 0;

  if(weaponState == WS_STOWED){
    if(_reloadTime > 0 && --_reloadTime == 0){
      _finishReload();
    }
  }

  if(weaponState == WS_FIRING_PRIMARY && --_cockTimer <= 0){
    //double deviation = -90;
    //cursor->kick(player->getRotation() + (-0.5 + static_cast<double>(std::rand())/RAND_MAX) * deviation, 15);
    //double deviation = 360;
    double deviation = 5;
    //auto dir = static_cast<double>(std::rand())/RAND_MAX * deviation;
    auto facingDegrees = getVectorAngleDegrees(getVectorBetween(player->getPosition(),
                                                                cursor->getWorldPosition()));    
    auto dir = facingDegrees + 180 + (randDouble()*2 - 1) * deviation;
    //cursor->kick(dir, 37.5);
    camera.kick(dir, 37.5);
    auto target = cursor->getWorldPosition();
    auto pos = player->getPosition();
    std::shared_ptr<Bullet> bullet = std::make_shared<FriendlyBullet>("bullet-final.png", pos, _shotDamage, sf::Vector2f{0,0}, 180);
    //bullet->setColor(sf::Color(0, 0, 255));
    float opp = target.y - pos.y;
    float adj = target.x - pos.x;
    float hyp = std::sqrt(opp*opp + adj*adj);

    float vx = (adj/hyp)*_shotVelocity;
    float vy = (opp/hyp)*_shotVelocity;

    bullet->setXVelocity(vx);
    bullet->setYVelocity(vy);
    
    playfield->addThing(bullet);
    _cockTimer = _cockDelay;
    weaponState = WS_IDLE;
  }
  
}


template <typename BulletType>
void Revolver<BulletType>::releasePrimaryFire(sf::Vector2f target){
  _cockTimer = _cockDelay;
  weaponState = WS_IDLE;
}

#endif
