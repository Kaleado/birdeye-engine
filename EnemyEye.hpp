#ifndef ENEMY_EYE_H
#define ENEMY_EYE_H

#include "Enemy.hpp"

class EnemyEye : public Enemy {
public:
  EnemyEye(sf::Vector2f position, int maxHp, double speed) : Enemy("orb.png", position, maxHp, speed) { };  
protected:
  //!Executed every frame when the creature's state is ES_IDLE.
  virtual void _whenIdle();

  //!Executed every frame when the creature's state is ES_AGGRO.
  virtual void _whenAggro();
  
  //!Executed every frame when the creature's state is ES_ATTACKING.
  virtual void _whenAttacking();
  
};

#endif
