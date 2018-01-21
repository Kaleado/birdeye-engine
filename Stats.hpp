#ifndef STATS_H
#define STATS_H

class Stats {
public:
  int maxHp;
  double speedMultiplier;
  double reloadDelayMultiplier;
  double firingDelayMultiplier;
  double abilityCooldownMultiplier;
  double globalDamageMultiplier;
  Stats operator+(const Stats& other);
  Stats operator-(const Stats& other);
  Stats operator+=(const Stats& other);
  Stats operator-=(const Stats& other);  
};

#endif
