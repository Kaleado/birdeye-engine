#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Playfield.hpp"
#include "Enemy.hpp"
#include "Cursor.hpp"
#include "Ui.hpp"
#include "Weapon.hpp"
#include "WeaponWidget.hpp"
#include "EnvironmentThing.hpp"

#include "ScriptedWeapon.hpp"
#include "ScriptedEnemy.hpp"

#include "EnemyDemon.hpp"
#include "EnemyEye.hpp"
#include "EnemyLegion.hpp"

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
    camera = Camera(sf::Vector2f{-100.0, -100.0});
    cursor = std::make_shared<Cursor>("res/cursor.png");
    player = std::make_shared<Player>("res/player-down.png", sf::Vector2f{0.0, 0.0}, 6.0, sf::FloatRect{7.0, 31.0, 26.0, 14.0});
    player->setSprintAbility(std::make_shared<Sprint>(1.333));
    playfield = std::make_shared<Playfield>("res/levels/other.plf");

    auto smg = std::make_shared<ScriptedWeapon>("res/scripts/weapon_smg.lua");
    smg->fillWithMods();
    auto revolver = std::make_shared<ScriptedWeapon>("res/scripts/weapon_revolver.lua");
    revolver->fillWithMods();
    auto shotgun = std::make_shared<ScriptedWeapon>("res/scripts/weapon_pump_shotgun.lua");
    shotgun->fillWithMods();
    auto rifle = std::make_shared<ScriptedWeapon>("res/scripts/weapon_sniper_rifle.lua");
    rifle->fillWithMods();
    auto minigun = std::make_shared<ScriptedWeapon>("res/scripts/weapon_minigun.lua");
    minigun->fillWithMods();


    weaponIcon[0] = WeaponWidget{smg,
                                 {static_cast<float>(window.getSize().x/2 + SCREEN_GUTTER/2 - WEAPON_ICON_SPACING*2 - WEAPON_ICON_WIDTH*2),
                                  static_cast<float>(window.getSize().y - WEAPON_ICON_HEIGHT - SCREEN_GUTTER)}};
    weaponIcon[1] = WeaponWidget{revolver,
                                 {static_cast<float>(window.getSize().x/2 + SCREEN_GUTTER/2 - WEAPON_ICON_SPACING - WEAPON_ICON_WIDTH),
                                  static_cast<float>(window.getSize().y - WEAPON_ICON_HEIGHT - SCREEN_GUTTER)}};
    weaponIcon[2] = WeaponWidget{shotgun,
                                 {static_cast<float>(window.getSize().x/2 + SCREEN_GUTTER/2),
                                  static_cast<float>(window.getSize().y - WEAPON_ICON_HEIGHT - SCREEN_GUTTER)}};
    weaponIcon[3] = WeaponWidget{rifle,
                                 {static_cast<float>(window.getSize().x/2 + SCREEN_GUTTER/2 + WEAPON_ICON_SPACING + WEAPON_ICON_WIDTH),
                                  static_cast<float>(window.getSize().y - WEAPON_ICON_HEIGHT - SCREEN_GUTTER)}};
    weaponIcon[4] = WeaponWidget{minigun,
                                 {static_cast<float>(window.getSize().x/2 + SCREEN_GUTTER/2 + WEAPON_ICON_SPACING*2 + WEAPON_ICON_WIDTH*2),
                                  static_cast<float>(window.getSize().y - WEAPON_ICON_HEIGHT - SCREEN_GUTTER)}};

    player->giveWeapon(smg);
    player->giveWeapon(revolver);
    player->giveWeapon(shotgun);
    player->giveWeapon(rifle);
    player->giveWeapon(minigun);

    playfield->addThing(player);

//    auto demon = std::make_shared<ScriptedEnemy>(std::array<std::string, FACING_MAX>{
//                                                         "res/enemy-up.png", "res/enemy-down.png",
//                                                         "res/enemy-left.png", "res/enemy-right.png",
//                                                         "res/enemy-upleft.png", "res/enemy-upright.png",
//                                                         "res/enemy-downleft.png", "res/enemy-downright.png"},
//                                                 sf::Vector2f{500.0f, 500.0f}, 1000,
//                                                 sf::FloatRect{7.0, 7.0, 26.0, 32.0}, "res/scripts/enemy_demon.lua");
//    playfield->addThing(demon);
//    std::cout << demon.get();

    healthBar = HorizontalBar<int>{[](){return player->getCurrentHp();}, [](){return player->stats.maxHp;}, {10, 10}, sf::Color::Red, 100, 15};
}

//!This function draws everything on the screen and calls tick() for everything that needs to handle events every frame.
void frameTick(){
    window.clear(sf::Color::Black);
    camera.setFocusPosition(player->getWorldPosition());
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
    if(newPlayfield != nullptr){
        playfield = newPlayfield;
        newPlayfield = nullptr;
    }
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

