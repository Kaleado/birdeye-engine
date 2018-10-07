#ifndef PUMPSHOTGUN_H
#define PUMPSHOTGUN_H

/**
  A shotgun that must be pumped after each shot with the right mouse button.
 */
template <typename BulletType>
class PumpShotgun : public Weapon {
protected:
  int _pumpDelay=20;
  int _pumpTimer;
  int _pelletDamage;
  int _pelletVelocity;
  int _numPellets=8;
  bool _isPumped=true;
  bool _isPumping=false;
public:
  void tick();
  PumpShotgun(int maxAmmo, int reloadTime, int pelletDamage, int pelletVelocity) : Weapon(maxAmmo, reloadTime) {
    _pelletDamage = pelletDamage;
    _pelletVelocity = pelletVelocity;
    _pumpTimer = _pumpDelay;
  };
};

template <typename BulletType>
void PumpShotgun<BulletType>::tick(){
  static int cooldown = 0;
  if(weaponState == WS_STOWED){
    if(_reloadTime > 0 && --_reloadTime == 0){
      _finishReload();
    }
  }

  //Fire the weapon.
  if(weaponState == WS_FIRING_PRIMARY && _isPumped){
    double deviation = 90;//90 degrees of deviation in the kick of the cursor and screen.
    auto facingDegrees = getVectorAngleDegrees(getVectorBetween(player->getWorldCenter(),
                                                                cursor->getWorldPosition()));
    auto dir = facingDegrees;// + (-0.5 + randDouble()) * deviation;
    //cursor->kick(dir, 60);
    camera.kick(dir, 90);
    for(int i = 0; i < _numPellets; ++i){
      //Essentially, we fire pellets to random spots 'near' the mouse (based on the spread).
      double spread = 0;
      auto target = cursor->getWorldPosition();
      target.x += randSignedDouble()*spread;
      target.y += randSignedDouble()*spread;
      auto pos = player->getWorldCenter();
      float opp = target.y - pos.y;
      float adj = target.x - pos.x;
      float hyp = std::sqrt(opp*opp + adj*adj);

      float vx = (adj/hyp)*_pelletVelocity + randSignedDouble()*_pelletVelocity/5;
      float vy = (opp/hyp)*_pelletVelocity + randSignedDouble()*_pelletVelocity/5;

      std::shared_ptr<Bullet> pellet = std::make_shared<BulletType>(true, pos, _pelletDamage, sf::Vector2f{vx,vy},
                                                                    static_cast<int>(FRAMERATE/5 + randDouble()*FRAMERATE/5));

      // auto unitVector = getUnitVectorBetween(pos, target);
      // unitVector.x *= _pelletVelocity + randDouble()*_pelletVelocity/10;
      // unitVector.y *= _pelletVelocity + randDouble()*_pelletVelocity/10;

      // pellet->setXVelocity(unitVector.x);
      // pellet->setYVelocity(unitVector.y);

      playfield->addThing(pellet);

    }
    _isPumped = false;
  }

  //Initiate pumping.
  if(weaponState == WS_FIRING_SECONDARY && !_isPumped){
    //Add a particle (the expelled casing).
    auto playerPos = player->getWorldPosition();
    std::shared_ptr<AmmoCasing> casing = std::make_shared<AmmoCasing>("res/shotgun-particle.png", playerPos, 2.0, 0, randDouble() * -2, 0.5, 0.9, FRAMERATE*3);
    playfield->addThing(casing);

    _isPumping = true;
    if(--_pumpTimer <= 0){
      _isPumping = false;
      _isPumped = true;
      weaponState = WS_IDLE;
    }
  }

}

#endif
