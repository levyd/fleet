#ifndef _COLLISION_LISTENER_H_
#define _COLLISION_LISTENER_H_

#include <OgreBulletDynamicsRigidBody.h>
#include "Entity.h"

class CollisionListener {
public:
    static void enableCallback(OgreBulletDynamics::RigidBody* body);

    virtual bool onCollision(Entity* other);
};

#endif

