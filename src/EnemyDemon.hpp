#ifndef ENEMY_DEMON_H
#define ENEMY_DEMON_H

#include "Enemy.hpp"

/**
   Class representing a generic 'demon' enemy that claws at the player
   when they get close enough.
 */
class EnemyDemon : public Enemy {
public:
  EnemyDemon(sf::Vector2f position, int maxHp, double speed) : Enemy(
                                                                     std::array<std::string, FACING_MAX>{
                                                                     "enemy-up.png", "enemy-down.png",
                                                                     "enemy-left.png", "enemy-right.png",
                                                                     "enemy-upleft.png", "enemy-upright.png",
                                                                     "enemy-downleft.png", "enemy-downright.png"},
                                                                     position, maxHp, speed,
                                                                     sf::FloatRect{7.0, 31.0, 26.0, 14.0}) { };
  EnemyDemon(){ };

protected:
  int _leapDelayTimer = FRAMERATE*0.75;
  int _leapTimer = FRAMERATE*0.5;
  bool _leaping = false;
  bool _initiateLeap = false;
  int _leapCooldown = FRAMERATE*1.5;
  bool _canLeap = true;


  //!Does nothing.
  virtual void _whenIdle();

  //!Runs towards the player.
  virtual void _whenAggro();

  //!Claws at the player.
  virtual void _whenAttacking();
};

#endif
