#include <OgreMath.h>
#include <OISInputManager.h>
#include <OISEvents.h>
#include <OISJoyStick.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "Controller.h"
#include "Keymap.h"

// INPUT MANAGER!!
// Not, 'control', 'addListener'! (with filter?)
class ControllerPlayer : public Controller, public OIS::KeyListener,
    public OIS::MouseListener, public OIS::JoyStickListener {
public:
    ControllerPlayer(OIS::InputManager* inputManager);
    ControllerPlayer();
    virtual ~ControllerPlayer();

    void control(Actionable* actor);
    void release();
    void setKeymap(Keymap* keymap);
    bool update(Ogre::Real deltaTime);

protected:
    Actionable* actor;
    Keymap* map;

    OIS::InputManager* inputManager;
    OIS::Keyboard* keyboard;
    OIS::Mouse* mouse;
    OIS::JoyStick* joystick;

    virtual bool keyPressed(const OIS::KeyEvent& event);
    virtual bool keyReleased(const OIS::KeyEvent& event);

    virtual bool mouseMoved(const OIS::MouseEvent& event);
    virtual bool mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID id);

    virtual bool axisMoved(const OIS::JoyStickEvent& event, int axis);
    virtual bool buttonPressed(const OIS::JoyStickEvent& event, int button);
    virtual bool buttonReleased(const OIS::JoyStickEvent& event, int button);
    virtual bool povMoved(const OIS::JoyStickEvent& event, int index);
    virtual bool sliderMoved(const OIS::JoyStickEvent& event, int index);
    virtual bool vector3Moved(const OIS::JoyStickEvent& event, int index);
};

