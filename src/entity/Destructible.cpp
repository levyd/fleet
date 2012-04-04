#include "Destructible.h"

#include <OgreLogManager.h>

/**
 * Constructs a new destructible object with the specified maximum hitpoints.
 */
Destructible::Destructible(int maxHP) {
    this->fullHitpoints = maxHP;
    this->hitpoints = this->fullHitpoints;
}

/**
 * Applies the given damage to this object.
 *
 * @param amount
 *     The amount of damage to apply to this object.
 */
void Destructible::damage(int amount) {
    if(this->hitpoints == 0) {
        return;
    }

    this->hitpoints -= amount;
    if(this->hitpoints <= 0) {
        Ogre::LogManager::getSingleton().logMessage("<this> has died.");
        this->hitpoints = 0;
    }
}

/**
 * Repairs damage that has been applied to this object.
 *
 * @param amount
 *     The amount of damage to repair this object by. Note that a value of zero
 *     will restore this object to its full hit points.
 */
void Destructible::repair(int amount) {
    if(amount == 0) {
        this->hitpoints = fullHitpoints;
    } else {
        this->hitpoints += amount;
        if(this->hitpoints > fullHitpoints) {
            this->hitpoints = fullHitpoints;
        }
    }
}

