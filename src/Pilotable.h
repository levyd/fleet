#ifndef _PILOTABLE_H_
#define _PILOTABLE_H_

#include <OgreMath.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <OgreBulletDynamicsRigidBody.h>
#include "Actionable.h"

class Pilotable : public Actionable {
public:
    Pilotable(OgreBulletDynamics::RigidBody* body);
    virtual ~Pilotable();

    bool update(Ogre::Real deltaTime);
    void setMovementSpeeds(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat);
    void setRotationSpeeds(Ogre::Real yaw, Ogre::Real pitch, Ogre::Real roll);

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
    Ogre::Vector3 thrustForward, thrustReverse, thrustLeft, thrustRight,
        thrustUp, thrustDown;
    /** Torques to apply when torque actions are performed. */
    Ogre::Vector3 torqueYawLeft, torqueYawRight, torquePitchUp, torquePitchDown,
        torqueRollLeft, torqueRollRight;

    /**
     * Applies a force to this Entity's body.
     *
     * The parameter @a force should be given in the Entity's local coordinate
     * system. It will be translated into the global coordinate system before
     * being applied to the body's center of mass.
     *
     * @param force The force to apply, specified in local coordinates.
     */
    void applyForce(Ogre::Vector3 force);

    /**
     * Applies a torque to this Entity's body.
     *
     * The parameter @a torque should be given in the Entity's local coordinate
     * system. It will be translated into the global coordinate system before
     * being applied to the body.
     *
     * @param torque The torque to apply, specified in local coordinates.
     */
    void applyTorque(Ogre::Vector3 torque);
};

#endif

