#include "EntityManager.h"

EntityManager::EntityManager(Ogre::SceneManager* scene) : scene(scene) {
}

EntityManager::~EntityManager() {
    for(int i = 0; i < 4; i++) {
        if(entities[i] != NULL) {
            delete entities[i];
        }
    }
}

Entity* EntityManager::createEntity(std::string& name, std::string& mesh) {
    entities[entityIndex] = new Entity(this->scene, name, mesh);

    return entities[entityIndex++];
}

bool EntityManager::update(Ogre::Real deltaTime) {
    for(int i = 0; i < 4; i++) {
        if(entities[i] != NULL) {
            // If an entity returns false, then we will too.
            entities[i]->update(deltaTime) || return false;
        }
    }
}

