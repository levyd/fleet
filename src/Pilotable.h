#ifndef _PILOTABLE_H_
#define _PILOTABLE_H_

#include <OgreSceneManager.h>
#include <OISKeyboard.h>
#include <string.h>

#include "Entity.h"
#include "ThrustController.h"

class Pilotable : public Entity {
public:
    Pilotable(Ogre::SceneManager* scene, OgreBulletDynamics::DynamicsWorld* world,
        std::string& name, std::string& mesh);
    virtual ~Pilotable();

    void controlThrust(OIS::Keyboard* kb);

    virtual bool update(Ogre::Real deltaTime);

protected:
    Controller::Thrust* thrustController;
};

#endif

