#include "EnemyDemon.hpp"

void EnemyDemon::_whenAttacking(){
  static bool hasAttacked = false;
  setXVelocity(0);
  setYVelocity(0);    
  if(!hasAttacked){
    _currentAnimation = Animation({"anim0.png", "anim1.png", "anim2.png", "anim1.png", "anim0.png"}, false, 10);
    _isAnimating = true;
    auto attackAnimation = Animation({"atk0.png", "atk1.png", "atk2.png", "atk3.png", "atk4.png"}, false, 30);
    std::shared_ptr<Bullet> attack = std::make_shared<HostileBullet>(attackAnimation, _position, 20, sf::Vector2f(0,0));
    playfield->addThing(attack);
    hasAttacked = true;
  }
  if(_currentAnimation.hasFinished()){
    hasAttacked = false;
    enemyState = ES_AGGRO;
  }
}

void EnemyDemon::_whenAggro(){
  _facing = getUnitVectorBetween(_position, player->getPosition());
  _setImageBasedOnFacing();
  double dist = _getDistanceFromPlayer();
  double attackRange = 30;  
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

void EnemyDemon::_whenIdle(){
  double aggroThreshold = 350;  
  if(_getDistanceFromPlayer() < aggroThreshold){
    enemyState = ES_AGGRO;
  }  
}
