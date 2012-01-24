#include "Body.h"

Body::Body(Ogre::SceneManager* sceneMgr, Ogre::Vector3 position)
    : scene(sceneMgr), velocity(0, 0, 0), angular(Ogre::Quaternion::IDENTITY) {
    bodyNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
    bodyNode->translate(position);
}

Body::~Body() {
}

void Body::AttachCamera(Ogre::Camera*& camera, Ogre::Vector3 offset) {
    bodyNode->createChildSceneNode(offset, Ogre::Quaternion::IDENTITY)->attachObject(camera);
    camera->lookAt(bodyNode->getPosition());
}

bool Body::Update(Ogre::Real deltaTime) {
    bodyNode->translate(velocity * deltaTime);
    bodyNode->rotate(Ogre::Quaternion::Slerp(deltaTime, Ogre::Quaternion::IDENTITY, angular));
    return true;
}

