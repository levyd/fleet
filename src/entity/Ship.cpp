#include <OgreBulletDynamicsWorld.h>

#include "Ship.h"

Ship::Ship(Ogre::SceneManager* scene, OgreBulletDynamics::DynamicsWorld* world, EntityProperties properties)
    : Entity(scene, world, properties), Pilotable(this->Entity::body) {
    this->Entity::body->applyImpulse(Ogre::Vector3(10000, 0, 0), Ogre::Vector3(0, 0, 0));
}

Ship::~Ship() {
}

bool Ship::update(Ogre::Real deltaTime) {
    return Pilotable::update(deltaTime);
}

