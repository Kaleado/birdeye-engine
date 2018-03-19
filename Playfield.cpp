#include "Playfield.hpp"
#include "EnemyDemon.hpp"
#include "EnemyEye.hpp"
#include "EnemyLegion.hpp"
#include "Teleporter.hpp"
#include "BreakableThing.hpp"

std::shared_ptr<Playfield> playfield;

Playfield::Playfield(std::string playfieldPath){
  std::ifstream fileStrm{playfieldPath};
  if(!fileStrm.is_open()){
    std::cerr << "Failed to open playfield file: " << playfieldPath << "\n";
    return;
  }
  //Read line-by-line.
  std::string line;
  while(std::getline(fileStrm, line)){
    std::cout << line << " ";
    std::istringstream lineStrm{line};
    std::string command;
    lineStrm >> command;
    std::cout << "(" << command << ")\n";

    //\\//\\//\\// COMMANDS //\\//\\//\\//

    //Specifying the background file.
    if(command == "Comment"){
      //Do nothing.
    }
    else if(command == "Background"){
      lineStrm >> _backgroundPath;
    }
    else if(command == "EnvironmentThing"){
      std::string thingPath;
      int x, y;
      bool shootThrough, walkThrough;
      lineStrm >> thingPath >> x >> y >> std::boolalpha >> shootThrough >> walkThrough;
      addThing(std::make_shared<EnvironmentThing>(thingPath, sf::Vector2f{x, y}, shootThrough, walkThrough));
    }
    else if(command == "BreakableThing"){
      std::string thingPath;
      int x, y;
      int hp;
      lineStrm >> thingPath >> x >> y >> hp;
      addThing(std::make_shared<BreakableThing>(thingPath, sf::Vector2f{x, y}, hp));
    }
    else if(command == "EnemyDemon"){
      int x, y, maxHp;
      double speed;
      lineStrm >> x >> y >> maxHp >> speed;
      addThing(std::make_shared<EnemyDemon>(sf::Vector2f{x, y}, maxHp, speed));
    }
    else if(command == "EnemyEye"){
      int x, y, maxHp;
      double speed;
      lineStrm >> x >> y >> maxHp >> speed;
      addThing(std::make_shared<EnemyEye>(sf::Vector2f{x, y}, maxHp, speed));
    }
    else if(command == "EnemyLegion"){
      int x, y, maxHp;
      double speed;
      lineStrm >> x >> y >> maxHp >> speed;
      std::array<std::shared_ptr<EnemyLegionSlave>, LEGION_SIZE> slaves;
      addThing(std::make_shared<EnemyLegion>(sf::Vector2f{x, y}, maxHp, speed, &slaves));
      for(auto it = (slaves).begin(); it != (slaves).end(); ++it){
        addThing(*it);
      }
    }
    else if(command == "Teleporter"){
      int x1, y1;
      std::string path1;

      int x2, y2;
      std::string path2;

      lineStrm >> x1 >> y1 >> path1 >> x2 >> y2 >> path2;
      auto tp1 = std::make_shared<Teleporter>(path1, sf::Vector2f{x1, y1});
      auto tp2 = std::make_shared<Teleporter>(path2, sf::Vector2f{x2, y2});
      tp1->setOtherTeleporter(tp2);
      tp2->setOtherTeleporter(tp1);
      addThing(tp1);
      addThing(tp2);
    }

  }
}

int Playfield::getBounds(){
  _sprite.getLocalBounds();
}

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
    if(/*isOnScreen(*t)*/true){
      results.push_back(t);
    }
  }
  return results;
}

void Playfield::tick(){
  //DEBUGGING
  // static int counter = 0;
  // if(++counter > FRAMERATE){
  //   counter = 0;
  //   int nSpawn = 10;
  //   for(int i = 0; i < nSpawn; ++i){
  //     auto xPos = (static_cast<double>(std::rand())/RAND_MAX) * 5000;
  //     auto yPos = (static_cast<double>(std::rand())/RAND_MAX) * 5000;
  //     addThing(newThing);
  //   }
  // }
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
    //nCulled += (t->isCulled() ? 1 : 0);
    if(t == nullptr){return true;}//There are sometimes nullptrs in the array. Not sure why.
    return t->isCulled();
  };
  _things.erase(std::remove_if(_things.begin(), _things.end(), cullPredicate), _things.end());
}

void Playfield::handleInput(sf::Event event){
  for(auto t = 0; t< _things.size(); t++){
    _things[t]->handleInput(event);
  }
}
