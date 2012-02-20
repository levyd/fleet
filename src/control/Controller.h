#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <OgrePrerequisites.h>

#include "../entity/Actionable.h"

class Controller {
public:
    Controller();
    virtual ~Controller();

    void control(Actionable* actor);
    void release();
    virtual bool update(Ogre::Real deltaTime) = 0;

protected:
    Actionable* actor;

};
#endif
