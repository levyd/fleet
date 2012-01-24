#ifndef _THRUST_CONTROLLER_H
#define _THRUST_CONTROLLER_H

#include <OgreSceneNode.h>

#include <OISInputManager.h>
#include <OISEvents.h>
#include <OISKeyboard.h>

#include "Body.h"
#include "Controller.h"

namespace Controller {
    class Thrust : public Controller {
    public:
        Thrust(Body* body);
        virtual ~Thrust();

        virtual bool Update(Ogre::Real deltaTime) = 0;

        void setMovementSpeeds(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat);
        void setRotationSpeeds(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Radian roll);

        Body* body;

        // Controller vectors use LOCAL coordinates
        Ogre::Vector3 thrust;
        Ogre::Quaternion torque;

    protected:
        void setTorque();

        Ogre::Real thrustForward, thrustReverse, thrustLateral;
        Ogre::Radian torqueYaw, torquePitch, torqueRoll;
        Ogre::Radian torqueX, torqueY, torqueZ;
    };

    class ThrustPlayer : public Thrust, public OIS::KeyListener {
    public:
        ThrustPlayer(Body* body, OIS::Keyboard*& kb);
        virtual ~ThrustPlayer();

        virtual bool Update(Ogre::Real deltaTime);

    protected:
        OIS::Keyboard* keyboard;
        virtual bool keyPressed(const OIS::KeyEvent& event);
        virtual bool keyReleased(const OIS::KeyEvent& event);
    };

    class ThrustAI : public Thrust {
    public:
    	ThrustAI(Body* body);
    	virtual ~ThrustAI();

    	virtual bool Update(Ogre::Real deltaTime);
    private:
    	int timer;
    };
}
#endif
