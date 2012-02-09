#ifndef _PILOTABLE_H_
#define _PILOTABLE_H_

#include <OgreMath.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include "Actionable.h"

class Pilotable : public Actionable {
public:
    Pilotable();
    virtual ~Pilotable();

    void setMovementSpeeds(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat);
    void setRotationSpeeds(Ogre::Radian yaw,
            Ogre::Radian pitch, Ogre::Radian roll);

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

protected:
    Ogre::Vector3 thrust;
    Ogre::Quaternion torque;

private:
    /** Speeds to apply when thrust actions are performed. */
    Ogre::Real thrustForward, thrustReverse, thrustLateral;
    /** Angular velocities to apply when torque actions are performed. */
    Ogre::Radian torqueYaw, torquePitch, torqueRoll;

    Ogre::Radian torqueX, torqueY, torqueZ;
    void setTorque();
};

#endif

