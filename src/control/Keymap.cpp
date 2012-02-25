#include <iostream>
#include <algorithm>
#include "Keymap.h"

KeyNameMap KeyboardMap::keyNames;

KeyboardMap::KeyboardMap() {
    for(int i = 0; i < NUM_KB_BUTTONS; i++) {
        this->buttonActions[i] = &Actionable::actionDefault;
    }
}

KeyboardMap::KeyboardMap(XmlNode xml) {
    for(int i = 0; i < NUM_KB_BUTTONS; i++) {
        this->buttonActions[i] = &Actionable::actionDefault;
    }
    std::vector<XmlNode>::iterator i;

    std::vector<XmlNode>* buttonNodes = xml.getChildren("button");
    for(i = buttonNodes->begin(); i < buttonNodes->end(); ++i) {
        std::string buttonName = i->getAttribute("value");
        OIS::KeyCode button = KeyboardMap::keyNames.getKeyCode(buttonName);
        if(button == OIS::KC_UNASSIGNED) { continue; }
        std::string actionName = i->getChild("action").getAttribute("value");
        ButtonAction action = Keymap::actionNames.getButtonAction(actionName);
        if(action == (ButtonAction)&Actionable::actionDefault) { continue; }
        this->buttonActions[button] = action;
    }
    buttonNodes->clear();
    delete buttonNodes;
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

JoystickNameMap JoystickMap::joystickNames;

JoystickMap::JoystickMap() {
    for(int i = 0; i < NUM_JS_BUTTONS; i++) {
        this->buttonActions[i] = &Actionable::actionDefault;
    }
    for(int i = 0; i < NUM_JS_AXIS; i++) {
        this->axisActions[i] = &Actionable::actionDefault;
    }
}

JoystickMap::JoystickMap(XmlNode xml) {
    for(int i = 0; i < NUM_JS_BUTTONS; i++) {
        this->buttonActions[i] = &Actionable::actionDefault;
    }
    for(int i = 0; i < NUM_JS_AXIS; i++) {
        this->axisActions[i] = &Actionable::actionDefault;
    }
    std::vector<XmlNode>::iterator i;

    std::vector<XmlNode>* axisNodes = xml.getChildren("axis");
    for(i = axisNodes->begin(); i < axisNodes->end(); ++i) {
        std::string axisName = i->getAttribute("value");
        int axis = JoystickMap::joystickNames.getAxisID(axisName);
        if(axis == -1) { continue; }
        std::string actionName = i->getChild("action").getAttribute("value");
        AxisAction action = Keymap::actionNames.getAxisAction(actionName);
        if(action == (AxisAction)&Actionable::actionDefault) { continue; }
        this->axisActions[axis] = action;
    }
    axisNodes->clear();
    delete axisNodes;

    std::vector<XmlNode>* buttonNodes = xml.getChildren("button");
    for(i = buttonNodes->begin(); i < buttonNodes->end(); ++i) {
        std::string buttonName = i->getAttribute("value");
        int button = JoystickMap::joystickNames.getButtonID(buttonName);
        if(button == -1) { continue; }
        std::string actionName = i->getChild("action").getAttribute("value");
        ButtonAction action = Keymap::actionNames.getButtonAction(actionName);
        if(action == (ButtonAction)&Actionable::actionDefault) { continue; }
        this->buttonActions[button] = action;
    }
    buttonNodes->clear();
    delete buttonNodes;
}

void JoystickMap::setAxisAction(int id, AxisAction action) {
    this->axisActions[id] = action;
}

const AxisAction JoystickMap::getAxisAction(int id) {
    return this->axisActions[id];
}

void JoystickMap::setButtonAction(int id, ButtonAction action) {
    this->buttonActions[id] = action;
}

const ButtonAction JoystickMap::getButtonAction(int id) {
    return this->buttonActions[id];
}

ActionNameMap Keymap::actionNames;

/**
 * Constructs an empty keymap.
 */
Keymap::Keymap() {
}

/**
 * Construct a Keymap from an XML file.
 *
 * This constructor delegates the task of interpreting a device subtree to the
 * appropriate device constructor.
 *
 * @param filename
 *     The path to the XML file that will be interpreted.
 */
Keymap::Keymap(std::string filename) {
    XmlDocument xml(filename);
    std::vector<XmlNode>* devices = xml.getRootNode("keymap").getChildren("device");
    std::vector<XmlNode>::iterator device;
    for(device = devices->begin(); device < devices->end(); ++device) {
        std::string typeName = device->getAttribute("type");
        std::transform(typeName.begin(), typeName.end(), typeName.begin(), tolower);
        if(typeName.compare("keyboard") == 0) {
            this->kb = KeyboardMap(*device);
        } else if(typeName.compare("joystick") == 0) {
            JoystickMap* jsMap = new JoystickMap(*device);
            this->js.push_back(jsMap);
        }
    }
    devices->clear();
    delete devices;
}

