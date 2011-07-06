#ifndef _SHIP_H_
#define _SHIP_H_

#include <OISKeyboard.h>

#include "Body.h"
#include "ThrustController.h"

class Ship : public Body {
public:
    Ship(Ogre::SceneManager* sceneMgr, std::string name, OIS::Keyboard* kb, \
        Ogre::Vector3 position, Ogre::Real kgMass);
    virtual ~Ship();

    virtual bool Update(Ogre::Real deltaTime);

protected:
    const Ogre::Real mass;
    const Ogre::Real moment; // Same moment for all axes! Whee!
    Controller::ThrustPlayer thrustController;
    //Controller::Turret laserController;
};

#endif
