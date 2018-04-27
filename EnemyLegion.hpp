#ifndef ENEMY_LEGION_H
#define ENEMY_LEGION_H

#include <memory>
#include "Enemy.hpp"

#define LEGION_SIZE 35

class EnemyLegionSlave;

/**
   Composite pattern class, treating the horde of slaves as individual enemies.
 */
class EnemyLegion : public Enemy, public std::enable_shared_from_this<EnemyLegion> {
  friend EnemyLegionSlave;
public:
  //!Draws nothing - this is just a logical entity.
  void draw(sf::RenderWindow& window);

  //!Culls all slaves as well.
  void cull();

  //!Gets a rectangle of size 0 because this doesn't actually collide with anything.
  sf::FloatRect getBounds();

  //!Does nothing because again, this is only a logical entity.
  void damage(int amount);

  EnemyLegion(sf::Vector2f position, int maxHp, double speed, std::array<std::shared_ptr<EnemyLegionSlave>, LEGION_SIZE>* slv);
protected:
  //!Returns the average HP for all slaves.
  int _getAverageHealth();

  //!Countdown for when enemies should stop fleeing.
  int _fleeCountdown;

  //!Countdown for when the enemy can flee again.
  int _nextFlee=0;

  //!Ensures that the enemies are only set to aggro once.

  //!Holds all the slaves that are in the enemies array.
  std::array<std::shared_ptr<EnemyLegionSlave>, LEGION_SIZE> _slaves;

  //!Executed every frame when the creature's state is ES_IDLE.
  //!This should set all the slaves to be ES_IDLE.
  virtual void _whenIdle();

  //!Executed every frame when the creature's state is ES_AGGRO.
  //!This should set all the slaves to be ES_AGGRO.
  virtual void _whenAggro();

  //!Executed every tick the creature is alive for.
  //!Checks the status of our slaves.
  virtual void _whenTick();

  //No attacking function - individual enemies can handle that.

};

/**
   Individual slaves.
 */
class EnemyLegionSlave : public Enemy {
  friend EnemyLegion;
public:
  EnemyLegionSlave(sf::Vector2f position, int maxHp, double speed) : Enemy("legion-slave.png", position, maxHp,
                                                                           speed,
                                                                           sf::FloatRect{0.0, 18.0, 32.0, 14.0}) {
  };

protected:
  std::weak_ptr<EnemyLegion> _parent;
  int _attackCooldown=0;

  //!Executed every frame when the creature's state is ES_IDLE.
  virtual void _whenIdle();

  //!Executed every frame when the creature's state is ES_AGGRO.
  virtual void _whenAggro();

  //!Executed every frame when the creature's state is ES_ATTACKING.
  virtual void _whenAttacking();

  //!Executed every frame, unconditionally.
  virtual void _whenTick();
};

#endif
