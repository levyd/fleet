#include <OgreEntity.h>

#include "Entity.h"

Entity::Entity(Ogre::SceneManager* sceneMgr, std::string& name, std::string& mesh)
    : scene(sceneMgr), velocity(0, 0, 0), angular(Ogre::Quaternion::IDENTITY) {
    node = sceneMgr->getRootSceneNode()->createChildSceneNode();

    Ogre::Entity* entity = sceneMgr->createEntity("Ship/Cruiser", "Cruiser.mesh");
    entity->setMaterialName("Steel");
    node->attachObject(entity);
}

Entity::~Entity() {
}

void Entity::attachCamera(Ogre::Camera*& camera, Ogre::Vector3 offset) {
    node->createChildSceneNode(offset, Ogre::Quaternion::IDENTITY)->attachObject(camera);
    camera->lookAt(node->getPosition());
}

bool Entity::update(Ogre::Real deltaTime) {
    node->translate(velocity * deltaTime);
    node->rotate(Ogre::Quaternion::Slerp(deltaTime, Ogre::Quaternion::IDENTITY, angular));
    return true;
}

