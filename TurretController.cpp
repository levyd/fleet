#include "TurretController.h"

#include <OgreStringConverter.h>

namespace Controller {
    Turret::Turret(Ogre::SceneNode* bodyNode, Ogre::Vector3 offset, Ogre::Quaternion rotation)
        : Controller(),
        rotationX(0), rotationY(0) {
        trackingSpeed = Ogre::Radian(Ogre::Degree(90));
        baseNode = bodyNode->createChildSceneNode(offset, rotation);
        turretNode = baseNode->createChildSceneNode(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
    }

    Turret::~Turret() {
    }
    //--------------------------------------------------------------------------
    TurretPlayer::TurretPlayer(Ogre::SceneNode* bodyNode, Ogre::Vector3 offset, Ogre::Quaternion rotation, OIS::Keyboard* kb, Ogre::Camera* camera)
        : Turret(bodyNode, offset, rotation), keyboard(kb) {
        keyboard->setEventCallback(this);
    	turretNode->attachObject(camera);
    }

    TurretPlayer::~TurretPlayer() {
    }

    bool TurretPlayer::Update(Ogre::Real deltaTime) {
    	keyboard->capture();
    	baseNode->rotate(Ogre::Vector3::UNIT_X, deltaTime * rotationY);
    	baseNode->rotate(Ogre::Vector3::UNIT_Y, deltaTime * rotationX);
    	return true;
    }

    bool TurretPlayer::keyPressed(const OIS::KeyEvent& event) {
        switch(event.key) {
        case OIS::KC_DOWN:
        case OIS::KC_NUMPAD2:
        case OIS::KC_NUMPAD5:
        	rotationY -= trackingSpeed;
        	break;
        case OIS::KC_NUMPAD4:
        	rotationX += trackingSpeed;
        	break;
        case OIS::KC_NUMPAD6:
        	rotationX -= trackingSpeed;
        	break;
        case OIS::KC_NUMPAD8:
        	rotationY += trackingSpeed;
        	break;
        default:
        	return false;
        }
    	return true;
    }

    bool TurretPlayer::keyReleased(const OIS::KeyEvent& event) {
    	switch(event.key) {
    	case OIS::KC_DOWN:
        case OIS::KC_NUMPAD2:
        case OIS::KC_NUMPAD5:
        	rotationY += trackingSpeed;
        	break;
        case OIS::KC_NUMPAD4:
        	rotationX -= trackingSpeed;
        	break;
        case OIS::KC_NUMPAD6:
        	rotationX += trackingSpeed;
        	break;
        case OIS::KC_NUMPAD8:
        	rotationY -= trackingSpeed;
        	break;
        default:
        	return false;
    	}
    	return true;
    }
    //--------------------------------------------------------------------------
    TurretAI::TurretAI(Ogre::SceneNode* bodyNode, Ogre::Vector3 offset, Ogre::Quaternion rotation)
        : Turret(bodyNode, offset, rotation) {
    }

    TurretAI::~TurretAI() {
    }

    bool TurretAI::Update(Ogre::Real deltaTime) {
    	return true;
    }
}

