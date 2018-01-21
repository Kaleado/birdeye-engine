#include "Stats.hpp"

Stats Stats::operator+(const Stats& other){
  Stats result;
  result.maxHp = maxHp + other.maxHp;
  result.speedMultiplier = speedMultiplier + other.speedMultiplier;
  result.reloadDelayMultiplier = reloadDelayMultiplier + other.reloadDelayMultiplier;
  result.firingDelayMultiplier = firingDelayMultiplier + other.firingDelayMultiplier;
  result.abilityCooldownMultiplier = abilityCooldownMultiplier + other.abilityCooldownMultiplier;
  result.globalDamageMultiplier = globalDamageMultiplier + other.globalDamageMultiplier;
  return result;
}

Stats Stats::operator-(const Stats& other){
  Stats result;
  result.maxHp = maxHp - other.maxHp;
  result.speedMultiplier = speedMultiplier - other.speedMultiplier;
  result.reloadDelayMultiplier = reloadDelayMultiplier - other.reloadDelayMultiplier;
  result.firingDelayMultiplier = firingDelayMultiplier - other.firingDelayMultiplier;
  result.abilityCooldownMultiplier = abilityCooldownMultiplier - other.abilityCooldownMultiplier;
  result.globalDamageMultiplier = globalDamageMultiplier - other.globalDamageMultiplier;
  return result;
}

Stats Stats::operator+=(const Stats& other){
  *this = *this + other;
}

Stats Stats::operator-=(const Stats& other){
  *this = *this - other;
}
