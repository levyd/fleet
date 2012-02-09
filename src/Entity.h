#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <string.h>

/**
 * Base class for all objects that have a physical representation in the world.
 *
 * Objects deriving this class must provide a mesh. The mesh is used by OGRE as
 * the object's visual representation, and is passed to Bullet, to use as the
 * object's collidable representation.
 */
class Entity {
public:
    Entity(Ogre::SceneManager* scene, OgreBulletDynamics::DynamicsWorld* world,
            std::string& name, std::string& mesh);
    virtual ~Entity();

    void attachCamera(Ogre::Camera* camera, Ogre::Vector3 offset);

    virtual bool update(Ogre::Real deltaTime);

    const Ogre::SceneNode* getSceneNode() { return this->node; }

    const Ogre::Vector3 getPosition() { return this->node->getPosition(); }
    void setPosition(Ogre::Vector3 position) { this->node->translate(position); }

    const Ogre::Vector3 getVelocity() { return this->velocity; }
    void setVelocity(Ogre::Vector3 velocity) { this->velocity = velocity; }

    const Ogre::Quaternion getOrientation() { return this->node->getOrientation(); }
    // TODO: Make this based on (global?) orientation
    void setOrientation(Ogre::Quaternion orientation) { this->node->rotate(orientation); }

    const Ogre::Quaternion getAngular() { return this->angular; }
    void setAngular(Ogre::Quaternion angular) { this->angular = angular; }

protected:
    Ogre::SceneManager* scene;
    Ogre::SceneNode* node;
    Ogre::Entity* entity;

    OgreBulletDynamics::RigidBody* body;
    Ogre::Vector3 velocity;
    Ogre::Quaternion angular;

};

#endif
