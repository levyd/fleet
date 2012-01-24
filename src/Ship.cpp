#include <OgreEntity.h>

#include "Ship.h"

Ship::Ship(Ogre::SceneManager* sceneMgr, Ogre::Vector3 position) : Body(sceneMgr, position) {
    Ogre::Entity* entity = sceneMgr->createEntity("Ship/Cruiser", "Cruiser.mesh");
    entity->setMaterialName("Steel");
    bodyNode->attachObject(entity);
}

Ship::Ship(Ogre::SceneManager* sceneMgr, Ogre::Vector3 position, OIS::Keyboard* kb, Ogre::Camera* camera)
    : Body(sceneMgr, position) {
    Ogre::Entity* entity = sceneMgr->createEntity("Ship/Cruiser", "Cruiser.mesh");
    entity->setMaterialName("Steel");
    bodyNode->attachObject(entity);

    AttachCamera(camera, Ogre::Vector3(0, 20, 120));

    thrustController = new Controller::ThrustPlayer(this, kb);
    thrustController->setMovementSpeeds(Ogre::Real(100), Ogre::Real(50), \
            Ogre::Real(10));
    thrustController->setRotationSpeeds(Ogre::Radian(100), Ogre::Radian(100), \
            Ogre::Radian(100));

    //turretController = new Controller::TurretPlayer(bodyNode, Ogre::Vector3(15, 0, 0), \
        Ogre::Quaternion(Ogre::Radian(Ogre::Degree(-90)), Ogre::Vector3::UNIT_Y), kb, camera);

}

Ship::~Ship() {
    delete thrustController;
}

bool Ship::Update(Ogre::Real deltaTime) {
    thrustController->Update(deltaTime);
    velocity += bodyNode->getOrientation() * thrustController->thrust * deltaTime;
    angular = angular * Ogre::Quaternion::Slerp(deltaTime, \
        Ogre::Quaternion::IDENTITY, thrustController->torque, true);

    //turretController->Update(deltaTime);

    return Body::Update(deltaTime);
}

