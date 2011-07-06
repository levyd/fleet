#include <OgreEntity.h>

#include "Ship.h"

Ship::Ship(Ogre::SceneManager* sceneMgr, std::string name, OIS::Keyboard* kb, \
    Ogre::Vector3 position, Ogre::Real kgMass) : Body(sceneMgr, position, name), \
    mass(kgMass), moment(kgMass), thrustController(100, 50, 10, Ogre::Radian(50), kb) {

    Ogre::Entity* entity = sceneMgr->createEntity("Ship/OgreHead", "ogrehead.mesh");
    bodyNode->attachObject(entity);

    //Ogre::AxisAlignedBox boundingBox = entity->getBoundingBox();
}

Ship::~Ship() {
}

bool Ship::Update(Ogre::Real deltaTime) {
	thrustController.Update(deltaTime);
    velocity += bodyNode->getOrientation() * thrustController.thrust * deltaTime / mass;
    angular = angular * thrustController.torque * (deltaTime / moment);
    return Body::Update(deltaTime);
}

