#include "Pilotable.h"

#include <LinearMath/btVector3.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>

Pilotable::Pilotable(OgreBulletDynamics::RigidBody* body) : body(body) {
    this->setMovementSpeeds(1.0f, 1.0f, 1.0f);
    this->setRotationSpeeds(1.0f, 1.0f, 1.0f);
}

Pilotable::~Pilotable() {
}

void Pilotable::setMovementSpeeds(Ogre::Real fwd, Ogre::Real rev,
        Ogre::Real lat) {
    thrustForward = Ogre::Vector3(   0,    0,  fwd);
    thrustReverse = Ogre::Vector3(   0,    0, -rev);
    thrustLeft    = Ogre::Vector3(-lat,    0,    0);
    thrustRight   = Ogre::Vector3( lat,    0,    0);
    thrustUp      = Ogre::Vector3(   0,  lat,    0);
    thrustDown    = Ogre::Vector3(   0, -lat,    0);
}

void Pilotable::setRotationSpeeds(Ogre::Real yaw, Ogre::Real pitch,
        Ogre::Real roll) {
    torqueYawLeft   = Ogre::Vector3(     0, -yaw,     0);
    torqueYawRight  = Ogre::Vector3(     0,  yaw,     0);
    torquePitchUp   = Ogre::Vector3(-pitch,    0,     0);
    torquePitchDown = Ogre::Vector3( pitch,    0,     0);
    torqueRollLeft  = Ogre::Vector3(     0,    0, -roll);
    torqueRollRight = Ogre::Vector3(     0,    0,  roll);
}

bool Pilotable::actionThrustForward(bool isActive) {
    if(isActive) {
        this->applyForce(thrustForward);
    } else {
        this->applyForce(-thrustForward);
    }
    return true;
}

bool Pilotable::actionThrustReverse(bool isActive) {
    if(isActive) {
        this->applyForce(thrustReverse);
    } else {
        this->applyForce(-thrustReverse);
    }
    return true;
}

bool Pilotable::actionThrustLeft(bool isActive) {
    if(isActive) {
        this->applyForce(thrustLeft);
    } else {
        this->applyForce(-thrustLeft);
    }
    return true;
}

bool Pilotable::actionThrustRight(bool isActive) {
    if(isActive) {
        this->applyForce(thrustRight);
    } else {
        this->applyForce(-thrustRight);
    }
    return true;
}

bool Pilotable::actionThrustUp(bool isActive) {
    if(isActive) {
        this->applyForce(thrustUp);
    } else {
        this->applyForce(-thrustUp);
    }
    return true;
}

bool Pilotable::actionThrustDown(bool isActive) {
    if(isActive) {
        this->applyForce(thrustDown);
    } else {
        this->applyForce(-thrustDown);
    }
    return true;
}

bool Pilotable::actionYawLeft(bool isActive) {
    if(isActive) {
        this->applyTorque(torqueYawLeft);
    } else {
        this->applyTorque(-torqueYawLeft);
    }
    return true;
}

bool Pilotable::actionYawRight(bool isActive) {
    if(isActive) {
        this->applyTorque(torqueYawRight);
    } else {
        this->applyTorque(-torqueYawRight);
    }
    return true;
}

bool Pilotable::actionPitchUp(bool isActive) {
    if(isActive) {
        this->applyTorque(torquePitchUp);
    } else {
        this->applyTorque(-torquePitchUp);
    }
    return true;
}

bool Pilotable::actionPitchDown(bool isActive) {
    if(isActive) {
        this->applyTorque(torquePitchDown);
    } else {
        this->applyTorque(-torquePitchDown);
    }
    return true;
}

bool Pilotable::actionRollLeft(bool isActive) {
    if(isActive) {
        this->applyTorque(torqueRollLeft);
    } else {
        this->applyTorque(-torqueRollLeft);
    }
    return true;
}

bool Pilotable::actionRollRight(bool isActive) {
    if(isActive) {
        this->applyTorque(torqueRollRight);
    } else {
        this->applyTorque(-torqueRollRight);
    }
    return true;
}

void Pilotable::applyForce(Ogre::Vector3 force) {
    this->body->applyImpulse(
            this->body->getWorldOrientation() * force,
            Ogre::Vector3::ZERO);
}

void Pilotable::applyTorque(Ogre::Vector3 torque) {
    Ogre::Vector3 global = this->body->getCenterOfMassOrientation() * torque;
    btVector3 btTorque = btVector3(global.x, global.y, global.z);
    this->body->getBulletRigidBody()->applyTorque(btTorque);
}

