#ifndef _MISSILE_H_
#define _MISSILE_H_

#include <OgreSceneManager.h>

#include "CollisionListener.h"
#include "Entity.h"
//#include "Pilotable.h"

class Missile : public Entity, public CollisionListener {
public:
    Missile(Ogre::SceneManager* scene, OgreBulletDynamics::DynamicsWorld* world,
            EntityProperties properties);
    virtual ~Missile();

    virtual bool onCollision(Entity* other);
    virtual bool update(Ogre::Real deltaTime);

private:
    Ogre::Real fuelTime;
    bool hasCollided;
};

#endif

