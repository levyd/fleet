#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <OgreVector3.h>
#include "../Entity.h"

/**
 * Interface shared by all weapon systems.
 */
class Weapon {
public:
    Weapon(Entity* attachedTo, Ogre::Vector3 weaponOffset);
    virtual ~Weapon() { };

    virtual void fire() = 0;
    virtual bool update(Ogre::Real deltaTime) = 0;

protected:
    Entity* attached;
    Ogre::Vector3 offset;
};

#endif

