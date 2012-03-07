#include "Missile.h"

Missile::Missile(Ogre::SceneManager* scene, OgreBulletDynamics::DynamicsWorld*
        world, EntityProperties properties) : Entity(scene, world, properties){
}

Missile::~Missile() {
}

/*bool Missile::onCollision(Entity* other) {
    Ogre::Vector3 impulse = this->getVelocity();
    other->body->applyImpulse(impulse);
}*/

bool Missile::update(Ogre::Real deltaTime) {
    return true;
}

