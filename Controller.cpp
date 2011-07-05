#include "Controller.h"

namespace Controller {
    static OIS::InputManager* inputMgr;

    void BuildInputManager(Ogre::RenderWindow* window) {
        size_t windowHandle = 0;
        window->getCustomAttribute("WINDOW", &windowHandle);
        inputMgr = OIS::InputManager::createInputSystem(windowHandle);
    }

    Controller::Controller() {
    }

    Controller::~Controller() {
    }

    Thrust::Thrust(Ogre::Real fwd, Ogre::Real rev, Ogre::Real lat, Ogre::Real rot)
    : Controller(), thrust(0, 0, 0), torque(0, 0) {
    	keyboard = static_cast<OIS::Keyboard*>(inputMgr->createInputObject(OIS::OISKeyboard, true));
        //Mouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
        keyboard->setEventCallback(this);
        //mouse.setEventCallback(this);
    }

    Thrust::~Thrust() {
    }

    bool Thrust::Update(Ogre::Real deltaTime) {
        keyboard->capture();
        return true;
    }

    bool Thrust::keyPressed(const OIS::KeyEvent& event) {
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
    bool Thrust::keyReleased(const OIS::KeyEvent& event) {
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

