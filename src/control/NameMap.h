#ifndef _NAMEMAP_H_
#define _NAMEMAP_H_
#include <string>

#include <OISJoyStick.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "../entity/Actionable.h"

/**
 * Translates a string into a keycode.
 *
 * Translates the name of a keyboard button into the corresponding OIS::KeyCode.
 * e.g. translates "w" into OIS::KC_W.
 *
 * It is intended that the class KeyboardMap instantiates a private static
 * KeyNameMap object.
 */
class KeyNameMap {
public:
    KeyNameMap();

    OIS::KeyCode getKeyCode(std::string name);

private:
    std::map<std::string, OIS::KeyCode> keyCodes;
};

/**
 * Translates a string into a joystick ID.
 *
 * Translates the name of a keyboard button into the corresponding joystick axis
 * or button ID. e.g. translates "Z" into 2.
 *
 * It is intended that the class JoystickMap instantiates a private static
 * JoystickNameMap object.
 */
class JoystickNameMap {
public:
    JoystickNameMap();

    int getAxisID(std::string);
    int getButtonID(std::string);

private:
    std::map<std::string, int> axisIDs;
    std::map<std::string, int> buttonIDs;
};

/**
 * Translates a string into an action.
 *
 * Provides methods to translate the name of an action into a reference to the
 * function that implements that action. e.g. translates "forward-thrust" into
 * &Actionable::actionThrustForward.
 *
 * It is intended that the class Keymap instantiates a private static
 * ActionNameMap object.
 */
class ActionNameMap {
public:
    ActionNameMap();

    ButtonAction getButtonAction(std::string name);
    AxisAction getAxisAction(std::string name);

private:
    std::map<std::string, ButtonAction> buttonActions;
    std::map<std::string, AxisAction> axisActions;
};

#endif
