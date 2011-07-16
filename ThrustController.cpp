#include "ThrustController.h"

#include <OgreLogManager.h>
namespace Controller {
    Thrust::Thrust(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat, Ogre::Radian horiz, Ogre::Radian vert)
        : Controller(),
          thrust(0, 0, 0),
          torque(Ogre::Quaternion::IDENTITY),
          thrustForward(fwd),
          thrustReverse(rev),
          thrustLateral(lat),
          torqueHorizontal(horiz),
          torqueVertical(vert) {
    }
    //--------------------------------------------------------------------------
    Thrust::~Thrust() {
    }
    //--------------------------------------------------------------------------
    ThrustPlayer::ThrustPlayer(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat, Ogre::Radian horiz, Ogre::Radian vert, \
        OIS::Keyboard* kb) : Thrust(fwd, rev, lat, horiz, vert) {
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
            thrust.z += thrustForward;
            break;
        case OIS::KC_A:
            thrust.x += thrustLateral;
            break;
        case OIS::KC_S:
            thrust.z -= thrustReverse;
            break;
        case OIS::KC_D:
            thrust.x -= thrustLateral;
            break;
        case OIS::KC_UP:
            torque = torque * Ogre::Quaternion(-torqueVertical, Ogre::Vector3::UNIT_X);
            break;
        case OIS::KC_LEFT:
            torque = torque * Ogre::Quaternion(torqueHorizontal, Ogre::Vector3::UNIT_Y);
            break;
        case OIS::KC_DOWN:
            torque = torque * Ogre::Quaternion(torqueVertical, Ogre::Vector3::UNIT_X);
            break;
        case OIS::KC_RIGHT:
            torque = torque * Ogre::Quaternion(-torqueHorizontal, Ogre::Vector3::UNIT_Y);
            break;
        case OIS::KC_SPACE:
        	thrust = Ogre::Vector3::ZERO;
        	torque = Ogre::Quaternion::IDENTITY;
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
             thrust.z -= thrustForward;
             break;
         case OIS::KC_A:
             thrust.x -= thrustLateral;
             break;
         case OIS::KC_S:
             thrust.z += thrustReverse;
             break;
         case OIS::KC_D:
             thrust.x += thrustLateral;
             break;
        case OIS::KC_UP:
        	torque = torque * Ogre::Quaternion(torqueVertical, Ogre::Vector3::UNIT_X);
        	break;
        case OIS::KC_LEFT:
        	torque = torque * Ogre::Quaternion(-torqueHorizontal, Ogre::Vector3::UNIT_Y);
        	break;
        case OIS::KC_DOWN:
        	torque = torque * Ogre::Quaternion(-torqueVertical, Ogre::Vector3::UNIT_X);
        	break;
        case OIS::KC_RIGHT:
        	torque = torque * Ogre::Quaternion(torqueVertical, Ogre::Vector3::UNIT_Y);
        	break;
        default:
          return false;
        }
        return true;
    }
}
