#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include <OgreRoot.h>

#include "GameWindow.h"
#include "Level.h"

class Application : Ogre::FrameListener {
public:
    Application(void);
    ~Application(void);

    bool Initialise(void);
    void Launch(void);

protected:
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& event);

private:
    Ogre::Root* root;

    void LoadResources(const std::string& resourcesCfg);

    GameWindow gameWindow;
    Level level;
};

#endif
