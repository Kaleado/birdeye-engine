#ifndef SMG_H
#define SMG_H

#include "Weapon.hpp"

/*
  A fast-firing, fully-automatic SMG with little recoil.
 */
template <typename BulletType>
class Smg : public Weapon {
protected:
  int _fireDelay;
  int _shotDamage;
  int _shotVelocity;
public:
  void tick();
  Smg(int maxAmmo, int reloadTime, int fireDelay, int shotDamage, int shotVelocity) : Weapon(maxAmmo, reloadTime) {
    _fireDelay = fireDelay;
    _shotDamage = shotDamage;
    _shotVelocity = shotVelocity;
  };
};

template <typename BulletType>
void Smg<BulletType>::tick(){
  static int cooldown = 0;
  if(weaponState == WS_STOWED){
    if(_reloadTime > 0 && --_reloadTime == 0){
      _finishReload();
    }
  }

  if(weaponState == WS_FIRING_PRIMARY && --cooldown <= 0){
    //Add a particle (the expelled casing).
    auto playerPos = player->getPosition();
    std::shared_ptr<AmmoCasing> casing = std::make_shared<AmmoCasing>("pistol-particle.png", playerPos, 0.5, 0, randDouble() * -5, 0.5, 0.9, FRAMERATE*3);
    playfield->addThing(casing);
    
    //Fire the bullet.
    double deviation = 180;
    auto dir = player->getWorldRotation() + 90 + (-0.5 + static_cast<double>(std::rand())/RAND_MAX) * deviation;
    cursor->kick(dir, 6);
    camera.kick(dir, 9);
    auto target = cursor->getWorldPosition();
    auto pos = player->getPosition();
    //std::shared_ptr<Bullet> bullet = std::make_shared<FriendlyBullet>("bullet-final.png", pos, _shotDamage, sf::Vector2f{0,0}, 180);
    float opp = target.y - pos.y;
    float adj = target.x - pos.x;
    float hyp = std::sqrt(opp*opp + adj*adj);

    float vx = (adj/hyp)*_shotVelocity;
    float vy = (opp/hyp)*_shotVelocity;

    std::shared_ptr<Bullet> bullet = std::make_shared<BulletType>(pos, _shotDamage, sf::Vector2f{vx,vy}, 180);
    
    playfield->addThing(bullet);
    cooldown = _fireDelay;
  }
}

#endif
