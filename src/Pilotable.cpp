#include "Pilotable.h"

Pilotable::Pilotable() {
    thrust = Ogre::Vector3::ZERO;
    torque = Ogre::Quaternion::IDENTITY;
}

Pilotable::~Pilotable() {
}

void Pilotable::setMovementSpeeds(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat) {
    thrustForward = fwd;
    thrustReverse = rev;
    thrustLateral = lat;
}

void Pilotable::setRotationSpeeds(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Radian roll) {
    torqueYaw = yaw;
    torquePitch = pitch;
    torqueRoll = roll;
}

bool Pilotable::actionThrustForward(bool isActive) {
    if(isActive) {
        this->thrust.z -= thrustForward;
    } else {
        this->thrust.z += thrustForward;
    }
    return true;
}

bool Pilotable::actionThrustReverse(bool isActive) {
    if(isActive) {
        this->thrust.z += thrustReverse;
    } else {
        this->thrust.z -= thrustReverse;
    }
    return true;
}

bool Pilotable::actionThrustLeft(bool isActive) {
    if(isActive) {
        this->thrust.x -= thrustLateral;
    } else {
        this->thrust.x += thrustLateral;
    }
    return true;
}

bool Pilotable::actionThrustRight(bool isActive) {
    if(isActive) {
        this->thrust.x += thrustLateral;
    } else {
        this->thrust.x -= thrustLateral;
    }
    return true;
}

bool Pilotable::actionThrustUp(bool isActive) {
    if(isActive) {
        this->thrust.y += thrustLateral;
    } else {
        this->thrust.y -= thrustLateral;
    }
    return true;
}

bool Pilotable::actionThrustDown(bool isActive) {
    if(isActive) {
        this->thrust.y -= thrustLateral;
    } else {
        this->thrust.y += thrustLateral;
    }
    return true;
}

bool Pilotable::actionYawLeft(bool isActive) {
    if(isActive) {
        this->torqueY -= torqueYaw;
    } else {
        this->torqueY += torqueYaw;
    }
    return true;
}

bool Pilotable::actionYawRight(bool isActive) {
    if(isActive) {
        this->torqueY += torqueYaw;
    } else {
        this->torqueY -= torqueYaw;
    }
    return true;
}

bool Pilotable::actionPitchUp(bool isActive) {
    if(isActive) {
        this->torqueX -= torquePitch;
    } else {
        this->torqueX += torquePitch;
    }
    return true;
}

bool Pilotable::actionPitchDown(bool isActive) {
    if(isActive) {
        this->torqueX += torquePitch;
    } else {
        this->torqueX -= torquePitch;
    }
    return true;
}

bool Pilotable::actionRollLeft(bool isActive) {
    if(isActive) {
        this->torqueZ -= torqueYaw;
    } else {
        this->torqueZ += torqueYaw;
    }
    return true;
}

bool Pilotable::actionRollRight(bool isActive) {
    if(isActive) {
        this->torqueZ += torqueYaw;
    } else {
        this->torqueZ -= torqueYaw;
    }
    return true;
}

void Pilotable::setTorque() {
    torque = Ogre::Quaternion(torqueX, Ogre::Vector3::UNIT_X)
           * Ogre::Quaternion(torqueY, Ogre::Vector3::UNIT_Y)
           * Ogre::Quaternion(torqueZ, Ogre::Vector3::UNIT_Z);
}
