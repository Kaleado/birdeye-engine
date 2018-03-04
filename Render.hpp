#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics.hpp>
#include <cmath>

//!All of this shit is for layout out the UI, please don't touch it.

const int SCREEN_GUTTER=10;//!Space left at the edge of the screen.

const int WEAPON_ICON_SPACING=10;//!Space left between each equipped weapon in the UI.
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

//!Obvious.
const int FRAMERATE=60;

//!This is THE window.
extern sf::RenderWindow window;

//!Returns the distance between two points.
double distanceBetween(sf::Vector2f a, sf::Vector2f b);

//!Returns a random number between 0 and 1.
double randDouble();

//!Returns the angle in degrees.
double radiansToDegrees(double rads);

//!Get the angle that a vector is facing, in radians. 0 radians is
//!pointing horizontally to the right.
double getVectorAngleRadians(sf::Vector2f vec);

//!Get the angle that a vector is facing, in degrees. 0 degrees is
//!pointing horizontally to the right.
double getVectorAngleDegrees(sf::Vector2f vec);

//!Returns the length of the vector.
double getVectorLength(sf::Vector2f vec);

//!Normalises the give vector so that it is of length 1.
sf::Vector2f getUnitVectorOf(sf::Vector2f vec);

//!Returns the unit vector between two points.
sf::Vector2f getUnitVectorBetween(sf::Vector2f src, sf::Vector2f dst);

//!Returns the vector connecting two points.
sf::Vector2f getVectorBetween(sf::Vector2f src, sf::Vector2f dst);

//!Returns whether a given thing is on the screen at the moment.
template <typename WorldThing>
bool isOnScreen(WorldThing& t){
  auto screenPos = t.getScreenPosition();
  return (screenPos.x >= 0 && screenPos.y >= 0 &&
          screenPos.x <= window.getSize().x && screenPos.y <= window.getSize().y);
}

#endif
