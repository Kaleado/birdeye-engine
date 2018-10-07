#include "WeaponWidget.hpp"

void ModWidget::_onLeftClickRelease(){
  _acquireMod();
}

void ModWidget::_acquireMod(){
  std::cout << "Acquiring\n\n\n\n";
  _mod->acquire();
}


void WeaponWidget::setWeapon(std::shared_ptr<Weapon> weapon){
  _weapon = weapon;
  _rebuildModWidgets();
}

void WeaponWidget::handleInput(sf::Event event){
  Widget::handleInput(event);
  //Hide the mod tree widget.
  if(_isShowingModTree && !isMouseOver() && !_modTreeWidget.isMouseOver()){
    _hideModTree();
  }
  else if(_isShowingModTree){
    for(auto w : _modWidgets){
      w->handleInput(event);
    }
    _modTreeWidget.handleInput(event);
  }
}

void WeaponWidget::_rebuildModWidgets(){
  //Rebuild the list of mod widgets.
  _modWidgets = {};
  //Common
  auto commonMods = _weapon->getModsOfQuality(MQ_COMMON);
  int i = 0;
  for(std::shared_ptr<WeaponMod> m : commonMods){
    //calculate where the icon should appear.
    float xPos = _position.x - WEAPON_ICON_WIDTH/2 + MOD_MENU_MOD_WIDGET_WIDTH*i + MOD_MENU_ICON_SPACING * (i+1);
    float yPos = _position.y - WEAPON_ICON_HEIGHT/2 - MOD_MENU_HEIGHT + MOD_MENU_COMMON_RELATIVE_Y_POS;
    auto newWidget = std::make_shared<ModWidget>("res/mod-icon.png", sf::Vector2f{xPos, yPos}, m, _weapon);
    _modWidgets.push_back(newWidget);
    ++i;
  }

}

void WeaponWidget::draw(sf::RenderWindow& window){
  //Show the modtree if we need to.
  if(_isShowingModTree){
    _rebuildModWidgets();
    std::cout << "Showing";
    _modTreeWidget.draw(window);
    for(auto w : _modWidgets){
      w->draw(window);
    }
  }

  //Also show the stowed/unstowed image.
  _sprite.setOrigin({WEAPON_ICON_WIDTH/2, WEAPON_ICON_HEIGHT/2});//Center of the image.
  if((!_weapon || _weapon->weaponState == WS_STOWED) && _showStowedImage == false){
    //Show the stowed image.
    _showStowedImage = true;
    _path = "res/weapon-image.png";//Replace with the weapon's actual image later.
    _isLoaded = false;
  }
  else if(_weapon && _weapon->weaponState != WS_STOWED && _showStowedImage == true) {
    //Show the unstowed image.
    _showStowedImage = false;
    _path = "res/weapon-image-selected.png";//Replace with the weapon's actual image later.
    _isLoaded = false;
  }
  Widget::draw(window);
}

void WeaponWidget::_onMouseOver(){
  //Show the mod tree widget.
  _showModTree();
}

void WeaponWidget::_onMouseOff(){
}

void WeaponWidget::_hideModTree(){
  _isShowingModTree = false;
}

void WeaponWidget::_showModTree(){
  _isShowingModTree = true;
}
 
