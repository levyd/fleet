#include "ThrustController.h"

namespace Controller {
    Thrust::Thrust(Entity* body)
        : Controller(), body(body),
          thrust(0, 0, 0), torque(Ogre::Quaternion::IDENTITY),
          thrustForward(0), thrustReverse(0), thrustLateral(0),
          torqueYaw(0), torquePitch(0), torqueRoll(0),
          torqueX(0), torqueY(0), torqueZ(0) {
    }

    Thrust::~Thrust() {
    }

    void Thrust::setMovementSpeeds(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat) {
        thrustForward = fwd;
        thrustReverse = rev;
        thrustLateral = lat;
    }

    void Thrust::setRotationSpeeds(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Radian roll) {
        torqueYaw = yaw;
        torquePitch = pitch;
        torqueRoll = roll;
    }

    void Thrust::setTorque() {
        torque = Ogre::Quaternion(torqueX, Ogre::Vector3::UNIT_X)
               * Ogre::Quaternion(torqueY, Ogre::Vector3::UNIT_Y)
               * Ogre::Quaternion(torqueZ, Ogre::Vector3::UNIT_Z);
    }
    //--------------------------------------------------------------------------
    ThrustPlayer::ThrustPlayer(Entity* body, OIS::Keyboard*& kb) \
        : Thrust(body), keyboard(kb) {
        keyboard->setEventCallback(this);
    }

    ThrustPlayer::~ThrustPlayer() {
    }

    bool ThrustPlayer::update(Ogre::Real deltaTime) {
        keyboard->capture();
        return true;
    }

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
            break;
        }
        setTorque();
        return true;
    }

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
            break;
        }
        setTorque();
        return true;
    }
    //--------------------------------------------------------------------------
    ThrustAI::ThrustAI(Entity* body) : Thrust(body) {
    	timer = 5;
    }

    ThrustAI::~ThrustAI() {
    }

    bool ThrustAI::update(Ogre::Real deltaTime) {
    	if(timer > 0) {
    	    timer -= deltaTime;
    	    thrust.x = 100;
    	} else {
    		thrust.x = 0;
    	}
    	return true;
    }
}
