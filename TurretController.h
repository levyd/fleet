#ifndef _TURRET_CONTROLLER_H
#define _TURRET_CONTROLLER_H

#include <OgreVector3.h>

#include <OISInputManager.h>
#include <OISEvents.h>
#include <OISKeyboard.h>

#include "Controller.h"

namespace Controller {
    class Turret : public Controller {
    public:
        Turret();
        virtual ~Turret();

        virtual bool Update(Ogre::Real deltaTime) = 0;

    protected:
    };

    class TurretPlayer : public Turret, public OIS::KeyListener {
    public:
        TurretPlayer(OIS::Keyboard* kb);
        virtual ~TurretPlayer();

        virtual bool Update(Ogre::Real deltaTime);

    protected:
        OIS::Keyboard* keyboard;
        virtual bool keyPressed(const OIS::KeyEvent& event);
        virtual bool keyReleased(const OIS::KeyEvent& event);
    };

    class TurretAI : public Turret {
    public:
    	TurretAI();
    	virtual ~TurretAI();

    	virtual bool Update(Ogre::Real deltaTime);
    private:
    	int timer;
    };
}
#endif
