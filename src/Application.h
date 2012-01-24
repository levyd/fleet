#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>

#include "Level.h"

class Application : public Ogre::FrameListener, public Ogre::WindowEventListener {
public:
    Application(void);
    ~Application(void);

    bool Initialise(void);
    void Launch(void);

protected:
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& event);
    virtual void windowClosed(Ogre::RenderWindow* rw);

private:
    void LoadResources(const std::string& resourcesCfg);

    Ogre::Root* root;
    Ogre::RenderWindow* window;
    OIS::InputManager* input;
    OIS::Keyboard* keyboard;

    Level level;
};

#endif
