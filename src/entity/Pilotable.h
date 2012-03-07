#ifndef _PILOTABLE_H_
#define _PILOTABLE_H_

#include <OgreMath.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <OgreBulletDynamicsRigidBody.h>
#include "Actionable.h"

/**
 * Handles movement actions.
 *
 * Entities deriving from this class can propel themselves around the game
 * environment.
 */
class Pilotable : virtual public Actionable {
public:
    Pilotable(OgreBulletDynamics::RigidBody* body);
    virtual ~Pilotable();

    bool update(Ogre::Real deltaTime);
    void setMovementSpeeds(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat);
    void setRotationSpeeds(Ogre::Real yaw, Ogre::Real pitch, Ogre::Real roll);

    virtual bool actionThrustForwardReverse(int old, int abs);
    virtual bool actionThrustLeftRight(int old, int abs);
    virtual bool actionThrustUpDown(int old, int abs);
    virtual bool actionYaw(int old, int abs);
    virtual bool actionPitch(int old, int abs);
    virtual bool actionRoll(int old, int abs);

    virtual bool actionThrustForward(bool isActive);
    virtual bool actionThrustReverse(bool isActive);
    virtual bool actionThrustLeft(bool isActive);
    virtual bool actionThrustRight(bool isActive);
    virtual bool actionThrustUp(bool isActive);
    virtual bool actionThrustDown(bool isActive);
    virtual bool actionYawLeft(bool isActive);
    virtual bool actionYawRight(bool isActive);
    virtual bool actionPitchUp(bool isActive);
    virtual bool actionPitchDown(bool isActive);
    virtual bool actionRollLeft(bool isActive);
    virtual bool actionRollRight(bool isActive);

private:
    /** Local cache of an Entity's RigidBody */
    OgreBulletDynamics::RigidBody* body;
    /** Current state of this object's thrusters */
    Ogre::Vector3 thrust, torque;
    /** Forces to apply when thrust actions are performed. */
    Ogre::Real thrustForward, thrustReverse, thrustLeft, thrustRight,
        thrustUp, thrustDown;
    /** Torques to apply when torque actions are performed. */
    Ogre::Real torqueYawLeft, torqueYawRight, torquePitchUp, torquePitchDown,
        torqueRollLeft, torqueRollRight;
};

#endif

