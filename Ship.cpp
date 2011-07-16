#include <OgreEntity.h>

#include <OgreStringConverter.h>

#include "Ship.h"

Ship::Ship(Ogre::SceneManager* sceneMgr, std::string name, OIS::Keyboard* kb, \
    Ogre::Vector3 position, Ogre::Real MgMass)
    : Body(sceneMgr, position, name),
    mass(MgMass),
    thrustController(100, 50, 10, Ogre::Radian(100), Ogre::Radian(100), kb) {

    Ogre::Entity* entity = sceneMgr->createEntity("Ship/OgreHead", "ogrehead.mesh");
    bodyNode->attachObject(entity);

    //Ogre::AxisAlignedBox boundingBox = entity->getBoundingBox();
}

Ship::~Ship() {
}

bool Ship::Update(Ogre::Real deltaTime) {
	Ogre::LogManager::getSingleton().logMessage("Ship ornt:" + Ogre::StringConverter::toString(bodyNode->getOrientation()) + \
	" angv:" + Ogre::StringConverter::toString(angular) + " trq:" + Ogre::StringConverter::toString(thrustController.torque));
	thrustController.Update(deltaTime);
    velocity += bodyNode->getOrientation() * thrustController.thrust * deltaTime / mass;
    angular = angular * Ogre::Quaternion::Slerp(deltaTime, Ogre::Quaternion::IDENTITY, thrustController.torque, true);
    return Body::Update(deltaTime);
}

