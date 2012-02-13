#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <string>

/**
 * Container class to simplify transportation of an Entity's properties.
 */
class EntityProperties {
public:
    EntityProperties();

    std::string name;
    std::string material;
    std::string mesh;
    Ogre::Vector3 position;
    Ogre::Quaternion orientation;
    Ogre::Real scale;
    Ogre::Real restitution;
    Ogre::Real friction;
    Ogre::Real mass;

};

/**
 * Base class for all objects that have a physical representation in the world.
 *
 * Objects deriving this class must provide a mesh. The mesh is used by OGRE as
 * the object's visual representation, and is passed to Bullet, to use as the
 * object's collidable representation.
 */
class Entity {
public:
    Entity(Ogre::SceneManager* scene, OgreBulletDynamics::DynamicsWorld*
        world, EntityProperties& properties, Ogre::Entity* entity = NULL);
    virtual ~Entity();

    void attachCamera(Ogre::Camera* camera, Ogre::Vector3 offset);

    virtual bool update(Ogre::Real deltaTime);

    const Ogre::SceneNode* getSceneNode() { return this->node; }

    const Ogre::Vector3 getPosition() { return this->body->getWorldPosition(); }
    void setPosition(Ogre::Vector3 position) { this->body->setPosition(position); }

    const Ogre::Vector3 getVelocity() { return this->body->getLinearVelocity(); }
    void setVelocity(Ogre::Vector3 velocity) { this->body->setLinearVelocity(velocity); }

    const Ogre::Quaternion getOrientation() { return this->body->getWorldOrientation(); }
    void setOrientation(Ogre::Quaternion orientation) { this->body->setOrientation(orientation); }

    const Ogre::Quaternion getAngular() { return this->angular; }
    void setAngular(Ogre::Quaternion angular) { this->angular = angular; }

protected:
    Ogre::SceneManager* scene;
    Ogre::SceneNode* node;
    Ogre::Entity* entity;

    OgreBulletDynamics::RigidBody* body;
    Ogre::Quaternion angular;

};

#endif
