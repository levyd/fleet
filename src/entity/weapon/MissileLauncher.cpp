#include "MissileLauncher.h"

MissileLauncher::MissileLauncher(Entity* attachedTo, Ogre::Vector3 weaponOffset,
        EntityManager* factory)
    : Weapon(attachedTo, weaponOffset), factory(factory), cooldownLength(1), cooldownRemaining(0) {
}

void MissileLauncher::setCooldown(Ogre::Real length) {
    this->cooldownLength = length;
}

void MissileLauncher::fire() {
    if(cooldownRemaining > 0) {
        return;
    }

    EntityProperties missileProperties;
    missileProperties.position = this->attached->getPosition()
        + this->attached->getOrientation() * offset;
    missileProperties.orientation = this->attached->getOrientation();
    missileProperties.mass = 1.0f;
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

