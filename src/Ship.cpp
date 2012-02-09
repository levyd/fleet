#include <OgreBulletDynamicsWorld.h>

#include "Ship.h"

Ship::Ship(Ogre::SceneManager* scene, OgreBulletDynamics::DynamicsWorld* world, std::string name, std::string mesh)
    : Entity(scene, world, name, mesh) {
}

Ship::~Ship() {
}

bool Ship::update(Ogre::Real deltaTime) {
    velocity += node->getOrientation() * this->thrust * deltaTime;
    angular = angular * Ogre::Quaternion::Slerp(deltaTime,
            Ogre::Quaternion::IDENTITY, this->torque, true);

    return Entity::update(deltaTime);
}

