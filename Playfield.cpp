#include "Playfield.hpp"

std::shared_ptr<Playfield> playfield;

void Playfield::addThing(std::shared_ptr<Thing> thing){
  _things.push_back(thing);
}

void Playfield::_drawBackground(sf::RenderWindow& window){
  _backgroundSprite.setPosition({-camera.getPosition().x, -camera.getPosition().y});
  window.draw(_backgroundSprite);
}

int Playfield::_loadBackground(){
  if(!_backgroundTexture.loadFromFile(_backgroundPath)){
    _isLoaded = false;
    return 1;
  }
  _backgroundSprite.setTexture(_backgroundTexture, true);
  _isLoaded = true;    
  return 0;
}

void Playfield::draw(sf::RenderWindow& window){
  if(!_isLoaded){
    _loadBackground();
  }
  _drawBackground(window);
  for(auto t : _things){
    t->draw(window);
  }  
}

std::vector<std::shared_ptr<Thing>> Playfield::_getPossiblyCollidingThings(){
  std::vector<std::shared_ptr<Thing>> results;
  for(auto t : _things){
    if(isOnScreen(*t)){
      results.push_back(t);
    }
  }
  return results;
}

void Playfield::tick(){
  //DEBUGGING
  static int counter = 0;
  if(++counter > FRAMERATE){
    counter = 0;
    int nSpawn = 10;
    for(int i = 0; i < nSpawn; ++i){
      auto xPos = (static_cast<double>(std::rand())/RAND_MAX) * 5000;
      auto yPos = (static_cast<double>(std::rand())/RAND_MAX) * 5000;
      std::shared_ptr<Enemy> newThing = std::make_shared<Enemy>(
                                                                std::array<std::string, FACING_MAX>{
                                                                  "enemy-up.png", "enemy-down.png",
                                                                  "enemy-left.png", "enemy-right.png",
                                                                  "enemy-upleft.png", "enemy-upright.png",
                                                                  "enemy-downleft.png", "enemy-downright.png"},
                                                                sf::Vector2f{xPos, yPos}, 150, 5.0);
      addThing(newThing);
    }
  }
  //END DEBUGGING
  
  _cullThings();    
  //Broad phase collision detection.
  std::vector<std::shared_ptr<Thing>> possibleCollisions = _getPossiblyCollidingThings();
  for(auto t = 0; t < possibleCollisions.size(); t++){
    possibleCollisions[t]->tick();
  }
  //Narrow phase collision detection.
  for(auto t = 0; t < possibleCollisions.size(); t++){
    auto first = possibleCollisions[t];
    for(auto u = 0; u < possibleCollisions.size(); u++){
      auto second = possibleCollisions[u];
      if(first == second){continue;}
      bool isColliding = first->getBounds().intersects(second->getBounds());
      if(isColliding){
        first->handleCollision(second);
      }
    }
    bool playerColliding = player->getBounds().intersects(first->getBounds());
    if(playerColliding){
      player->handleCollision(first);
      first->handleCollision(player);
    }    
  }  
}


void Playfield::_cullThings(){
  //Remove Things that need to be culled.
  int nCulled = 0;
  auto cullPredicate = [&nCulled](std::shared_ptr<Thing> t){
    nCulled += (t->isCulled() ? 1 : 0);
    return t->isCulled();
  };
  _things.erase(std::remove_if(_things.begin(), _things.end(), cullPredicate), _things.end());
}

void Playfield::handleInput(sf::Event event){
  for(auto t = 0; t< _things.size(); t++){
    _things[t]->handleInput(event);
  }
}
