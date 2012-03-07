#include "Weapon.h"

Weapon::Weapon(Entity* attachedTo, Ogre::Vector3 weaponOffset)
         : attached(attachedTo), offset(weaponOffset) {
}

