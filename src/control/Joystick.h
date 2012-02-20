#include <OISEvents.h>
#include <OISJoyStick.h>
#include "Controller.h"
#include "Keymap.h"

class Joystick : public Controller, public OIS::JoyStickListener {
public:
    Joystick(OIS::JoyStick* js);
    virtual ~Joystick();

    void setKeymap(JoystickMap* jsMap);
    void control(Actionable* actor);
    void release();
    bool update(Ogre::Real deltaTime);

    OIS::JoyStick* getInputObject();

    virtual bool axisMoved(const OIS::JoyStickEvent& event, int axis);
    virtual bool buttonPressed(const OIS::JoyStickEvent& event, int button);
    virtual bool buttonReleased(const OIS::JoyStickEvent& event, int button);
    virtual bool povMoved(const OIS::JoyStickEvent& event, int index);
    virtual bool sliderMoved(const OIS::JoyStickEvent& event, int index);
    virtual bool vector3Moved(const OIS::JoyStickEvent& event, int index);

private:
    JoystickMap* map;
    OIS::JoyStick* joystick;
    OIS::JoyStickState joystickState;
};
