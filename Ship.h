#ifndef _SHIP_H_
#define _SHIP_H_

#include <OISKeyboard.h>

#include "Body.h"
#include "ThrustController.h"

class Ship : public Body {
public:
    Ship(Ogre::SceneManager* sceneMgr, Ogre::Vector3 position);
    Ship(Ogre::SceneManager* sceneMgr, Ogre::Vector3 position, OIS::Keyboard* kb);
    virtual ~Ship();

    virtual bool Update(Ogre::Real deltaTime);

protected:
    Controller::Thrust* thrustController;
    //Controller::Turret laserController;
};

#endif
