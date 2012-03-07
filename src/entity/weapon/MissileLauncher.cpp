#include "MissileLauncher.h"

#include <iostream>

MissileLauncher::MissileLauncher(Entity* attachedTo, Ogre::Vector3 weaponOffset,
        EntityManager* factory)
    : Weapon(attachedTo, weaponOffset), factory(factory), cooldownLength(1), cooldownRemaining(0) {
}

void MissileLauncher::setCooldown(Ogre::Real length) {
    this->cooldownLength = length;
}

void MissileLauncher::fire() {
    if(cooldownRemaining > 0) {
        std::cout << "Cool it, ace!" << std::endl;
        return;
    }

    EntityProperties missileProperties;
    missileProperties.position = this->attached->getPosition()
        + this->attached->getOrientation() * offset;
    missileProperties.orientation = this->attached->getOrientation();
    Missile* missile = factory->createMissile(missileProperties);
    missile->setVelocity(attached->getVelocity()
            + this->attached->getOrientation() * Ogre::Vector3(0, 0, -50));
    cooldownRemaining = cooldownLength;
}

bool MissileLauncher::update(Ogre::Real deltaTime) {
    if(cooldownRemaining > 0) {
        cooldownRemaining -= deltaTime;
    }
    return true;
}

