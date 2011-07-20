#include "ThrustController.h"

namespace Controller {
    Thrust::Thrust(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat, Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Radian roll)
        : Controller(),
          thrust(0, 0, 0),
          torqueX(0), torqueY(0), torqueZ(0),
          thrustForward(fwd),
          thrustReverse(rev),
          thrustLateral(lat),
          torqueYaw(yaw),
          torquePitch(pitch),
          torqueRoll(roll) {
    }
    //--------------------------------------------------------------------------
    Thrust::~Thrust() {
    }
    //--------------------------------------------------------------------------
    ThrustPlayer::ThrustPlayer(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat, Ogre::Radian yaw, \
        Ogre::Radian pitch, Ogre::Radian roll, OIS::Keyboard* kb)
        : Thrust(fwd, rev, lat, yaw, pitch, roll) {
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
        case OIS::KC_DOWN:
        case OIS::KC_NUMPAD2:
        case OIS::KC_NUMPAD5:
        	torqueX = torqueX - torquePitch;
        	break;
        case OIS::KC_LEFT:
        case OIS::KC_NUMPAD4:
        	torqueY = torqueY - torqueYaw;
        	break;
        case OIS::KC_RIGHT:
        case OIS::KC_NUMPAD6:
        	torqueY = torqueY + torqueYaw;
        	break;
        case OIS::KC_NUMPAD7:
        	torqueZ = torqueZ - torqueRoll;
        	break;
        case OIS::KC_UP:
        case OIS::KC_NUMPAD8:
        	torqueX = torqueX + torquePitch;
        	break;
        case OIS::KC_NUMPAD9:
        	torqueZ = torqueZ + torqueRoll;
        	break;
        case OIS::KC_SPACE:
        	thrust = Ogre::Vector3::ZERO;
        	torqueX = 0;
        	torqueY = 0;
        	torqueZ = 0;
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
        case OIS::KC_DOWN:
        case OIS::KC_NUMPAD2:
        case OIS::KC_NUMPAD5:
        	torqueX = torqueX + torquePitch;
        	break;
        case OIS::KC_LEFT:
        case OIS::KC_NUMPAD4:
        	torqueY = torqueY + torqueYaw;
        	break;
        case OIS::KC_RIGHT:
        case OIS::KC_NUMPAD6:
        	torqueY = torqueY - torqueYaw;
        	break;
        case OIS::KC_NUMPAD7:
        	torqueZ = torqueZ + torqueRoll;
        	break;
        case OIS::KC_UP:
        case OIS::KC_NUMPAD8:
        	torqueX = torqueX - torquePitch;
        	break;
        case OIS::KC_NUMPAD9:
        	torqueZ = torqueZ - torqueRoll;
        	break;
        default:
          return false;
        }
        return true;
    }

    ThrustAI::ThrustAI(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat, Ogre::Radian yaw, \
    		Ogre::Radian pitch, Ogre::Radian roll) : Thrust(fwd, rev, lat, yaw, pitch, roll) {
    	timer = 5;
    }

    ThrustAI::~ThrustAI() {
    }

    bool ThrustAI::Update(Ogre::Real deltaTime) {
    	if(timer > 0) {
    	    timer -= deltaTime;
    	    thrust.x = 100;
    	} else {
    		thrust.x = 0;
    	}
    	return true;
    }
}
