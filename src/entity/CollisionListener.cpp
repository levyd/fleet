#include "CollisionListener.h"

#include <BulletDynamics/Dynamics/btRigidBody.h>

/**
 * Activates the collision callbacks for this listener.
 *
 * @param body
 *     The rigid body that should now trigger collision callbacks.
 */
void CollisionListener::enableCallback(OgreBulletDynamics::RigidBody* body) {
    btRigidBody* bulletBody = body->getBulletRigidBody();
    bulletBody->setCollisionFlags(bulletBody->getCollisionFlags() |
            btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
}

/**
 * Handle a collision.
 * 
 * @param other
 *     The Entity that this object has collided with.
 * @return
 *     Returns true if this function has modified any collision property of
 *     either object involved in the collision. Returns false otherwise.
 */
bool CollisionListener::onCollision(Entity* other) {
    return false;
}
