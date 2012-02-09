#ifndef _SHIP_H_
#define _SHIP_H_

#include <OgreSceneManager.h>
#include <string.h>

#include "Entity.h"
#include "Pilotable.h"

class Ship : public Entity, public Pilotable {
public:
    Ship(Ogre::SceneManager* scene, OgreBulletDynamics::DynamicsWorld* world,
            std::string name, std::string mesh);
    virtual ~Ship();

    virtual bool update(Ogre::Real deltaTime);
};

#endif
