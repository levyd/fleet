#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>

#include "Level.h"
#include "util/Console.h"

class Application : public Ogre::FrameListener {
public:
    Application(void);
    ~Application(void);

    bool initialise(void);
    void launch(void);

protected:
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& event);

private:
    void loadResources(const std::string& resourcesCfg);
    void unloadResources();

    Ogre::Root* root;
    Ogre::RenderWindow* window;
    OIS::InputManager* inputManager;

    OgreConsole* console;

    Level* level;
};

#endif
