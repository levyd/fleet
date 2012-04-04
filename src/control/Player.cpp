#include "Player.h"
#include "../util/Console.h"

/**
 * Constructs a Player object.
 *
 * A Player is constructed with a keyboard, a mouse, and as many Joystick as
 * @a inputManager has detected.
 * 
 * A default Keymap is constructed and used.
 *
 * @param inputManager
 *     The OIS::InputManager to obtain InputObjects from.
 */
Player::Player(OIS::InputManager* inputManager) : inputManager(inputManager) {
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
    for(int i = 0; i < inputManager->getNumberOfDevices(OIS::OISJoyStick); i++) {
        OIS::JoyStick* js = static_cast<OIS::JoyStick*>(
                inputManager->createInputObject(OIS::OISJoyStick, true));
        Joystick* joystick = new Joystick(js);
        joysticks.push_back(joystick);
    }

    this->map = new Keymap();
    this->setKeymap(this->map);
}

Player::~Player() {
    if(map != NULL) { delete map; }
    if(keyboard != NULL) { inputManager->destroyInputObject(keyboard); keyboard = NULL; }
    if(mouse != NULL) { inputManager->destroyInputObject(mouse); mouse = NULL; }
    for(unsigned i = 0; i < joysticks.size(); i++) {
        inputManager->destroyInputObject(joysticks[i]->getInputObject());
    }
}

/**
 * Begin controlling the specified @a actor.
 *
 * Input events from this Player's devices will begin to call the action
 * handlers of the specified @a actor.
 *
 * You may also want to specify a {@link Keymap} for this Player with
 * Player::setKeymap().
 *
 * @param actor
 *     The actor to begin controlling.
 */
void Player::control(Actionable* actor) {
    this->actor = actor;
    if(this->keyboard != NULL) { this->keyboard->setEventCallback(this); }
    if(this->mouse != NULL) { this->mouse->setEventCallback(this); }
    for(unsigned i = 0; i < joysticks.size(); i++) {
        joysticks[i]->control(actor);
    }
}

/**
 * Stop controlling this Player's current Player::actor.
 *
 * Input events from this Player's devices will no longer call the action
 * handlers of this Player's Player::actor.
 */
void Player::release() {
    if(this->keyboard != NULL) { this->keyboard->setEventCallback(NULL); }
    if(this->mouse != NULL) { this->mouse->setEventCallback(NULL); }
    for(unsigned i = 0; i < joysticks.size(); i++) {
        joysticks[i]->release();
    }
}

/**
 * Use the specified {@link Keymap} to translate events into actions.
 *
 * @param keymap
 *     The new keymap to use.
 * @return
 *     The keymap that was in use prior to this function. The caller might use
 *     the old keymap elsewhere, or delete it.
 */
Keymap* Player::setKeymap(Keymap* keymap) {
    Keymap* old = this->map;
    this->map = keymap;
    for(unsigned i = 0; i < joysticks.size() && i < this->map->js.size(); i++) {
        joysticks[i]->setKeymap(this->map->js[i]);
    }
    return old;
}

/**
 * Update the state of this object after a game timestep.
 *
 * Captures events from input devices.
 *
 * @param deltaTime
 *     The interval of time that has passed since the last update.
 */
bool Player::update(Ogre::Real deltaTime) {
    if(keyboard != NULL) {
        this->keyboard->capture();
    }
    bool status = true;
    for(unsigned i = 0; i < joysticks.size(); i++) {
        status = status && joysticks[i]->update(deltaTime);
    }
    return status;
}

bool Player::keyPressed(const OIS::KeyEvent& event) {
    OgreConsole::getSingleton().onKeyPressed(event);
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

