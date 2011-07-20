#ifndef _THRUST_CONTROLLER_H
#define _THRUST_CONTROLLER_H

#include <OgreVector3.h>

#include <OISInputManager.h>
#include <OISEvents.h>
#include <OISKeyboard.h>

#include "Controller.h"

namespace Controller {
    class Thrust : public Controller {
    public:
        Thrust(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat, Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Radian roll);
        virtual ~Thrust();

        virtual bool Update(Ogre::Real deltaTime) = 0;

        // Controller vectors use LOCAL coordinates
        Ogre::Vector3 thrust;
        Ogre::Radian torqueX, torqueY, torqueZ;

    protected:
        Ogre::Real thrustForward, thrustReverse, thrustLateral;
        Ogre::Radian torqueYaw, torquePitch, torqueRoll;
    };

    class ThrustPlayer : public Thrust, public OIS::KeyListener {
    public:
        ThrustPlayer(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat, Ogre::Radian yaw, \
        		Ogre::Radian pitch, Ogre::Radian roll, OIS::Keyboard* kb);
        virtual ~ThrustPlayer();

        virtual bool Update(Ogre::Real deltaTime);

    protected:
        OIS::Keyboard* keyboard;
        virtual bool keyPressed(const OIS::KeyEvent& event);
        virtual bool keyReleased(const OIS::KeyEvent& event);
    };

    class ThrustAI : public Thrust {
    public:
    	ThrustAI(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat, Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Radian roll);
    	virtual ~ThrustAI();

    	virtual bool Update(Ogre::Real deltaTime);
    private:
    	int timer;
    };
}
#endif
