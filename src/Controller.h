#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <OgrePrerequisites.h>

#include "Entity.h"

class Controller {
public:
    Controller();
    virtual ~Controller();

    void control(Entity* entity);
    virtual bool update(Ogre::Real deltaTime) = 0;

private:
    Entity* entity;

};
#endif
