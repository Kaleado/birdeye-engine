#include "Render.hpp"

sf::RenderWindow window{sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Testing", sf::Style::Fullscreen};

double distanceBetween(sf::Vector2f a, sf::Vector2f b){
  double dx = a.x - b.x;
  double dy = a.y - b.y;

  return std::sqrt(dx*dx + dy*dy);
}

double randDouble(){
  return static_cast<double>(std::rand())/RAND_MAX;
}

double randSignedDouble(){
  return randDouble()*2 - 1;
}

double radiansToDegrees(double rads){
  return rads / 3.14159265358979 * 180;
}

double getVectorAngleRadians(sf::Vector2f vec){
  return atan2(vec.y, vec.x);
}

double getVectorAngleDegrees(sf::Vector2f vec){
  return radiansToDegrees(getVectorAngleRadians(vec));
}

double getVectorLength(sf::Vector2f vec){
  return std::sqrt(vec.x*vec.x + vec.y*vec.y);
}

sf::Vector2f getUnitVectorOf(sf::Vector2f vec){
  double len = getVectorLength(vec);
  if(len == 0){return {0,0};}
  return sf::Vector2f{vec.x / len, vec.y / len};
}

sf::Vector2f getVectorBetween(sf::Vector2f src, sf::Vector2f dst){
  float opp = dst.y - src.y;
  float adj = dst.x - src.x;
  return sf::Vector2f{adj, opp};
}

sf::Vector2f getUnitVectorBetween(sf::Vector2f src, sf::Vector2f dst){
  return getUnitVectorOf(getVectorBetween(src, dst));
}
