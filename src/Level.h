#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>

#include <OISInputManager.h>

#include <OgreBulletDynamicsWorld.h>

#include <string>

#include "control/Player.h"
#include "entity/EntityManager.h"
#include "entity/Ship.h"

class Level {
public:
    Level(const std::string& name, OIS::InputManager* kb);
    ~Level();

    void buildScene();
    void loadResources();
    void launch(Ogre::RenderWindow* window);
    bool update(Ogre::Real deltaTime);
    void unloadResources();

protected:

    std::string name;
    Ogre::SceneManager* scene;
    Ogre::Camera* camera;
    OgreBulletDynamics::DynamicsWorld* world;

    EntityManager* entities;
    Player* player;
    Ship* ship;
};
#endif
