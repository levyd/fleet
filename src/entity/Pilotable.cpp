#include <LinearMath/btVector3.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <OISJoyStick.h>

#include <OgreStringConverter.h>

#include "Pilotable.h"

Pilotable::Pilotable(OgreBulletDynamics::RigidBody* body) : body(body),
    thrust(Ogre::Vector3::ZERO), torque(Ogre::Vector3::ZERO) {
    this->setMovementSpeeds(1.0f, 1.0f, 1.0f);
    this->setRotationSpeeds(1.0f, 1.0f, 1.0f);
}

Pilotable::~Pilotable() {
}

/**
 * Update the state of this object after a game timestep.
 *
 * Applies the active thrust and torque forces to this entity's body.
 *
 * @param deltaTime 
 *     The interval of time that has passed since the last update.
 */
bool Pilotable::update(Ogre::Real deltaTime) {
    // Thrust
    this->body->applyImpulse(this->body->getWorldOrientation() * this->thrust,
            Ogre::Vector3::ZERO);

    // Torque
    Ogre::Vector3 global = this->body->getCenterOfMassOrientation() *
        this->torque;
    btVector3 btTorque = btVector3(global.x, global.y, global.z);
    this->body->getBulletRigidBody()->applyTorque(btTorque);

    return true;
}

/**
 * Sets the maximum thrust that can be applied to this entity.
 */
void Pilotable::setMovementSpeeds(Ogre::Real fwd, Ogre::Real rev,
        Ogre::Real lat) {
    thrustForward = -fwd;
    thrustReverse = rev;
    thrustLeft    = -lat;
    thrustRight   = lat;
    thrustUp      = lat;
    thrustDown    = -lat;
}

/**
 * Sets the maximum torque that can be applied to this entity.
 */
void Pilotable::setRotationSpeeds(Ogre::Real yaw, Ogre::Real pitch,
        Ogre::Real roll) {
    torqueYawLeft   = yaw;
    torqueYawRight  = -yaw;
    torquePitchUp   = pitch;
    torquePitchDown = -pitch;
    torqueRollLeft  = roll;
    torqueRollRight = -roll;
}

bool Pilotable::actionThrustForwardReverse(int old, int abs) {
    if(abs < 0) {
        this->thrust.z = thrustForward * (Ogre::Real(-abs) / OIS::JoyStick::MAX_AXIS);
    } else {
        this->thrust.z = thrustReverse * (Ogre::Real(abs) / OIS::JoyStick::MAX_AXIS);
    }
    return true;
}

bool Pilotable::actionThrustLeftRight(int old, int abs) {
    if(abs < 0) {
        this->thrust.x = thrustLeft * (Ogre::Real(-abs) / OIS::JoyStick::MAX_AXIS);
    } else {
        this->thrust.x = thrustRight * (Ogre::Real(abs) / OIS::JoyStick::MAX_AXIS);
    }
    return true;
}

bool Pilotable::actionThrustUpDown(int old, int abs) {
    if(abs < 0) {
        this->thrust.y = thrustUp * (Ogre::Real(-abs) / OIS::JoyStick::MAX_AXIS);
    } else {
        this->thrust.y = thrustDown * (Ogre::Real(abs) / OIS::JoyStick::MAX_AXIS);
    }
    return true;
}

bool Pilotable::actionYaw(int old, int abs) {
    if(abs < 0) {
        this->torque.y = torqueYawLeft * (Ogre::Real(-abs) / OIS::JoyStick::MAX_AXIS);
    } else {
        this->torque.y = torqueYawRight * (Ogre::Real(abs) / OIS::JoyStick::MAX_AXIS);
    }
    return true;
}

bool Pilotable::actionPitch(int old, int abs) {
    if(abs < 0) {
        this->torque.x = torquePitchDown * (Ogre::Real(-abs) / OIS::JoyStick::MAX_AXIS);
    } else {
        this->torque.x = torquePitchUp * (Ogre::Real(abs) / OIS::JoyStick::MAX_AXIS);
    }
    return true;
}

bool Pilotable::actionRoll(int old, int abs) {
    if(abs < 0) {
        this->torque.z = torqueRollLeft * (Ogre::Real(-abs) / OIS::JoyStick::MAX_AXIS);
    } else {
        this->torque.z = torqueRollRight * (Ogre::Real(abs) / OIS::JoyStick::MAX_AXIS);
    }
    return true;
}

bool Pilotable::actionThrustForward(bool isActive) {
    if(isActive) {
        this->thrust.z = thrustForward;
    } else {
        this->thrust.z = 0;
    }
    return true;
}

bool Pilotable::actionThrustReverse(bool isActive) {
    if(isActive) {
        this->thrust.z = thrustReverse;
    } else {
        this->thrust.z = 0;
    }
    return true;
}

bool Pilotable::actionThrustLeft(bool isActive) {
    if(isActive) {
        this->thrust.x = thrustLeft;
    } else {
        this->thrust.x = 0;
    }
    return true;
}

bool Pilotable::actionThrustRight(bool isActive) {
    if(isActive) {
        this->thrust.x = thrustRight;
    } else {
        this->thrust.x = 0;
    }
    return true;
}

bool Pilotable::actionThrustUp(bool isActive) {
    if(isActive) {
        this->thrust.y = thrustUp;
    } else {
        this->thrust.y = 0;
    }
    return true;
}

bool Pilotable::actionThrustDown(bool isActive) {
    if(isActive) {
        this->thrust.y = thrustDown;
    } else {
        this->thrust.y = 0;
    }
    return true;
}

bool Pilotable::actionYawLeft(bool isActive) {
    if(isActive) {
        this->torque.y = torqueYawLeft;
    } else {
        this->torque.y = 0;
    }
    return true;
}

bool Pilotable::actionYawRight(bool isActive) {
    if(isActive) {
        this->torque.y = torqueYawRight;
    } else {
        this->torque.y = 0;
    }
    return true;
}

bool Pilotable::actionPitchUp(bool isActive) {
    if(isActive) {
        this->torque.x = torquePitchUp;
    } else {
        this->torque.x = 0;
    }
    return true;
}

bool Pilotable::actionPitchDown(bool isActive) {
    if(isActive) {
        this->torque.x = torquePitchDown;
    } else {
        this->torque.x = 0;
    }
    return true;
}

bool Pilotable::actionRollLeft(bool isActive) {
    if(isActive) {
        this->torque.z = torqueRollLeft;
    } else {
        this->torque.z = 0;
    }
    return true;
}

bool Pilotable::actionRollRight(bool isActive) {
    if(isActive) {
        this->torque.z = torqueRollRight;
    } else {
        this->torque.z = 0;
    }
    return true;
}

