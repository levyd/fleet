#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>

#include "Ship.h"

class Level {
public:
    Level();
    ~Level();
    void Initialise(const std::string& name);
    void Launch(Ogre::RenderWindow* window);
    bool Update(Ogre::Real deltaTime);

protected:
    void LoadResources();
    void UnloadResources();
    void BuildScene();

	Ogre::SceneManager* scene;
    Ogre::Camera* camera;
    std::string name;

    Ship* ship;
};
#endif
