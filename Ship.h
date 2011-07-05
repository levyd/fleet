#ifndef _SHIP_H_
#define _SHIP_H_

#include "Body.h"
#include "Controller.h"

class Ship : public Body {
public:
    Ship(Ogre::SceneManager* sceneMgr, std::string name, OIS::OISKeyboard* kb, \
        Ogre::Vector3 position, Ogre::Real kgMass);
    virtual ~Ship();

    virtual bool Update(Ogre::Real deltaTime);

protected:
    const Ogre::Real mass;
    //Ogre::Vector3 moment;
    Controller::Thrust thrustController;
    //Controller::Turret laserController;
};

#endif
