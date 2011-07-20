#include <OgreEntity.h>

#include "Ship.h"

Ship::Ship(Ogre::SceneManager* sceneMgr, Ogre::Vector3 position) : Body(sceneMgr, position) {
    Ogre::Entity* entity = sceneMgr->createEntity("Ship/Cruiser", "Cruiser.mesh");
    bodyNode->attachObject(entity);
}

Ship::Ship(Ogre::SceneManager* sceneMgr, Ogre::Vector3 position, OIS::Keyboard* kb)
    : Body(sceneMgr, position) {
	thrustController = new Controller::ThrustPlayer(Ogre::Real(100), Ogre::Real(50), \
			Ogre::Real(10), Ogre::Radian(100), Ogre::Radian(100), Ogre::Radian(100), kb);
	Ogre::Entity* entity = sceneMgr->createEntity("Ship/Cruiser", "Cruiser.mesh");
	bodyNode->attachObject(entity);

}

Ship::~Ship() {
	delete thrustController;
}

bool Ship::Update(Ogre::Real deltaTime) {
	thrustController->Update(deltaTime);
    velocity += bodyNode->getOrientation() * thrustController->thrust * deltaTime;
    Ogre::Quaternion alpha = Ogre::Quaternion(thrustController->torqueX, Ogre::Vector3::UNIT_X)
                           * Ogre::Quaternion(thrustController->torqueY, Ogre::Vector3::UNIT_Y)
                           * Ogre::Quaternion(thrustController->torqueZ, Ogre::Vector3::UNIT_Z);
    angular = angular * Ogre::Quaternion::Slerp(deltaTime, Ogre::Quaternion::IDENTITY, alpha, true);

    return Body::Update(deltaTime);
}

