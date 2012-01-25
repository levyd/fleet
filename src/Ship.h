#ifndef _SHIP_H_
#define _SHIP_H_

#include <OgreSceneManager.h>
#include <OISKeyboard.h>
#include <string.h>

#include "Entity.h"
#include "ThrustController.h"
#include "TurretController.h"

class Ship : public Entity {
public:
    Ship(Ogre::SceneManager* sceneMgr, std::string name, std::string mesh);
    virtual ~Ship();

    virtual bool update(Ogre::Real deltaTime);

    void controlThrust(OIS::Keyboard* kb);

protected:
    Controller::Thrust* thrustController;
    Controller::Turret* turretController;
};

#endif
