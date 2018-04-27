#include "Teleporter.hpp"

void Teleporter::_whenCollidingWith(std::weak_ptr<Thing> other){
  if(_otherTeleporter == nullptr || _enabled == false){
    return;
  }
  auto otherPtr = other.lock();
  otherPtr->setWorldPosition(_otherTeleporter->getWorldPosition());
  _otherTeleporter->_cooldownTimer = _otherTeleporter->_cooldownMax;
  _otherTeleporter->_enabled = false;
}

void Teleporter::setOtherTeleporter(std::shared_ptr<Teleporter> otherTeleporter){
  _otherTeleporter = otherTeleporter;
  _enabled = true;
}

void Teleporter::tick(){
  if(_cooldownTimer > 0){
    if(--_cooldownTimer == 0){
      _enabled = true;
    }
  }
}
