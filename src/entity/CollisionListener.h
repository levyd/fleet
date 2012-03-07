#ifndef _COLLISION_LISTENER_H_
#define _COLLISION_LISTENER_H_
class CollisionListener {
public:
    virtual bool onCollision(Entity* other) { return false; };
};

#endif

