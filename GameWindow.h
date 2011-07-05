#ifndef _GAME_WINDOW_H_
#define _GAME_WINDOW_H_

#include <OgreWindowEventUtilities.h>
#include <OgreRenderWindow.h>

class GameWindow : public Ogre::WindowEventListener {
public:
    GameWindow();
    virtual ~GameWindow();

    void Initialise(Ogre::RenderWindow* w);
    bool Update(Ogre::Real deltaTime);

    Ogre::RenderWindow* window;
};
#endif
