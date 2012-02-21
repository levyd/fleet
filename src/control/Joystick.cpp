#include "Joystick.h"

Joystick::Joystick(OIS::JoyStick* js) : joystick(js) {
    this->joystickState = js->getJoyStickState();
    this->map = NULL;
}

Joystick::~Joystick() {
    this->release();
}

void Joystick::setKeymap(JoystickMap* jsMap) {
    this->map = jsMap;
}

void Joystick::control(Actionable* actor) {
    this->actor = actor;
    this->joystick->setEventCallback(this);
}

void Joystick::release() {
    this->joystick->setEventCallback(NULL);
    this->actor = NULL;
}

bool Joystick::update(Ogre::Real deltaTime) {
    this->joystick->capture();
    return true;
}

OIS::JoyStick* Joystick::getInputObject() {
    return joystick;
}

#define JS_DEADZONE 500
bool Joystick::axisMoved(const OIS::JoyStickEvent& event, int axis) {
    if(this->map == NULL) { return false; }
    AxisAction action = map->getAxisAction(axis);
    int old = joystickState.mAxes[axis].abs;
    int abs = event.state.mAxes[axis].abs;
    this->joystickState = event.state;

    if(abs < JS_DEADZONE && abs > -JS_DEADZONE) {
        abs = 0;
        this->joystickState.mAxes[axis].abs = 0;
    }

    return PERFORM(actor, action)(old, abs);
}

bool Joystick::buttonPressed(const OIS::JoyStickEvent& event, int button) {
    ButtonAction action;
    action = map->getButtonAction(button);
    return PERFORM(actor, action)(true);
}

bool Joystick::buttonReleased(const OIS::JoyStickEvent& event, int button) {
    ButtonAction action;
    action = map->getButtonAction(button);
    return PERFORM(actor, action)(false);
}

bool Joystick::povMoved(const OIS::JoyStickEvent& event, int index) {
    return false;
}

bool Joystick::sliderMoved(const OIS::JoyStickEvent& event, int index) {
    return false;
}

bool Joystick::vector3Moved(const OIS::JoyStickEvent& event, int index) {
    return false;
}

