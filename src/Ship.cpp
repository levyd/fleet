#include <OgreBulletDynamicsWorld.h>

#include "Ship.h"

Ship::Ship(Ogre::SceneManager* scene, OgreBulletDynamics::DynamicsWorld* world, std::string name, std::string mesh)
    : Pilotable(scene, world, name, mesh) {

    //turretController = new Controller::TurretPlayer(node, Ogre::Vector3(15, 0, 0), \
        Ogre::Quaternion(Ogre::Radian(Ogre::Degree(-90)), Ogre::Vector3::UNIT_Y), kb, camera);
}

Ship::~Ship() {
}

bool Ship::update(Ogre::Real deltaTime) {
    //turretController->update(deltaTime);

    return Pilotable::update(deltaTime);
}

