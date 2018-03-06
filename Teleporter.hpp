#ifndef TELEPORTER_H
#define TELEPORTER_H

#include "Render.hpp"
#include "EnvironmentThing.hpp"

/**
   This class represents a two-directional teleporter that teleports
   Things from one teleporter to the other, instantaneously.
 */
class Teleporter : public EnvironmentThing {
protected:
  //!Used to manage how frequently the teleporter can be used.
  int _cooldownMax=FRAMERATE/3;
  int _cooldownTimer;
  
  //!Whether the teleporter functions when walked on.
  bool _enabled=true;

  //!The teleporter linked to this teleporter.
  std::shared_ptr<Teleporter> _otherTeleporter = nullptr;

  //!Teleports the Thing that collides with the teleporter.
  void _whenCollidingWith(std::weak_ptr<Thing> other);
public:
  //!Decrements the cooldown timer.
  void tick();

  //!Sets the other teleporter for this teleporter. You MUST do this
  //!to get the teleporter to actually do something.
  void setOtherTeleporter(std::shared_ptr<Teleporter> otherTeleporter);

  Teleporter(Animation& anim, sf::Vector2f position) : EnvironmentThing(anim, position,
                                                                        true, true) { }
  Teleporter(std::string path, sf::Vector2f position) : EnvironmentThing(path, position,
                                                                         true, true) { }
  Teleporter() : EnvironmentThing() {}
};

#endif
