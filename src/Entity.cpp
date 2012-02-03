#include <OgreEntity.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>

#include "Entity.h"

Entity::Entity(Ogre::SceneManager* scene, OgreBulletDynamics::DynamicsWorld* world,
        std::string& name, std::string& mesh)
        : scene(scene), velocity(0, 0, 0), angular(Ogre::Quaternion::IDENTITY) {

    node = scene->getRootSceneNode()->createChildSceneNode();

    this->entity = scene->createEntity("Ship/Cruiser", "Cruiser.mesh");
    this->entity->setMaterialName("Steel");
    node->attachObject(this->entity);

    Ogre::Vector3 size = this->entity->getBoundingBox().getSize() * 0.48f;
    OgreBulletCollisions::BoxCollisionShape* shape;
    shape = new OgreBulletCollisions::BoxCollisionShape(size);

    this->body = new OgreBulletDynamics::RigidBody("Ship/Cruiser", world);
    this->body->setShape(this->node, shape, 0.6f, 0.6f, 1.0f,
            Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
}

Entity::~Entity() {
    if(this->entity != NULL) { scene->destroyEntity(this->entity); }
    if(this->node != NULL) { scene->destroySceneNode(this->node); }
    if(this->body != NULL) { delete this->body; }
}

void Entity::attachCamera(Ogre::Camera* camera, Ogre::Vector3 offset) {
    this->node->createChildSceneNode(offset, Ogre::Quaternion::IDENTITY)->attachObject(camera);
    camera->lookAt(node->getPosition());
}

bool Entity::update(Ogre::Real deltaTime) {
    this->node->translate(this->velocity * deltaTime);
    this->node->rotate(Ogre::Quaternion::Slerp(deltaTime, Ogre::Quaternion::IDENTITY, this->angular));
    return true;
}

