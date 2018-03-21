#include "Thing.hpp"

std::shared_ptr<Thing> player;

void Thing::setFacing(sf::Vector2f facing){
  _facing = facing;
}

void Thing::setRotation(double rotation){
  _rotation = rotation;
}

sf::Vector2f Thing::getWorldCenter(){
  return {_position.x + getBounds().width/2, _position.y + getBounds().height/2};
}

sf::Vector2f Thing::getScreenPosition(){
  return sf::Vector2f{_position.x -  camera.getPosition().x, _position.y -  camera.getPosition().y};
}

void Thing::setWorldPosition(sf::Vector2f newPos){
  _position = newPos;
  _sprite.setPosition(getScreenPosition());
}

int Thing::_load(){
  static int count = 0;
  if(!_isAnimating){
    //DEBUG
    // if(!_isLoaded){ std::cout << std::hex << this << " loading " << std::dec << ++count << "\n"; }
    //END DEBUG
    if(!_isLoaded && (!_texture.loadFromFile(_path))){
      _isLoaded = false;
      return 1;
    }
    //DEBUG
    // std::cout << "Success.\n";
    //END DEBUG
    _sprite.setTexture(_texture, true);
    _isLoaded = true;
  }
  return 0;
}

void Thing::draw(sf::RenderWindow& window){
  _position += _velocity;
  //Either show the current animation, or display the original sprite for the Thing.
  if(_isAnimating){
    //If animating, get the next frame.
    bool moreFramesToGo = _currentAnimation.getNextFrame(_sprite);
    if(!moreFramesToGo){
      _isAnimating = false;
      _isLoaded = false;
    }
  }
  else if(!_isLoaded){
    if(_load()){
      std::cerr << "Could not load image at path '" << _path << "'\n";
      return;
    }
  }
  _sprite.setRotation(_rotation);
  _sprite.setPosition(getScreenPosition());
  window.draw(_sprite);
}

void Thing::preventOverlapping(std::weak_ptr<Thing> otherThing, double strength){
  auto otherBounds = otherThing.lock()->getBounds();
  // if(std::floor(_velocity.x) == 0 && std::floor(_velocity.y) == 0){
    //We get the unit vector between the two centers of the enemies -
    //this will point away from the center of one of the enemies.
    auto otherPos = otherThing.lock()->getWorldCenter();
    auto thisCenter = getWorldCenter();
    double pushFactor = strength; //The strength of the 'push' out of an enemy there is.
    sf::Vector2f centerVector = { thisCenter.x - otherPos.x,
                                  thisCenter.y - otherPos.y};
    float length = std::sqrt(centerVector.x*centerVector.x + centerVector.y*centerVector.y);
    centerVector = {centerVector.x / length, centerVector.y / length};
    //We then add this vector to the enemy's current velocity.
    while(getBounds().intersects(otherBounds)){
      std::cout << _velocity.x << " " << _velocity.y << "\n";
      _position += centerVector;
      _sprite.setPosition(getScreenPosition());
    }
}


void Thing::tick(){
  //Do nothing.
}

void Thing::setColor(sf::Color c){
  _sprite.setColor(c);
}

void Thing::setXVelocity(float dx){
  _velocity.x = dx;
}

void Thing::setYVelocity(float dy){
  _velocity.y = dy;
}

void Thing::setVelocity(sf::Vector2f v){
  _velocity = v;
}

void Thing::cull(){
  _cullMe = true;
}

bool Thing::isCulled(){
  return _cullMe;
}

void Thing::handleInput(sf::Event event){
  //Don't handle any events.
}

void Thing::handleCollision(std::weak_ptr<Thing> other){
  //Don't handle any collisions.
}

sf::Vector2f Thing::getPosition(){
  return _position;
}
sf::FloatRect Thing::getBounds(){
  return _sprite.getGlobalBounds();
}

float Thing::getWorldRotation(){
  return _rotation;
}

void AmmoCasing::tick(){
  if(--_lifetime <= 0){
    cull();
    return;
  }
  auto floor = 30.0 + (randDouble()*2 - 1) * 16;
  _dz += _az;
  _z += _dz;
  if(_z >= floor){
    _sprite.rotate(randDouble() * 3.14159265358979 * 2);
    //Proportion of speed converted into horizontal motion.
    double degrees = randDouble()*150 + 15;
    double radians = degrees * 3.141592653589793238 / 180;
    _velocity.x = _dz * std::cos(radians) * _bounciness;
    _z -= _dz;
    //_dz *= (-1 * _bounciness);
    _dz *= std::sin(radians) * _bounciness * -1;
  }
}

void AmmoCasing::draw(sf::RenderWindow& window){
  _position += _velocity;
  //Either show the current animation, or display the original sprite for the Thing.
  if(_isAnimating){
    //If animating, get the next frame.
    bool moreFramesToGo = _currentAnimation.getNextFrame(_sprite);
    if(!moreFramesToGo){
      _isAnimating = false;
      _isLoaded = false;
    }
  }
  else if(!_isLoaded){
    if(_load()){
      std::cerr << "Could not load image at path '" << _path << "'\n";
      return;
    }
  }
  auto displayedPosition = sf::Vector2f{getScreenPosition().x, getScreenPosition().y + _z};
  _sprite.setPosition(displayedPosition);
  window.draw(_sprite);
}
