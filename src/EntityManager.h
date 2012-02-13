#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include <OgreSceneManager.h>
#include <OgreBulletDynamicsWorld.h>

#include <string>
#include <vector>

#include "Entity.h"
#include "Ship.h"

class EntityManager {
public:
    EntityManager(Ogre::SceneManager* scene,
            OgreBulletDynamics::DynamicsWorld* world);
    virtual ~EntityManager();

    Entity* createEntity(EntityProperties& properties);
    Entity* createPlanet(EntityProperties& properties);
    Ship*   createShip(EntityProperties& properties);
    bool    update(Ogre::Real deltaTime);

private:
    Ogre::SceneManager* scene;
    OgreBulletDynamics::DynamicsWorld* world;

    std::vector<Entity*> entities;
};

#endif

