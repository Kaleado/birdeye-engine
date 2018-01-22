#ifndef STATS_H
#define STATS_H

/*
  Class representing the player's stats. These stats can be modified
  by weapon mods, player abilities, etc.
 */
class Stats {
public:
  int maxHp;//The player's max hitpoints.
  double speedMultiplier;//A multiplier to the player's max movement speed.
  double reloadDelayMultiplier;//A multiplier to the time taken to reload all weapons.
  double firingDelayMultiplier;//A multiplier to the deley between each shot taken.
  double abilityCooldownMultiplier;//A multiplier to the cooldown of each ability.
  double globalDamageMultiplier;//A multiplier to all damage dealt.
  Stats operator+(const Stats& other);
  Stats operator-(const Stats& other);
  Stats operator+=(const Stats& other);
  Stats operator-=(const Stats& other);  
};

#endif
