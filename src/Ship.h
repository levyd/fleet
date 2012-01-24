#ifndef _SHIP_H_
#define _SHIP_H_

#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <OISKeyboard.h>

#include "Body.h"
#include "ThrustController.h"
#include "TurretController.h"

class Ship : public Body {
public:
    Ship(Ogre::SceneManager* sceneMgr, Ogre::Vector3 position);
    Ship(Ogre::SceneManager* sceneMgr, Ogre::Vector3 position, OIS::Keyboard* kb, Ogre::Camera* camera);
    virtual ~Ship();

    virtual bool Update(Ogre::Real deltaTime);

protected:
    Controller::Thrust* thrustController;
    Controller::Turret* turretController;
};

#endif
