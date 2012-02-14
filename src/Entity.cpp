#include <OgreEntity.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>

#include "Entity.h"

EntityProperties::EntityProperties() : name(""), material(""), mesh(""),
    position(Ogre::Vector3::ZERO), orientation(Ogre::Quaternion::IDENTITY),
    restitution(0.6f), friction(0.6f), mass(1.0f) {
}

/**
 * Entity constructor.
 *
 * If the parameter @a entity has not been specified or is @c null, this constructor
 * will first build a new Ogre::Entity from the fields in @a properties, and then
 * use it to create an @c Entity.
 *
 * If the parameter @a entity is not null, this constructor will use it instead of
 * building a new Ogre::Entity.
 */
Entity::Entity(Ogre::SceneManager* scene, OgreBulletDynamics::DynamicsWorld*
        world, EntityProperties& properties, Ogre::Entity* entity) :
    scene(scene), angular(Ogre::Quaternion::IDENTITY) {

    if(entity == NULL) {
        entity = scene->createEntity(properties.name, properties.mesh);
    }

    this->node = scene->getRootSceneNode()->createChildSceneNode(properties.name);

    this->entity = entity;
    if(!properties.material.empty()) {
        this->entity->setMaterialName(properties.material);
    }
    node->attachObject(this->entity);

    Ogre::Vector3 size = this->entity->getBoundingBox().getSize() * 0.48f;
    OgreBulletCollisions::BoxCollisionShape* shape;
    shape = new OgreBulletCollisions::BoxCollisionShape(size);

    this->body = new OgreBulletDynamics::RigidBody(properties.name, world);
    this->body->setShape(this->node, shape, properties.restitution,
            properties.friction, properties.mass, properties.position,
            properties.orientation);
}

Entity::~Entity() {
    if(this->entity != NULL) { scene->destroyEntity(this->entity); }
    if(this->node != NULL) { scene->destroySceneNode(this->node); }
    if(this->body != NULL) { delete this->body; }
}

/** Attach a camera to this entity */
void Entity::attachCamera(Ogre::Camera* camera, Ogre::Vector3 offset) {
    this->node->createChildSceneNode(offset, Ogre::Quaternion::IDENTITY)->attachObject(camera);
    camera->lookAt(node->getPosition());
}

bool Entity::update(Ogre::Real deltaTime) {
    return true;
}

