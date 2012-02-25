#include "NameMap.h"
#include "Keymap.h"

KeyNameMap::KeyNameMap() {
    this->keyCodes["a"] = OIS::KC_A;
    this->keyCodes["b"] = OIS::KC_B;
    this->keyCodes["c"] = OIS::KC_C;
    this->keyCodes["d"] = OIS::KC_D;
    this->keyCodes["e"] = OIS::KC_E;
    this->keyCodes["q"] = OIS::KC_Q;
    this->keyCodes["s"] = OIS::KC_S;
    this->keyCodes["w"] = OIS::KC_W;

    this->keyCodes["numpad-0"] = OIS::KC_NUMPAD0;
    this->keyCodes["numpad-1"] = OIS::KC_NUMPAD1;
    this->keyCodes["numpad-2"] = OIS::KC_NUMPAD2;
    this->keyCodes["numpad-3"] = OIS::KC_NUMPAD3;
    this->keyCodes["numpad-4"] = OIS::KC_NUMPAD4;
    this->keyCodes["numpad-5"] = OIS::KC_NUMPAD5;
    this->keyCodes["numpad-6"] = OIS::KC_NUMPAD6;
    this->keyCodes["numpad-7"] = OIS::KC_NUMPAD7;
    this->keyCodes["numpad-8"] = OIS::KC_NUMPAD8;
    this->keyCodes["numpad-9"] = OIS::KC_NUMPAD9;
}

OIS::KeyCode KeyNameMap::getKeyCode(std::string name) {
    std::map<std::string, OIS::KeyCode>::iterator i;
    i = this->keyCodes.find(name);
    OIS::KeyCode kc = OIS::KC_UNASSIGNED;
    if(i != keyCodes.end()) {
        kc = i->second;
    }
    return kc;
}

JoystickNameMap::JoystickNameMap() {
    this->axisIDs["x"] = 0;
    this->axisIDs["y"] = 1;
    this->axisIDs["z"] = 2;

    this->buttonIDs["1"]  =  0;
    this->buttonIDs["2"]  =  1;
    this->buttonIDs["3"]  =  2;
    this->buttonIDs["4"]  =  3;
    this->buttonIDs["5"]  =  4;
    this->buttonIDs["6"]  =  5;
    this->buttonIDs["7"]  =  6;
    this->buttonIDs["8"]  =  7;
    this->buttonIDs["9"]  =  8;
    this->buttonIDs["10"] =  9;
    this->buttonIDs["11"] = 10;
    this->buttonIDs["12"] = 11;
}

int JoystickNameMap::getAxisID(std::string name) {
    std::map<std::string, int>::iterator i;
    i = this->axisIDs.find(name);
    int id = -1;
    if(i != axisIDs.end()) {
        id = i->second;
    }
    return id;
}

int JoystickNameMap::getButtonID(std::string name) {
    std::map<std::string, int>::iterator i;
    i = this->buttonIDs.find(name);
    int id = -1;
    if(i != buttonIDs.end()) {
        id = i->second;
    }
    return id;
}

ActionNameMap::ActionNameMap() {
    this->axisActions["thrust-forwardreverse"] = &Actionable::actionThrustForwardReverse;
    this->axisActions["thrust-leftright"] = &Actionable::actionThrustLeftRight;
    this->axisActions["thrust-updown"] = &Actionable::actionThrustUpDown;

    this->axisActions["yaw"] = &Actionable::actionYaw;
    this->axisActions["pitch"] = &Actionable::actionPitch;
    this->axisActions["roll"] = &Actionable::actionRoll;

    this->buttonActions["thrust-forward"] = &Actionable::actionThrustForward;
    this->buttonActions["thrust-reverse"] = &Actionable::actionThrustReverse;
    this->buttonActions["thrust-left"] = &Actionable::actionThrustLeft;
    this->buttonActions["thrust-right"] = &Actionable::actionThrustRight;
    this->buttonActions["thrust-up"] = &Actionable::actionThrustUp;
    this->buttonActions["thrust-down"] = &Actionable::actionThrustDown;

    this->buttonActions["yaw-left"] = &Actionable::actionYawLeft;
    this->buttonActions["yaw-right"] = &Actionable::actionYawRight;
    this->buttonActions["pitch-up"] = &Actionable::actionPitchUp;
    this->buttonActions["pitch-down"] = &Actionable::actionPitchDown;
    this->buttonActions["roll-left"] = &Actionable::actionRollLeft;
    this->buttonActions["roll-right"] = &Actionable::actionRollRight;
}

AxisAction ActionNameMap::getAxisAction(std::string name) {
    std::map<std::string, AxisAction>::iterator i;
    i = this->axisActions.find(name);
    AxisAction action = &Actionable::actionDefault;
    if(i != this->axisActions.end()) {
        action = i->second;
    }
    return action;
}

ButtonAction ActionNameMap::getButtonAction(std::string name) {
    std::map<std::string, ButtonAction>::iterator i;
    i = this->buttonActions.find(name);
    ButtonAction action = &Actionable::actionDefault;
    if(i != this->buttonActions.end()) {
        action = i->second;
    }
    return action;
}

