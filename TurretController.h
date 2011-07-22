#ifndef _TURRET_CONTROLLER_H
#define _TURRET_CONTROLLER_H

#include <OgreVector3.h>
#include <OgreSceneManager.h>

#include <OISInputManager.h>
#include <OISEvents.h>
#include <OISKeyboard.h>

#include "Controller.h"

namespace Controller {
    class Turret : public Controller {
    public:
        Turret(Ogre::SceneNode* bodyNode, Ogre::Vector3 offset, Ogre::Quaternion rotation);
        virtual ~Turret();

        virtual bool Update(Ogre::Real deltaTime) = 0;

    protected:
        Ogre::SceneNode* baseNode;
        Ogre::SceneNode* turretNode;
        Ogre::Radian rotationX, rotationY;
        Ogre::Radian trackingSpeed;
    };

    class TurretPlayer : public Turret, public OIS::KeyListener {
    public:
        TurretPlayer(Ogre::SceneNode* bodyNode, Ogre::Vector3 offset, Ogre::Quaternion rotation, OIS::Keyboard* kb, Ogre::Camera* camera);
        virtual ~TurretPlayer();

        virtual bool Update(Ogre::Real deltaTime);

    protected:
        OIS::Keyboard* keyboard;
        virtual bool keyPressed(const OIS::KeyEvent& event);
        virtual bool keyReleased(const OIS::KeyEvent& event);
    };

    class TurretAI : public Turret {
    public:
    	TurretAI(Ogre::SceneNode* bodyNode, Ogre::Vector3 offset, Ogre::Quaternion rotation);
    	virtual ~TurretAI();

    	virtual bool Update(Ogre::Real deltaTime);
    private:
    	int timer;
    };
}
#endif
