#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>

#include <OISInputManager.h>

#include <OgreBulletDynamicsWorld.h>

#include <string.h>

#include "ControllerPlayer.h"
#include "Ship.h"

class Level {
public:
    Level();
    ~Level();
    void initialise(const std::string& name, OIS::InputManager* kb);
    void launch(Ogre::RenderWindow* window);
    bool update(Ogre::Real deltaTime);

protected:
    void loadResources();
    void unloadResources();
    void buildScene();

    std::string name;
    Ogre::SceneManager* scene;
    Ogre::Camera* camera;
    OgreBulletDynamics::DynamicsWorld* world;

    Ship* ship;
    ControllerPlayer* player;
};
#endif
