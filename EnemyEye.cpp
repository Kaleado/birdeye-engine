#include "EnemyEye.hpp"

void EnemyEye::_whenAttacking(){
  static bool hasAttacked = false;
  setXVelocity(0);
  setYVelocity(0);
  if(!hasAttacked){
    _currentAnimation = Animation({"orb-attacking.png", "orb.png", "orb-attacking.png", "orb.png", "orb-attacking.png"}, false, 10);
    _isAnimating = true;
    auto attackVec = getUnitVectorBetween(getPosition(), player->getPosition());
    double bulletSpeed = 15.0;
    attackVec.x *= bulletSpeed;
    attackVec.y *= bulletSpeed;
    std::shared_ptr<Bullet> attack = std::make_shared<Bullet>(false, "laser-crest.png", _position, 20, attackVec);
    playfield->addThing(attack);
    hasAttacked = true;
  }
  else if(--_attackCooldown <= 0){
    hasAttacked = false;
    enemyState = ES_AGGRO;
    _attackCooldown = FRAMERATE/3;
  }
}

void EnemyEye::_whenAggro(){
  _facing = getUnitVectorBetween(_position, player->getPosition());
  _setImageBasedOnFacing();
  double dist = _getDistanceFromPlayer();
  double attackRange = 500;
  if(dist > attackRange){
    auto target = player->getPosition();

    auto unitVector = getUnitVectorBetween(_position, target);

    float vx = unitVector.x * _speed;
    float vy = unitVector.y * _speed;

    setXVelocity(vx);
    setYVelocity(vy);
  }
  else {
    enemyState = ES_ATTACKING;
  }

}

void EnemyEye::_whenIdle(){
  double aggroThreshold = 350;
  if(_getDistanceFromPlayer() < aggroThreshold){
    enemyState = ES_AGGRO;
  }
}
