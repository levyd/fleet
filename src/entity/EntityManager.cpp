#include <BulletCollision/NarrowPhaseCollision/btManifoldPoint.h>
#include <Collisions/OgreBulletCollisionsShape.h>
#include "EntityManager.h"
#include "CollisionListener.h"

#include <iostream>

/**
 * The currently registered EntityManager, which is responsible for notifying
 * Entities when they collide.
 */
EntityManager* SINGLETON = NULL;

/**
 * Static callback function, to be called by Bullet after any collision between
 * two objects.
 *
 * @return
 *     Return value indicates if the collision properties (e.g. friction) have
 *     been modified.
 */
bool CollisionCallback(btManifoldPoint& cp, const btCollisionObject* colObj0,
        int partId0, int index0, const btCollisionObject* colObj1, int partId1,
        int index1) {
    if(SINGLETON == NULL) {
        return false;
    }
    return SINGLETON->onCollision(cp, colObj0, partId0, index0, colObj1,
            partId1, index1);
}

/**
 * Construct a new EntityManager from the SceneManager @a scene, and the
 * DynamicsWorld @a world.
 *
 * The entities constructed by the resulting EntityManager will reside in the
 * world that @a scene and @a world represent.
 *
 * This constructor will also register itself as the collision callback
 * singleton, thereby becoming responsible for notifying Entities when they
 * collide.
 */
EntityManager::EntityManager(Ogre::SceneManager* scene,
        OgreBulletDynamics::DynamicsWorld* world) : scene(scene),
    world(world) {
        numMissiles = 0;
    this->registerAsSingleton();
}

/**
 * Destructor.
 *
 * Destruction of this object will cause destruction of all Entities that it
 * maintains when it is deleted.
 *
 * If this object is also the current collision callback singleton, this
 * destructor will unregister itself from that role.
 */
EntityManager::~EntityManager() {
    std::vector<Entity*>::iterator i;
    for(i = entities.begin(); i < entities.end(); i++) {
        if(*i != NULL) {
            delete *i;
        }
    }
    if(this == SINGLETON) {
        gContactProcessedCallback = NULL;
        SINGLETON = NULL;
    }
}

/**
 * Registers this EntityManager as the collision callback singleton, which is
 * responsible for notifying Entities when they collide.
 */
void EntityManager::registerAsSingleton() {
    if(SINGLETON == NULL) { SINGLETON = this; }
    Ogre::LogManager::getSingleton().logMessage("Registered collision callback.");
    gContactAddedCallback = &CollisionCallback;
}

bool EntityManager::onCollision(btManifoldPoint& cp, const btCollisionObject*
        colObj0, int partId0, int index0, const btCollisionObject* colObj1, int
        partId1, int index1) {
    const btRigidBody* rb0 = btRigidBody::upcast(colObj0);
    Entity* entity0 = NULL;
    if(objectMap.count(rb0) > 0) {
        entity0 = objectMap[rb0];
    }

    const btRigidBody* rb1 = btRigidBody::upcast(colObj1);
    Entity* entity1 = NULL;
    if(objectMap.count(rb1) > 0) {
        entity1 = objectMap[rb1];
    }

    bool isModified = false;
    if(entity0 != NULL) {
        CollisionListener* listener = dynamic_cast<CollisionListener*>(entity1);
        if(listener != NULL) {
            // Notify this listener that it has collided with another object.
            // Note that the other btRigidBody might not have been associated
            // with an Entity.
            isModified = listener->onCollision(entity0) || isModified;
        }
    }
    if(entity1 != NULL) {
        CollisionListener* listener = dynamic_cast<CollisionListener*>(entity0);
        if(listener != NULL) {
            // Notify this listener that it has collided with another object.
            // Note that the other btRigidBody might not have been associated
            // with an Entity.
            isModified = listener->onCollision(entity1) || isModified;
        }
    }
    return isModified;
}

Entity* EntityManager::createEntity(EntityProperties& properties) {
    return this->add(new Entity(this->scene, this->world, properties));
}

/**
 * Navigating weapon Entity. Currently flies straight forward.
 */
Missile* EntityManager::createMissile(EntityProperties& properties) {
    properties.name = "Missile" + Ogre::StringConverter::toString(numMissiles++);
    properties.mesh = "Missile.mesh";
    properties.material = "Steel";
    return (Missile*)this->add(new Missile(this->scene, this->world, properties));
}

/**
 * Simple round-body Entity. Uses an Ogre PrefabType instead of a supplied
 * mesh.
 */
Entity* EntityManager::createPlanet(EntityProperties& properties) {
    Ogre::Entity* entity = scene->createEntity(properties.name,
            Ogre::SceneManager::PT_SPHERE);
    return this->add(new Entity(this->scene, this->world, properties, entity));
}

/**
 * Pilotable, [armed?] Entity. Potentially controlled by either a player or
 * AI.
 */
Ship* EntityManager::createShip(EntityProperties& properties) {
    return (Ship*)this->add(new Ship(this->scene, this->world, properties));
}

/**
 * Update the state of each Entity after a game timestep.
 *
 * Updates each Entity that is managed by this EntityManager.
 *
 * @param deltaTime 
 *     The interval of time that has passed since the last update.
 */
bool EntityManager::update(Ogre::Real deltaTime) {
    std::vector<Entity*>::iterator i;
    for(i = entities.begin(); i < entities.end(); i++) {
        if(*i == NULL) {
            continue;
        }
        if((*i)->update(deltaTime) == false) {
            return false;
        }
    }
    return true;
}

/**
 * Tells this EntityManager to use a new SceneManager and a new DynamicsWorld.
 *
 * Subsequent Entities constructed will reside in the world represented by @a
 * scene and @a world.
 */
void EntityManager::useScene(Ogre::SceneManager* scene,
        OgreBulletDynamics::DynamicsWorld* world) {
    this->scene = scene;
    this->world = world;
}

/**
 * Manage the Entity @a entity, as if it were created by this EntityManager.
 *
 * This could be useful for transferring Entities between worlds, when used in
 * conjunction with {@link remove}.
 */
Entity* EntityManager::add(Entity* entity) {
    entities.push_back(entity);
    objectMap[entity->body->getBulletRigidBody()] = entity;
    return entity;
}

/**
 * Stop managing the Entity @a entity.
 *
 * This could be useful for transferring Entities between worlds, when used in
 * conjunction with {@link add}.
 */
/*Entity* EntityManager::remove(Entity* entity) {
    TODO: Write find(entities, entity) or change vector to map<Entity*, bool?>
    entities.erase(entities.find(entity));
    objectMap.erase(entity->body->getShape()->getBulletObject());
    return entity;
}*/
