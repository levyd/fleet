#ifndef _THRUST_CONTROLLER_H
#define _THRUST_CONTROLLER_H

//#include <OgreVector2.h>
#include <OgreVector3.h>

#include <OISInputManager.h>
#include <OISEvents.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "Controller.h"

namespace Controller {
    class Thrust : public Controller {
    public:
        Thrust(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat, Ogre::Radian horiz, Ogre::Radian vert);
        virtual ~Thrust();

        virtual bool Update(Ogre::Real deltaTime) = 0;

        // Controller vectors use LOCAL coordinates
        Ogre::Vector3 thrust;
        Ogre::Quaternion torque;

    protected:
        Ogre::Real thrustForward, thrustReverse, thrustLateral;
        Ogre::Radian torqueHorizontal, torqueVertical;
    };

    class ThrustPlayer : public Thrust, public OIS::KeyListener {
    public:
        ThrustPlayer(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat,
        		Ogre::Radian horiz, Ogre::Radian vert, OIS::Keyboard* kb);
        virtual ~ThrustPlayer();

        virtual bool Update(Ogre::Real deltaTime);

    protected:
        OIS::Keyboard* keyboard;
        virtual bool keyPressed(const OIS::KeyEvent& event);
        virtual bool keyReleased(const OIS::KeyEvent& event);
    };
}
#endif
