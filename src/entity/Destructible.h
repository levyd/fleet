#ifndef _DESTRUCTIBLE_H_
#define _DESTRUCTIBLE_H_

#include "CollisionListener.h"

/**
 * Manages the health of an entity.
 */
class Destructible {
public:
    Destructible(int maxHP);
    virtual ~Destructible() { };

    void damage(int amount);
    void repair(int amount);

    int getHitpoints() { return this->hitpoints; };

private:
    int fullHitpoints;
    int hitpoints;
};

#endif

