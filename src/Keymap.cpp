#include "Keymap.h"

KeyboardMap::KeyboardMap() {
    for(int i = 0; i < NUM_KB_BUTTONS; i++) {
        this->buttonActions[i] = &Actionable::actionDefault;
    }
}

void KeyboardMap::setButtonAction(OIS::KeyCode id, ButtonAction action) {
    this->buttonActions[id] = action;
}

const ButtonAction KeyboardMap::getButtonAction(OIS::KeyCode id) {
    return this->buttonActions[id];
}

MouseMap::MouseMap() {
    for(int i = 0; i < NUM_MS_BUTTONS; i++) {
        this->buttonActions[i] = &Actionable::actionDefault;
    }
    for(int i = 0; i < NUM_MS_AXIS; i++) {
        this->axisActions[i] = &Actionable::actionDefault;
    }
}

void MouseMap::setAxisAction(enum MouseAxis id, AxisAction action) {
    this->axisActions[id] = action;
}

const AxisAction MouseMap::getAxisAction(enum MouseAxis id) {
    return this->axisActions[id];
}

void MouseMap::setButtonAction(OIS::MouseButtonID id, ButtonAction action) {
    this->buttonActions[id] = action;
}

const ButtonAction MouseMap::getButtonAction(OIS::MouseButtonID id) {
    return this->buttonActions[id];
}

JoystickMap::JoystickMap() {
    for(int i = 0; i < NUM_JS_BUTTONS; i++) {
        this->buttonActions[i] = &Actionable::actionDefault;
    }
    for(int i = 0; i < NUM_JS_AXIS; i++) {
        this->axisActions[i] = &Actionable::actionDefault;
    }
}
void JoystickMap::setAxisAction(enum JoystickAxis id, AxisAction action) {
    this->axisActions[id] = action;
}

const AxisAction JoystickMap::getAxisAction(enum JoystickAxis id) {
    return this->axisActions[id];
}

void JoystickMap::setButtonAction(int id, ButtonAction action) {
    this->buttonActions[id] = action;
}

const ButtonAction JoystickMap::getButtonAction(int id) {
    return this->buttonActions[id];
}

/**
 * Construct a keymap from an xml file.
 */
Keymap::Keymap(const std::string file) {
    // Not implemented!
}

/**
 * Build the default keymap.
 */
Keymap::Keymap() {
    this->kb.setButtonAction(OIS::KC_W, &Actionable::actionThrustForward);
    this->kb.setButtonAction(OIS::KC_A, &Actionable::actionThrustLeft);
    this->kb.setButtonAction(OIS::KC_S, &Actionable::actionThrustReverse);
    this->kb.setButtonAction(OIS::KC_D, &Actionable::actionThrustRight);
    this->kb.setButtonAction(OIS::KC_Q, &Actionable::actionThrustDown);
    this->kb.setButtonAction(OIS::KC_E, &Actionable::actionThrustUp);

    this->kb.setButtonAction(OIS::KC_NUMPAD2, &Actionable::actionPitchUp);
    this->kb.setButtonAction(OIS::KC_NUMPAD4, &Actionable::actionYawLeft);
    this->kb.setButtonAction(OIS::KC_NUMPAD6, &Actionable::actionYawRight);
    this->kb.setButtonAction(OIS::KC_NUMPAD7, &Actionable::actionRollLeft);
    this->kb.setButtonAction(OIS::KC_NUMPAD8, &Actionable::actionPitchDown);
    this->kb.setButtonAction(OIS::KC_NUMPAD9, &Actionable::actionRollRight);
}
