#include "Armed.h"

Armed::Armed() : index(0) {
}

Armed::~Armed() {
    for(unsigned i = 0; i < weapons.size(); i++) {
        delete weapons[i];
    }
    weapons.clear();
}

/**
 * Attaches a weapon to this entity.
 *
 * Adds the given Weapon to this Entity's list of managed weapons.
 */
void Armed::attachWeapon(Weapon* weapon) {
    weapons.push_back(weapon);
}

/**
 * Removes a weapon from this entity.
 *
 * Removes the given Weapon from this Entity's list of managed weapons.
 *
 * @param weapon
 *     The Weapon to be removed from the list.
 */
void Armed::removeWeapon(Weapon* weapon) {
    std::vector<Weapon*>::iterator it;
    for(it = weapons.begin(); it < weapons.end(); ++it) {
        if(weapon == *it) {
            weapons.erase(it);
            return;
        }
    }
}

/**
 * Update the state of this object after a game timestep.
 *
 * Updates each of this Entity's managed weapons.
 *
 * @param deltaTime 
 *     The interval of time that has passed since the last update.
 */
bool Armed::update(Ogre::Real deltaTime) {
    std::vector<Weapon*>::iterator it;
    for(it = weapons.begin(); it < weapons.end(); ++it) {
        (*it)->update(deltaTime);
    }
    return true;
}

/**
 * Activates the currently selected weapon.
 */
bool Armed::actionWeaponFire(bool isActive) {
    if(!isActive) { return false; }
    if(index < weapons.size()) {
        weapons[index]->fire();
        return true;
    }
    return false;
}

/**
 * Selects the next weapon.
 *
 * When this ButtonAction is activated, this Armed entity will select the next
 * weapon. If the end of the weapon list is reached, the first weapon will be
 * selected.
 */
bool Armed::actionWeaponNext(bool isActive) {
    if(!isActive) { return false; }
    if(weapons.size() > 0) {
        index = (index + 1) % weapons.size();
        return true;
    }
    return false;
}

/**
 * Selects the previous weapon.
 *
 * When this ButtonAction is activated, this Armed entity will select the
 * previous weapon. If the beginning of the weapon list is reached, the last
 * weapon will be selected.
 */
bool Armed::actionWeaponPrevious(bool isActive) {
    if(!isActive) { return false; }
    if(weapons.size() > 0) {
        index = (index - 1) % weapons.size();
        return true;
    }
    return false;
}


