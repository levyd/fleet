#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <OgrePrerequisites.h>

namespace Controller {
    class Controller {
    public:
        Controller();
        virtual ~Controller();

        virtual bool update(Ogre::Real deltaTime) = 0;

    };
}
#endif
