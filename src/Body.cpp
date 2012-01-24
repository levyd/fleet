#include "Body.h"

Body::Body(Ogre::SceneManager* sceneMgr, Ogre::Vector3 position)
    : scene(sceneMgr), velocity(0, 0, 0), angular(Ogre::Quaternion::IDENTITY) {
    bodyNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
    bodyNode->translate(position);
}

Body::~Body() {
}

bool Body::Update(Ogre::Real deltaTime) {
    bodyNode->translate(velocity * deltaTime);
    bodyNode->rotate(Ogre::Quaternion::Slerp(deltaTime, Ogre::Quaternion::IDENTITY, angular));
    return true;
}

