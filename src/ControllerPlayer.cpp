#include "ControllerPlayer.h"

ControllerPlayer::ControllerPlayer(OIS::InputManager* inputManager) :
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
    } else {
        this->mouse = NULL;
    }
    if(inputManager->getNumberOfDevices(OIS::OISJoyStick) > 0) {
        this->joystick = static_cast<OIS::JoyStick*>(
                inputManager->createInputObject(OIS::OISJoyStick, true));
        this->joystickState = joystick->getJoyStickState();
    } else {
        this->joystick = NULL;
    }

}

ControllerPlayer::~ControllerPlayer() {
    if(map != NULL) { delete map; }
    if(keyboard != NULL) { inputManager->destroyInputObject(keyboard); keyboard = NULL; }
    if(mouse != NULL) { inputManager->destroyInputObject(mouse); mouse = NULL; }
    if(joystick != NULL) { inputManager->destroyInputObject(joystick); joystick = NULL; }
}

void ControllerPlayer::control(Actionable* actor) {
    this->actor = actor;
    if(this->keyboard != NULL) { this->keyboard->setEventCallback(this); }
    if(this->mouse != NULL) { this->mouse->setEventCallback(this); }
    if(this->joystick != NULL) { this->joystick->setEventCallback(this); }
}

void ControllerPlayer::release() {
    this->keyboard->setEventCallback(NULL);
    this->mouse->setEventCallback(NULL);
    this->joystick->setEventCallback(NULL);
}

/**
 * Use the specified keymap to translate events into actions.
 *
 * The old keymap, either default or previously specified, will be deleted.
 *
 * @param keymap
 *     The new keymap to use.
 */
void ControllerPlayer::setKeymap(Keymap* keymap) {
    if(this->map != NULL) { delete this->map; }
    this->map = map;
}

/**
 * Update the state of this object after a game timestep.
 *
 * Captures events from input devices.
 */
bool ControllerPlayer::update(Ogre::Real deltaTime) {
    if(keyboard != NULL) {
        this->keyboard->capture();
    }
    if(joystick != NULL) {
        this->joystick->capture();
    }
    return true;
}

bool ControllerPlayer::keyPressed(const OIS::KeyEvent& event) {
    ButtonAction action;
    action = map->kb.getButtonAction(event.key);
    return PERFORM(actor, action)(true);
}

bool ControllerPlayer::keyReleased(const OIS::KeyEvent& event) {
    ButtonAction action;
    action = map->kb.getButtonAction(event.key);
    return PERFORM(actor, action)(false);
}

bool ControllerPlayer::mouseMoved(const OIS::MouseEvent& event) {
    return false;
}

bool ControllerPlayer::mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID id) {
    ButtonAction action;
    action = map->ms.getButtonAction(id);
    return PERFORM(actor, action)(true);
}

bool ControllerPlayer::mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID id) {
    ButtonAction action;
    action = map->ms.getButtonAction(id);
    return PERFORM(actor, action)(false);
}

#define JS_DEADZONE 500
bool ControllerPlayer::axisMoved(const OIS::JoyStickEvent& event, int axis) {
    AxisAction action = map->js.getAxisAction(axis);
    int old = joystickState.mAxes[axis].abs;
    int abs = event.state.mAxes[axis].abs;
    joystickState = event.state;

    if(abs < JS_DEADZONE && abs > -JS_DEADZONE) {
        abs = 0;
        joystickState.mAxes[axis].abs = 0;
    }

    return PERFORM(actor, action)(old, abs);
}

bool ControllerPlayer::buttonPressed(const OIS::JoyStickEvent& event, int button) {
    ButtonAction action;
    action = map->js.getButtonAction(button);
    return PERFORM(actor, action)(true);
}

bool ControllerPlayer::buttonReleased(const OIS::JoyStickEvent& event, int button) {
    return false;
}

bool ControllerPlayer::povMoved(const OIS::JoyStickEvent& event, int index) {
    return false;
}

bool ControllerPlayer::sliderMoved(const OIS::JoyStickEvent& event, int index) {
    return false;
}

bool ControllerPlayer::vector3Moved(const OIS::JoyStickEvent& event, int index) {
    return false;
}

