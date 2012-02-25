#ifndef _KEYMAP_H_
#define _KEYMAP_H_
#include <string>

#include <OISJoyStick.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "../entity/Actionable.h"
#include "NameMap.h"
#include "../util/Xml.h"

#define NUM_KB_BUTTONS 0xFF

class KeyboardMap {
public:
    KeyboardMap();
    KeyboardMap(XmlNode xml);
    void setButtonAction(OIS::KeyCode id, ButtonAction action);
    const ButtonAction getButtonAction(OIS::KeyCode id);

private:
    static KeyNameMap keyNames;

    ButtonAction buttonActions[NUM_KB_BUTTONS];
};

#define NUM_MS_BUTTONS 0x07
enum MouseAxis { MS_X, MS_Y, MS_Z, NUM_MS_AXIS };

class MouseMap {
public:
    MouseMap();
    void setAxisAction(enum MouseAxis axis, AxisAction action);
    const AxisAction getAxisAction(enum MouseAxis axis);
    void setButtonAction(OIS::MouseButtonID id, ButtonAction action);
    const ButtonAction getButtonAction(OIS::MouseButtonID id);

private:
    AxisAction axisActions[NUM_MS_AXIS];
    ButtonAction buttonActions[NUM_MS_BUTTONS];
};

#define NUM_JS_BUTTONS 0x20
enum JoystickAxis { JS_X, JS_Y, JS_Z, JS_R, JS_S, JS_T, NUM_JS_AXIS };

class JoystickMap {
public:
    JoystickMap();
    JoystickMap(XmlNode xml);
    void setAxisAction(int id, AxisAction action);
    const AxisAction getAxisAction(int id);
    void setButtonAction(int id, ButtonAction action);
    const ButtonAction getButtonAction(int id);

private:
    static JoystickNameMap joystickNames;

    AxisAction axisActions[NUM_JS_AXIS];
    ButtonAction buttonActions[NUM_JS_BUTTONS];
};

#define MAX_NUM_JS 4
class Keymap {
    friend class KeyboardMap;
    friend class MouseMap;
    friend class JoystickMap;
public:
    Keymap();
    Keymap(const std::string filename);

    KeyboardMap kb;
    MouseMap ms;
    std::vector<JoystickMap*> js;

private:
    static ActionNameMap actionNames;
};

#endif

