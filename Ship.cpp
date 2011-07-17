#include <OgreEntity.h>

#include <OgreStringConverter.h>

#include "Ship.h"

Ship::Ship(Ogre::SceneManager* sceneMgr, std::string name, OIS::Keyboard* kb, \
    Ogre::Vector3 position, Ogre::Real MgMass)
    : Body(sceneMgr, position, name),
    mass(MgMass),
    thrustController(100, 50, 10, Ogre::Radian(100), Ogre::Radian(100), Ogre::Radian(100), kb) {

    Ogre::Entity* entity = sceneMgr->createEntity("Ship/Cruiser", "Cruiser.mesh");
    bodyNode->attachObject(entity);

    //Ogre::AxisAlignedBox boundingBox = entity->getBoundingBox();
}

Ship::~Ship() {
}

bool Ship::Update(Ogre::Real deltaTime) {
	thrustController.Update(deltaTime);
    velocity += bodyNode->getOrientation() * thrustController.thrust * deltaTime / mass;
    Ogre::Quaternion alpha = Ogre::Quaternion(thrustController.torqueX, Ogre::Vector3::UNIT_X)
                           * Ogre::Quaternion(thrustController.torqueY, Ogre::Vector3::UNIT_Y)
                           * Ogre::Quaternion(thrustController.torqueZ, Ogre::Vector3::UNIT_Z);
    angular = angular * Ogre::Quaternion::Slerp(deltaTime, Ogre::Quaternion::IDENTITY, alpha, true);


    Ogre::LogManager::getSingleton().logMessage("Ship ornt:" + Ogre::StringConverter::toString(bodyNode->getOrientation()) + \
	" angv:" + Ogre::StringConverter::toString(angular) + " trq:" + Ogre::StringConverter::toString(alpha));

    return Body::Update(deltaTime);
}

