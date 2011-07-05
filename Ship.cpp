#include <OgreEntity.h>

#include "Ship.h"

Ship::Ship(Ogre::SceneManager* sceneMgr, std::string name, OIS::OISKeyboard* kb, \
    Ogre::Vector3 position, Ogre::Real kgMass)
    : Body(sceneMgr, position, name), mass(kgMass), thrustController(10, 5, 1, 5, kb) {

    Ogre::Entity* entity = sceneMgr->createEntity("Ship/OgreHead", "ogrehead.mesh");
    bodyNode->attachObject(entity);

    //Ogre::AxisAlignedBox boundingBox = entity->getBoundingBox();
}

Ship::~Ship() {
}

bool Ship::Update(Ogre::Real deltaTime) {
	thrustController.Update(deltaTime);
    velocity += bodyNode->getOrientation() * thrustController.thrust * deltaTime / mass;
    return Body::Update(deltaTime);
}

