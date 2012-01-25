#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OISKeyboard.h>
#include <string.h>

#include "Ship.h"

class Level {
public:
    Level();
    ~Level();
    void Initialise(const std::string& name, OIS::Keyboard* kb);
    void Launch(Ogre::RenderWindow* window);
    bool update(Ogre::Real deltaTime);

protected:
    void LoadResources();
    void UnloadResources();
    void BuildScene();

    Ogre::SceneManager* scene;
    Ogre::Camera* camera;
    OIS::Keyboard* keyboard;
    std::string name;

    Ship* ship;
};
#endif
