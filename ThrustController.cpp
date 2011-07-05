#include "ThrustController.h"

namespace Controller {
    Thrust::Thrust(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat, Ogre::Real rot)
        : Controller(), thrust(0, 0, 0), torque(0, 0) {
    }
    //--------------------------------------------------------------------------
    Thrust::~Thrust() {
    }
    //--------------------------------------------------------------------------
    ThrustPlayer::ThrustPlayer(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat, Ogre::Real rot, \
        OIS::OISKeyboard kb) : Thrust(fwd, rev, lat, rot) {
        keyboard = kb;
        keyboard->setEventCallback(this);
    }
    //--------------------------------------------------------------------------
    Thrust::~ThrustPlayer() {
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
            thrust.x += maxForward;
            break;
        case OIS::KC_A:
            thrust.z -= maxLateral;
            break;
        case OIS::KC_S:
            thrust.x -= maxReverse;
            break;
        case OIS::KC_D:
            thrust.z += maxLateral;
            break;
        case OIS::KC_UP:
            torque.x += maxRotation;
            break;
        case OIS::KC_LEFT:
            torque.y += maxRotation;
            break;
        case OIS::KC_DOWN:
            torque.x -= maxRotation;
            break;
        case OIS::KC_RIGHT:
            torque.y -= maxRotation;
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
            torque.x -= maxRotation;
            break;
        case OIS::KC_LEFT:
            torque.y -= maxRotation;
            break;
        case OIS::KC_DOWN:
            torque.x += maxRotation;
            break;
        case OIS::KC_RIGHT:
            torque.y += maxRotation;
            break;
        default:
          return false;
        }
        return true;
    }
}
