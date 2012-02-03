#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include <OgreSceneManager.h>
#include <OgreBulletDynamicsWorld.h>

#include <string.h>

class EntityManager {
public:
    EntityManager(Ogre::SceneManager* scene);
    virtual ~EntityManager();

    Entity* createEntity(std::string& name, std::string& mesh);
    bool update(Ogre::Real deltaTime);

private:
    Entity* entities[4] = { NULL };
    int entityIndex = 0;

    Ogre::SceneManager* scene;
}

#endif

