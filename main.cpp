#include <memory>
#include <vector>
#include <thread>
#include <SFML/Graphics.hpp>
#include "Render.hpp"
#include "Thing.hpp"
#include "Player.hpp"
#include "Playfield.hpp"
#include "Enemy.hpp"
#include "Cursor.hpp"
#include "Ui.hpp"
#include "Weapon.hpp"
#include "WeaponWidget.hpp"
#include "EnvironmentThing.hpp"

#include "Smg.hpp"
#include "Revolver.hpp"
#include "PumpShotgun.hpp"
#include "SniperRifle.hpp"
#include "Minigun.hpp"
 
#include "EnemyDemon.hpp"

HorizontalBar<int> healthBar;
std::array<WeaponWidget, NUM_WEAPONS> weaponIcon;

//!Root input handling function - all other input handling occurs within this function.
void handleInput(sf::Event event){
  playfield->handleInput(event);
  cursor->handleInput(event);
  for(int i = 0; i < NUM_WEAPONS; ++i){
    weaponIcon[i].handleInput(event);
  }
  if(event.type == sf::Event::Closed){
    window.close();
  }
}

//!This function initialises all game-logic related state.
void initialiseGameState(){
  camera = Camera(sf::Vector2f{-100, -100});
  cursor = std::make_shared<Cursor>("cursor.png");
  playfield = std::make_shared<Playfield>("level.plf");
  player = std::make_shared<Player>("player-down.png", sf::Vector2f{0, 0}, 8.0);
  player->setSprintAbility(std::make_shared<Sprint>(1.333));

  auto smg = std::make_shared<Smg<Rocket>>(1, 1, 5, 40, 20);
  smg->fillWithMods();
  auto revolver = std::make_shared<Revolver<Rocket>>(1, 1, 90, 30);
  revolver->fillWithMods();
  auto shotgun = std::make_shared<PumpShotgun<Rocket>>(1, 1, 40, 30);
  shotgun->fillWithMods();
  auto rifle = std::make_shared<SniperRifle<Rocket>>(1, 1, 150, 30);
  rifle->fillWithMods();
  auto minigun = std::make_shared<Minigun<Rocket>>(1, 1, 30, 2, 2, 40, 20, 0.5);
  minigun->fillWithMods();

  weaponIcon[0] = WeaponWidget{smg,
                               {window.getSize().x/2 + SCREEN_GUTTER/2 - WEAPON_ICON_SPACING*2 - WEAPON_ICON_WIDTH*2,
                                window.getSize().y - WEAPON_ICON_HEIGHT - SCREEN_GUTTER}};
  weaponIcon[1] = WeaponWidget{revolver,
                               {window.getSize().x/2 + SCREEN_GUTTER/2 - WEAPON_ICON_SPACING - WEAPON_ICON_WIDTH,
                                window.getSize().y - WEAPON_ICON_HEIGHT - SCREEN_GUTTER}};
  weaponIcon[2] = WeaponWidget{shotgun,
                               {window.getSize().x/2 + SCREEN_GUTTER/2,
                                window.getSize().y - WEAPON_ICON_HEIGHT - SCREEN_GUTTER}};
  weaponIcon[3] = WeaponWidget{rifle,
                               {window.getSize().x/2 + SCREEN_GUTTER/2 + WEAPON_ICON_SPACING + WEAPON_ICON_WIDTH,
                                window.getSize().y - WEAPON_ICON_HEIGHT - SCREEN_GUTTER}};
  weaponIcon[4] = WeaponWidget{minigun,
                               {window.getSize().x/2 + SCREEN_GUTTER/2 + WEAPON_ICON_SPACING*2 + WEAPON_ICON_WIDTH*2,
                                window.getSize().y - WEAPON_ICON_HEIGHT - SCREEN_GUTTER}};
  player->giveWeapon(smg);
  player->giveWeapon(revolver);
  player->giveWeapon(shotgun);
  player->giveWeapon(rifle);
  player->giveWeapon(minigun);

  playfield->addThing(player);
  healthBar = HorizontalBar<int>{[&player](){return player->getCurrentHp();}, [&player](){return player->stats.maxHp;}, {10, 10}, sf::Color::Red, 100, 15};
}
 
//!This function draws everything on the screen and calls tick() for everything that needs to handle events every frame.
void frameTick(){
  window.clear(sf::Color::Black);
  camera.setFocusPosition(player->getPosition());
  playfield->tick();
  playfield->draw(window);
  healthBar.draw(window);
  for(int i = 0; i < NUM_WEAPONS; ++i){
    weaponIcon[i].draw(window);
    cursor->draw(window);
    cursor->tick();
  }
  cursor->draw(window);
  cursor->tick();
  camera.tick();
  window.setActive(true);
  window.display();
}
 
int main(){
  window.setFramerateLimit(FRAMERATE);
  //We're using a soft cursor at the moment, but the UI would be a bit
  //more responsive if we used a hardware-provided cursor.
  window.setMouseCursorVisible(false);
  
  initialiseGameState();
  while(window.isOpen()){
    sf::Event event;
    while(window.pollEvent(event)){
      handleInput(event);
    }
    //Draw everything on the screen.
    frameTick();
  }
  return 0;
}
 
 
 
 
 
 
 
