#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <OgreRenderWindow.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

namespace Controller {
    void BuildInputManager(Ogre::RenderWindow* window);

    class Controller : public OIS::KeyListener {//, public OIS::MouseListener {
    public:
        Controller();
        virtual ~Controller();

        virtual bool Update(Ogre::Real deltaTime) = 0;

    protected:
        OIS::Keyboard* keyboard;
        virtual bool keyPressed(const OIS::KeyEvent& event) = 0;
        virtual bool keyReleased(const OIS::KeyEvent& event) = 0;

        //OIS::Mouse* mouse;
        //virtual bool mouseMoved(const OIS::MouseEvent& event) = 0;
        //virtual bool mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID id) = 0;
        //virtual bool mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID id) = 0;
    };

    class Thrust : public Controller {
    public:
        Thrust(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat, Ogre::Real rot);
        virtual ~Thrust();

        virtual bool Update(Ogre::Real deltaTime);

        // Controller vectors use LOCAL coordinates
        Ogre::Vector3 thrust;
        Ogre::Vector2 torque;

    protected:
        Ogre::Real maxForward, maxReverse, maxLateral, maxRotation;

        virtual bool keyPressed(const OIS::KeyEvent& event);
        virtual bool keyReleased(const OIS::KeyEvent& event);

        //virtual bool mouseMoved(const OIS::MouseEvent& event) = 0;
        //virtual bool mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID id);
        //virtual bool mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID id);
    };
}
#endif
