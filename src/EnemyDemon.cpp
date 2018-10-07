#include "EnemyDemon.hpp"

void EnemyDemon::_whenAttacking(){
  static bool hasAttacked = false;
  setXVelocity(0);
  setYVelocity(0);
  if(!hasAttacked){
    _currentAnimation = Animation({"anim0.png", "anim1.png", "anim2.png", "anim1.png", "anim0.png"}, false, 10);
    _isAnimating = true;
    auto attackAnimation = Animation({"atk0.png", "atk1.png", "atk2.png", "atk3.png", "atk4.png"}, false, 30);
    std::shared_ptr<Bullet> attack = std::make_shared<Bullet>(false, attackAnimation, _position, 20, sf::Vector2f(0,0));
    playfield->addThing(attack);
    hasAttacked = true;
  }
  if(_currentAnimation.hasFinished()){
    hasAttacked = false;
    enemyState = ES_AGGRO;
  }
}

void EnemyDemon::_whenAggro(){
  _facing = getUnitVectorBetween(_position, player->getWorldPosition());
  _setImageBasedOnFacing();
  double dist = _getDistanceFromPlayer();
  double attackRange = 30;
  double leapRange = 250;
  double leapSpeed = 14.0;

  if(!_canLeap){
    if(--_leapCooldown <= 0){
      _canLeap = true;
      _leapCooldown = FRAMERATE*1.5;
      _leapDelayTimer = FRAMERATE*0.75;
      _leapTimer = FRAMERATE*0.5;
    }
  }

  if(_leaping){
    if(--_leapTimer <= 0 || dist < attackRange){
      _leaping = false;
      _canLeap = false;
    }
    if(dist < attackRange){
      enemyState = ES_ATTACKING;
    }
    return;
  }

  auto target = player->getWorldPosition();
  auto unitVector = getUnitVectorBetween(_position, target);

  if(_initiateLeap){
    if(--_leapDelayTimer <= 0){
      _initiateLeap = false;
      _velocity = {static_cast<float>(unitVector.x * leapSpeed), static_cast<float>(unitVector.y * leapSpeed)};
      _leaping = true;
    }
  }
  else if((_canLeap && dist > leapRange) || (!_canLeap && dist > attackRange)){
    _velocity = {static_cast<float>(unitVector.x * _speed), static_cast<float>(unitVector.y * _speed)};
  }
  else if(_canLeap && dist < leapRange){
    _initiateLeap = true;
    _velocity = {0.0, 0.0};
  }
  else if(dist < attackRange){
    enemyState = ES_ATTACKING;
  }

}

void EnemyDemon::_whenIdle(){
  static int tick = FRAMERATE*7.5;
  static sf::Vector2f home = _position;
  static bool returnHome = false;
  static bool runOnce = false;

  if(!returnHome && !runOnce){
    _velocity = {static_cast<float>(randDouble() * 2 - 1), static_cast<float>(randDouble() * 2 - 1)};
    runOnce = true;
  }
  else if(returnHome && !runOnce){
    _velocity = getUnitVectorBetween(_position, home);
    runOnce = true;
  }

  if(--tick <= 0){
    returnHome = !returnHome;
    tick = FRAMERATE*7.5;
    runOnce = false;
  }

  double aggroThreshold = 650;
  if(_getDistanceFromPlayer() < aggroThreshold){
    enemyState = ES_AGGRO;
  }
}
