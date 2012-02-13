#include "EntityManager.h"

EntityManager::EntityManager(Ogre::SceneManager* scene,
        OgreBulletDynamics::DynamicsWorld* world) : scene(scene),
    world(world) {
}

EntityManager::~EntityManager() {
    std::vector<Entity*>::iterator i;
    for(i = entities.begin(); i < entities.end(); i++) {
        if(*i != NULL) {
            delete *i;
        }
    }
}

Entity* EntityManager::createEntity(EntityProperties& properties) {
    entities.push_back(new Entity(this->scene, this->world, properties));
    return entities.back();
}

/**
 * Simple round-body Entity. Uses an Ogre PrefabType instead of a supplied
 * mesh.
 */
Entity* EntityManager::createPlanet(EntityProperties& properties) {
    Ogre::Entity* entity = scene->createEntity(properties.name,
            Ogre::SceneManager::PT_SPHERE);
    entities.push_back(new Entity(this->scene, this->world, properties, entity));
    return entities.back();
}

/**
 * Pilotable, [armed?] Entity. Potentially controlled by either a player or
 * AI.
 */
Ship* EntityManager::createShip(EntityProperties& properties) {
    entities.push_back(new Ship(this->scene, this->world, properties));
    return (Ship*)entities.back();
}

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

