#include "Player.h"

Player::Player(OIS::InputManager* inputManager) :
    inputManager(inputManager) {
    // Default keymap
    this->map = new Keymap();

    if(inputManager->getNumberOfDevices(OIS::OISKeyboard) > 0) {
        this->keyboard = static_cast<OIS::Keyboard*>(
                inputManager->createInputObject(OIS::OISKeyboard, true));
    } else {
        this->keyboard = NULL;
    }

    if(inputManager->getNumberOfDevices(OIS::OISMouse) > 0) {
        //this->mouse = static_cast<OIS::Mouse*>(
        //        inputManager->createInputObject(OIS::OISMouse, true));
        this->mouse = NULL;
    } else {
        this->mouse = NULL;
    }
    if(inputManager->getNumberOfDevices(OIS::OISJoyStick) > 0) {
        OIS::JoyStick* js = static_cast<OIS::JoyStick*>(
                inputManager->createInputObject(OIS::OISJoyStick, true));
        this->joystick = new Joystick(js);
        this->joystick->setKeymap(&(this->map->js));
    } else {
        this->joystick = NULL;
    }

}

Player::~Player() {
    if(map != NULL) { delete map; }
    if(keyboard != NULL) { inputManager->destroyInputObject(keyboard); keyboard = NULL; }
    if(mouse != NULL) { inputManager->destroyInputObject(mouse); mouse = NULL; }
    inputManager->destroyInputObject(joystick->getInputObject());
}

void Player::control(Actionable* actor) {
    this->actor = actor;
    if(this->keyboard != NULL) { this->keyboard->setEventCallback(this); }
    if(this->mouse != NULL) { this->mouse->setEventCallback(this); }
    this->joystick->control(actor);
}

void Player::release() {
    this->keyboard->setEventCallback(NULL);
    this->mouse->setEventCallback(NULL);
    this->joystick->release();
}

/**
 * Use the specified keymap to translate events into actions.
 *
 * @param keymap
 *     The new keymap to use.
 */
void Player::setKeymap(Keymap* keymap) {
    this->map = keymap;
    this->joystick->setKeymap(&(this->map->js));
}

/**
 * Update the state of this object after a game timestep.
 *
 * Captures events from input devices.
 */
bool Player::update(Ogre::Real deltaTime) {
    if(keyboard != NULL) {
        this->keyboard->capture();
    }
    return joystick->update(deltaTime);
}

bool Player::keyPressed(const OIS::KeyEvent& event) {
    ButtonAction action;
    action = map->kb.getButtonAction(event.key);
    return PERFORM(actor, action)(true);
}

bool Player::keyReleased(const OIS::KeyEvent& event) {
    ButtonAction action;
    action = map->kb.getButtonAction(event.key);
    return PERFORM(actor, action)(false);
}

bool Player::mouseMoved(const OIS::MouseEvent& event) {
    return false;
}

bool Player::mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID id) {
    ButtonAction action;
    action = map->ms.getButtonAction(id);
    return PERFORM(actor, action)(true);
}

bool Player::mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID id) {
    ButtonAction action;
    action = map->ms.getButtonAction(id);
    return PERFORM(actor, action)(false);
}

