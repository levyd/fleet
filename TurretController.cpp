#include "TurretController.h"

namespace Controller {
    Turret::Turret() : Controller() {
    }

    Turret::~Turret() {
    }

    TurretPlayer::TurretPlayer(OIS::Keyboard* kb) : keyboard(kb) {
    }

    TurretPlayer::~TurretPlayer() {
    }

    bool TurretPlayer::Update(Ogre::Real deltaTime) {
    	return true;
    }

    bool TurretPlayer::keyPressed(const OIS::KeyEvent& event) {
    	return true;
    }

    bool TurretPlayer::keyReleased(const OIS::KeyEvent& event) {
    	return true;
    }

    TurretAI::TurretAI() {
    }

    TurretAI::~TurretAI() {
    }

    bool TurretAI::Update(Ogre::Real deltaTime) {
    	return true;
    }
}

