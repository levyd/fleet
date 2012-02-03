#ifndef _SHIP_H_
#define _SHIP_H_

#include <OgreSceneManager.h>
#include <string.h>

#include "Pilotable.h"
#include "TurretController.h"

class Ship : public Pilotable {
public:
    Ship(Ogre::SceneManager* scene, OgreBulletDynamics::DynamicsWorld* world,
            std::string name, std::string mesh);
    virtual ~Ship();

    virtual bool update(Ogre::Real deltaTime);

protected:
    Controller::Turret* turretController;
};

#endif
