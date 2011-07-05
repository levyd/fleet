#ifndef _THRUST_CONTROLLER_H
#define _THRUST_CONTROLLER_H

#include <OISInputManager.h>
#include <OISEvents.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

namespace Controller {
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
    };

    class ThrustPlayer : public Thrust, public OIS::KeyListener {
    public:
        ThrustPlayer(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat, Ogre::Real rot, OIS::OISKeyboard* kb);
        virtual ~Thrust();

        virtual bool Update(Ogre::Real deltaTime);

    protected:
        OIS::Keyboard* keyboard;
        virtual bool keyPressed(const OIS::KeyEvent& event) = 0;
        virtual bool keyReleased(const OIS::KeyEvent& event) = 0;
}
#endif
