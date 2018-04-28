#include "EnemyLegion.hpp"

EnemyLegion::EnemyLegion(sf::Vector2f position, int maxHp,
                         double speed, std::array<std::shared_ptr<EnemyLegionSlave>, LEGION_SIZE>* slv) : Enemy("orb.png", position, maxHp, speed){
  //Add some legion slaves.
  for(int i = 0; i < LEGION_SIZE; ++i){
    auto slave = std::make_shared<EnemyLegionSlave>(sf::Vector2f{_position.x + rand() % 50, _position.y + rand() % 50}, _maxHp, _speed);
    _slaves[i] = slave;
  }
  for(int i = 0; i < LEGION_SIZE; ++i){
    (*slv)[i] = _slaves[i];
    std::cout << _slaves[i] << "\n";
  }
}


void EnemyLegion::draw(sf::RenderWindow& window){
  return;
}

void EnemyLegion::cull(){
  for(auto it = _slaves.begin(); it != _slaves.end(); ++it){
    (*it)->cull();
  }
}

sf::FloatRect EnemyLegion::getBounds(){
  return {0.0, 0.0, 0.0, 0.0};
}

void EnemyLegion::damage(int amount){
  return;
}

void EnemyLegion::_whenIdle(){
  for(auto it = _slaves.begin(); it != _slaves.end(); ++it){
    if((*it)->enemyState == ES_AGGRO){
      enemyState = ES_AGGRO;
    }
  }
  return;
}

void EnemyLegion::_whenAggro(){
  //All slaves also become ES_AGGRO.
  for(auto it = _slaves.begin(); it != _slaves.end(); ++it){
    (*it)->enemyState = ES_AGGRO;
  }
}

int EnemyLegion::_getAverageHealth(){
  int sum = 0;
  for(auto it = _slaves.begin(); it != _slaves.end(); ++it){
    sum += (*it)->_hp;
  }
  return sum;
}

void EnemyLegion::_whenTick(){
  int fleeLength = FRAMERATE*2;
  int nextFleeDelay = FRAMERATE*5;
  //Get total health; if they are damaged, have them run away and regroup.
  if(enemyState != ES_FLEE && _getAverageHealth() < _maxHp / 2 && --_nextFlee <= 0){
    for(auto it = _slaves.begin(); it != _slaves.end(); ++it){
      (*it)->enemyState = ES_FLEE;
      _fleeCountdown = fleeLength;
      _nextFlee = nextFleeDelay;
    }
    enemyState = ES_FLEE;
  }

  if(enemyState == ES_FLEE && --_fleeCountdown <= 0){
    //No longer fleeing.
    for(auto it = _slaves.begin(); it != _slaves.end(); ++it){
      (*it)->enemyState = ES_FLEE;
    }
    enemyState = ES_AGGRO;
  }
}

void EnemyLegionSlave::_whenAttacking(){
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

void EnemyLegionSlave::_whenAggro(){
  _facing = getUnitVectorBetween(_position, player->getWorldPosition());
  _setImageBasedOnFacing();
  double dist = _getDistanceFromPlayer();
  double attackRange = 30;
  if(dist > attackRange){
    auto target = player->getWorldPosition();

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

void EnemyLegionSlave::_whenIdle(){
  double aggroThreshold = 350;
  if(_getDistanceFromPlayer() < aggroThreshold){
    enemyState = ES_AGGRO;
  }
}

void EnemyLegionSlave::_whenTick(){
  if(enemyState == ES_FLEE){
    auto target = player->getWorldPosition();

    auto unitVector = getUnitVectorBetween(_position, target);

    float vx = unitVector.x * _speed * -1;
    float vy = unitVector.y * _speed * -1;

    setXVelocity(vx);
    setYVelocity(vy);

  }
}
