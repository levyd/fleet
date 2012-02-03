#include "Pilotable.h"

Pilotable::Pilotable(Ogre::SceneManager* scene, OgreBulletDynamics::DynamicsWorld* world,
        std::string& name, std::string& mesh)
        : Entity(scene, world, name, mesh) {
    thrustController = new Controller::ThrustAI(this);
}

Pilotable::~Pilotable() {
    if(thrustController != NULL) { delete thrustController; }
}

void Pilotable::controlThrust(OIS::Keyboard* kb) {
    if(thrustController != NULL) { delete thrustController; }
    thrustController = new Controller::ThrustPlayer(this, kb);

    thrustController->setMovementSpeeds(Ogre::Real(100), Ogre::Real(50), \
            Ogre::Real(10));
    thrustController->setRotationSpeeds(Ogre::Radian(100), Ogre::Radian(100), \
            Ogre::Radian(100));
}

bool Pilotable::update(Ogre::Real deltaTime) {
    thrustController->update(deltaTime);

    velocity += node->getOrientation() * thrustController->thrust * deltaTime;
    angular = angular * Ogre::Quaternion::Slerp(deltaTime, \
        Ogre::Quaternion::IDENTITY, thrustController->torque, true);

    return Entity::update(deltaTime);
}

