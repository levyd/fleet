#ifndef _MISSILE_LAUNCHER_H_
#define _MISSILE_LAUNCHER_H_

#include <OgreMath.h>
#include "../EntityManager.h"
#include "Weapon.h"

/**
 * Weapon system responsible for launching Missiles.
 *
 * The missile launcher creates instances of the Missile class when fired. It
 * employs a cooldown period to simulate reloading of the missile tube
 */
class MissileLauncher : public Weapon {
public:
    MissileLauncher(Entity* attachedTo, Ogre::Vector3 weaponOffset,
            EntityManager* factory);
    virtual ~MissileLauncher() { };

    void setCooldown(Ogre::Real length);
    void fire();
    bool update(Ogre::Real deltaTime);

private:
    EntityManager* factory;
    Ogre::Real cooldownLength;
    Ogre::Real cooldownRemaining;

    int missilesFired;
};

#endif

