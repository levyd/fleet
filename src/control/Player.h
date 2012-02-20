#include <OgreMath.h>
#include <OISInputManager.h>
#include <OISEvents.h>
#include <OISJoyStick.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "Controller.h"
#include "Joystick.h"
#include "Keymap.h"

class Player : public Controller, public OIS::KeyListener,
    public OIS::MouseListener {
public:
    Player(OIS::InputManager* inputManager);
    Player();
    virtual ~Player();

    void control(Actionable* actor);
    void release();
    void setKeymap(Keymap* keymap);
    bool update(Ogre::Real deltaTime);

protected:
    Joystick* joystick;
    Keymap* map;

    OIS::InputManager* inputManager;
    OIS::Keyboard* keyboard;
    OIS::Mouse* mouse;

    virtual bool keyPressed(const OIS::KeyEvent& event);
    virtual bool keyReleased(const OIS::KeyEvent& event);

    virtual bool mouseMoved(const OIS::MouseEvent& event);
    virtual bool mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID id);
};

