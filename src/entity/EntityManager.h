#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include <OgreSceneManager.h>
#include <OgreBulletDynamicsWorld.h>

#include <string>
#include <list>

#include "Entity.h"
#include "Missile.h"
#include "Ship.h"

class EntityManager {
public:
    EntityManager(Ogre::SceneManager* scene,
            OgreBulletDynamics::DynamicsWorld* world);
    virtual ~EntityManager();

    Entity*  createEntity(EntityProperties& properties);
    Entity*  createPlanet(EntityProperties& properties);
    Ship*    createShip(EntityProperties& properties);
    Missile* createMissile(EntityProperties& properties);
    bool     update(Ogre::Real deltaTime);

    void useScene(Ogre::SceneManager* scene,
            OgreBulletDynamics::DynamicsWorld* world);
    Entity* add(Entity* entity);
    void remove(Entity* entity);

    void registerAsSingleton();
    bool onCollision(btManifoldPoint& cp, const btCollisionObject* colObj0,
            int partId0, int index0, const btCollisionObject* colObj1,
            int partId1, int index1);

private:
    std::list<Entity*>::iterator find(Entity* entity);
    std::list<Entity*>::iterator remove(std::list<Entity*>::iterator it);

    Ogre::SceneManager* scene;
    OgreBulletDynamics::DynamicsWorld* world;

    std::list<Entity*> entities;
    std::map<const btRigidBody*, Entity*> objectMap;

    // TEMPORARY - DON'T ADD MORE COUNTERS
    int numMissiles;
};

#endif

