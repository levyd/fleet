#include "ThrustController.h"

#include <OgreLogManager.h>
namespace Controller {
    Thrust::Thrust(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat, Ogre::Radian rot)
        : Controller(), thrust(0, 0, 0), torque(0, 0, 0), maxForward(fwd), \
          maxReverse(rev), maxLateral(lat), maxRotation(rot) {
    }
    //--------------------------------------------------------------------------
    Thrust::~Thrust() {
    }
    //--------------------------------------------------------------------------
    ThrustPlayer::ThrustPlayer(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat, Ogre::Radian rot, \
        OIS::Keyboard* kb) : Thrust(fwd, rev, lat, rot) {
        keyboard = kb;
        keyboard->setEventCallback(this);
    }
    //--------------------------------------------------------------------------
    ThrustPlayer::~ThrustPlayer() {
    }
    //--------------------------------------------------------------------------
    bool ThrustPlayer::Update(Ogre::Real deltaTime) {
        keyboard->capture();
        return true;
    }
    //--------------------------------------------------------------------------
    bool ThrustPlayer::keyPressed(const OIS::KeyEvent& event) {
        switch(event.key) {
        case OIS::KC_W:
            thrust.z += maxForward;
            break;
        case OIS::KC_A:
            thrust.x += maxLateral;
            break;
        case OIS::KC_S:
            thrust.z -= maxReverse;
            break;
        case OIS::KC_D:
            thrust.x -= maxLateral;
            break;
        case OIS::KC_UP:
            torque = torque * Ogre::Quaternion(-maxRotation, Ogre::Vector3::UNIT_X);
            break;
        case OIS::KC_LEFT:
            torque = torque * Ogre::Quaternion(maxRotation, Ogre::Vector3::UNIT_Y);
            break;
        case OIS::KC_DOWN:
            torque = torque * Ogre::Quaternion(maxRotation, Ogre::Vector3::UNIT_X);
            break;
        case OIS::KC_RIGHT:
            torque = torque * Ogre::Quaternion(-maxRotation, Ogre::Vector3::UNIT_Y);
            break;
        default:
            return false;
        }
        return true;
    }
    //--------------------------------------------------------------------------
    bool ThrustPlayer::keyReleased(const OIS::KeyEvent& event) {
        switch(event.key) {
        case OIS::KC_W:
            thrust.x -= maxForward;
            break;
        case OIS::KC_A:
            thrust.z += maxLateral;
            break;
        case OIS::KC_S:
            thrust.x += maxReverse;
            break;
        case OIS::KC_D:
            thrust.z -= maxLateral;
            break;
        case OIS::KC_UP:
        	torque = torque * Ogre::Quaternion(maxRotation, Ogre::Vector3::UNIT_X);
        	break;
        case OIS::KC_LEFT:
        	torque = torque * Ogre::Quaternion(-maxRotation, Ogre::Vector3::UNIT_Y);
        	break;
        case OIS::KC_DOWN:
        	torque = torque * Ogre::Quaternion(-maxRotation, Ogre::Vector3::UNIT_X);
        	break;
        case OIS::KC_RIGHT:
        	torque = torque * Ogre::Quaternion(maxRotation, Ogre::Vector3::UNIT_Y);
        	break;
        default:
          return false;
        }
        return true;
    }
}
