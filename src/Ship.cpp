#include "Ship.h"

Ship::Ship(Ogre::SceneManager* sceneMgr, std::string name, std::string mesh)
    : Entity(sceneMgr, name, mesh) {

    thrustController = new Controller::ThrustAI(this);

    //turretController = new Controller::TurretPlayer(node, Ogre::Vector3(15, 0, 0), \
        Ogre::Quaternion(Ogre::Radian(Ogre::Degree(-90)), Ogre::Vector3::UNIT_Y), kb, camera);
}

Ship::~Ship() {
    if(thrustController != NULL) { delete thrustController; }
}

void Ship::controlThrust(OIS::Keyboard* kb) {
    if(thrustController != NULL) { delete thrustController; }
    thrustController = new Controller::ThrustPlayer(this, kb);

    thrustController->setMovementSpeeds(Ogre::Real(100), Ogre::Real(50), \
            Ogre::Real(10));
    thrustController->setRotationSpeeds(Ogre::Radian(100), Ogre::Radian(100), \
            Ogre::Radian(100));
}

bool Ship::update(Ogre::Real deltaTime) {
    thrustController->update(deltaTime);
    velocity += node->getOrientation() * thrustController->thrust * deltaTime;
    angular = angular * Ogre::Quaternion::Slerp(deltaTime, \
        Ogre::Quaternion::IDENTITY, thrustController->torque, true);

    //turretController->update(deltaTime);

    return Entity::update(deltaTime);
}

