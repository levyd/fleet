#include "Missile.h"

#include <string>
#include <OgreLogManager.h>
#include "Destructible.h"

Missile::Missile(Ogre::SceneManager* scene, OgreBulletDynamics::DynamicsWorld*
        world, EntityProperties properties) : Entity(scene, world, properties){
    this->fuelTime = 5.0;
    CollisionListener::enableCallback(this->body);
}

Missile::~Missile() {
}

bool Missile::onCollision(Entity* other) {
    Ogre::LogManager::getSingleton().logMessage(std::string("Missile has collided with a ") +
            typeid(*other).name());//, Ogre::LML_TRIVIAL);
    Destructible* destructible = dynamic_cast<Destructible*>(other);
    if(destructible != NULL) {
        destructible->damage(10);
    }
    //Ogre::Vector3 impulse = this->getVelocity() - other->getVelocity();
    //other->applyImpulse(impulse);
    return false;
}

bool Missile::update(Ogre::Real deltaTime) {
    if(fuelTime > 0) {
        fuelTime -= deltaTime;
        Ogre::Vector3 thrust = Ogre::Vector3(0, 0, -1000 * deltaTime);
        this->body->applyImpulse(this->body->getWorldOrientation() * thrust,
                Ogre::Vector3::ZERO);
    }
    return true;
}

