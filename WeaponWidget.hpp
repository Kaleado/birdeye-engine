#ifndef WEAPONWIDGET_H
#define WEAPONWIDGET_H

#include "Ui.hpp"
#include "Weapon.hpp"
#include "ModTree.hpp"
#include "WeaponMod.hpp"

class ModWidget : public Widget {
private:
  std::shared_ptr<WeaponMod> _mod;
  std::shared_ptr<Weapon> _weapon;
  void _onLeftClickRelease();
  void _acquireMod();
public:
  ModWidget(std::string path, sf::Vector2f position, std::shared_ptr<WeaponMod> mod, std::shared_ptr<Weapon> weapon) : Widget(path, position) {
    _mod = mod;
    _weapon = weapon;
  }
};

class WeaponWidget : public Widget {
protected:
  Widget _modTreeWidget;
  std::vector<std::shared_ptr<ModWidget>> _modWidgets;
  void _hideModTree();
  void _showModTree(); 
  bool _isShowingModTree=false;
  bool _showStowedImage=true;
  std::shared_ptr<Weapon> _weapon=nullptr;//nullptr indicates the widget is 'empty'.
  void _onMouseOver();//Show the mod tree widget.
  void _onMouseOff();//Hide the mod tree widget.
  void _rebuildModWidgets();//Re-fetch all the mods from the weapon and update the UI to display them.
public:
  void handleInput(sf::Event event);
  void setWeapon(std::shared_ptr<Weapon> weapon);
  void draw(sf::RenderWindow& window);//Show the modtree widget if we need to. Also show the stowed/unstowed image.
  WeaponWidget(){}
  WeaponWidget(std::shared_ptr<Weapon> weapon, sf::Vector2f position) : Widget{"", position} {
    _weapon = weapon;
    _modTreeWidget = Widget{"modmenu.png", {_position.x - WEAPON_ICON_WIDTH/2, _position.y - MOD_MENU_HEIGHT - WEAPON_ICON_HEIGHT/2}};
  }
};

#endif
