#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics.hpp>
#include <cmath>

const int SCREEN_GUTTER=10;//Space left at the edge of the screen.

const int WEAPON_ICON_SPACING=10;//Space left between each equipped weapon in the UI.
const int WEAPON_ICON_WIDTH=270;
const int WEAPON_ICON_HEIGHT=90;

const int MOD_MENU_WIDTH=200;
const int MOD_MENU_HEIGHT=400;
const int MOD_MENU_COMMON_RELATIVE_Y_POS=360;
const int MOD_MENU_UNCOMMON_RELATIVE_Y_POS=360 - 80;
const int MOD_MENU_RARE_RELATIVE_Y_POS=360 - 160;
const int MOD_MENU_EPIC_RELATIVE_Y_POS=360 - 240;
const int MOD_MENU_LEGENDARY_RELATIVE_Y_POS=360 - 320;
const int MOD_MENU_ICON_SPACING=10;
const int MOD_MENU_MOD_WIDGET_WIDTH=45;
const int MOD_MENU_MOD_WIDGET_HEIGHT=45;

const int FRAMERATE=60;

extern sf::RenderWindow window;

double distanceBetween(sf::Vector2f a, sf::Vector2f b);

double randDouble();

double radiansToDegrees(double rads);

double getVectorAngleRadians(sf::Vector2f vec);

double getVectorAngleDegrees(sf::Vector2f vec);

double getVectorLength(sf::Vector2f vec);

sf::Vector2f getUnitVectorOf(sf::Vector2f vec);

sf::Vector2f getUnitVectorBetween(sf::Vector2f src, sf::Vector2f dst);

sf::Vector2f getVectorBetween(sf::Vector2f src, sf::Vector2f dst);

template <typename WorldThing>
bool isOnScreen(WorldThing& t){
  auto screenPos = t.getScreenPosition();
  return (screenPos.x >= 0 && screenPos.y >= 0 &&
          screenPos.x <= window.getSize().x && screenPos.y <= window.getSize().y);
}

#endif
