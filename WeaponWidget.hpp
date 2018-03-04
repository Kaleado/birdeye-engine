#ifndef WEAPONWIDGET_H
#define WEAPONWIDGET_H

#include "Ui.hpp"
#include "Weapon.hpp"
#include "ModTree.hpp"
#include "WeaponMod.hpp"

/**
  This class represents the UI element for a mod in the mod menu.
 */
class ModWidget : public Widget {
private:
  //!This is the mod itself.
  std::shared_ptr<WeaponMod> _mod;

  //!This is the weapon the mod is attached to.
  std::shared_ptr<Weapon> _weapon;

  //!This is a UI element so we had to override this to make it so that
  //!when the element is clicked, the mod is acquired.
  void _onLeftClickRelease();

  //!Acquires the mod.
  void _acquireMod();
public:
  ModWidget(std::string path, sf::Vector2f position, std::shared_ptr<WeaponMod> mod, std::shared_ptr<Weapon> weapon) : Widget(path, position) {
    _mod = mod;
    _weapon = weapon;
  }
};

/**
  This class represents the weapon icons at the bottom of the screen.
 */
class WeaponWidget : public Widget {
protected:
  //!Represents the mod tree that pops up when you mouse-over the weapon icon.
  Widget _modTreeWidget;
  
  //!This list will contain widgets for each mod in the mod tree.
  std::vector<std::shared_ptr<ModWidget>> _modWidgets;

  //!Shows and hides the mod tree widget in the UI.
  void _hideModTree();
  void _showModTree();

  //!Whether to show the mod tree widget or not.
  bool _isShowingModTree=false;

  //!Whether the 'stowed' image should be shown or not - implementation-related.
  bool _showStowedImage=true;

  //!Points to the weapon that the widget is linked to. nullptr indicates the widget is 'empty'.
  std::shared_ptr<Weapon> _weapon=nullptr;

  //!These are overriden to give the desired behaviour to the weapon widget.
  //!Show the mod tree widget.
  void _onMouseOver();
  
  //!Hide the mod tree widget.  
  void _onMouseOff();

  //!Re-fetch all the mods from the weapon and update the UI to display them.
  void _rebuildModWidgets();
public:
  //!You know what this is already.
  void handleInput(sf::Event event);

  //!Sets the weapon to be displayed in the widget.
  void setWeapon(std::shared_ptr<Weapon> weapon);

  //!Show the modtree widget if we need to. Also show the stowed/unstowed image.
  void draw(sf::RenderWindow& window);
  
  WeaponWidget(){}
  WeaponWidget(std::shared_ptr<Weapon> weapon, sf::Vector2f position) : Widget{"", position} {
    _weapon = weapon;
    _modTreeWidget = Widget{"modmenu.png", {_position.x - WEAPON_ICON_WIDTH/2, _position.y - MOD_MENU_HEIGHT - WEAPON_ICON_HEIGHT/2}};
  }
};

#endif
