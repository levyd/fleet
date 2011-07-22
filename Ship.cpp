#include <OgreEntity.h>

#include "Ship.h"

Ship::Ship(Ogre::SceneManager* sceneMgr, Ogre::Vector3 position) : Body(sceneMgr, position) {
    Ogre::Entity* entity = sceneMgr->createEntity("Ship/Cruiser", "Cruiser.mesh");
    entity->setMaterialName("Steel");
    bodyNode->attachObject(entity);
}

Ship::Ship(Ogre::SceneManager* sceneMgr, Ogre::Vector3 position, OIS::Keyboard* kb, Ogre::Camera* camera)
    : Body(sceneMgr, position) {
	Ogre::Entity* entity = sceneMgr->createEntity("Ship/Cruiser", "Cruiser.mesh");
    entity->setMaterialName("Steel");
	bodyNode->attachObject(entity);

	thrustController = new Controller::ThrustAI();//bodyNode, Ogre::Vector3(0, 20, 120), kb, camera);
    thrustController->SetMovementSpeeds(Ogre::Real(100), Ogre::Real(50), \
        Ogre::Real(10), Ogre::Radian(100), Ogre::Radian(100), Ogre::Radian(100));

	turretController = new Controller::TurretPlayer(bodyNode, Ogre::Vector3(15, 0, 0), \
			Ogre::Quaternion(Ogre::Radian(Ogre::Degree(-90)), Ogre::Vector3::UNIT_Y), kb, camera);

}

Ship::~Ship() {
	delete thrustController;
}

bool Ship::Update(Ogre::Real deltaTime) {
	thrustController->Update(deltaTime);
    velocity += bodyNode->getOrientation() * thrustController->thrust * deltaTime;
    Ogre::Quaternion alpha = Ogre::Quaternion(thrustController->torqueX, Ogre::Vector3::UNIT_X)
                           * Ogre::Quaternion(thrustController->torqueY, Ogre::Vector3::UNIT_Y)
                           * Ogre::Quaternion(thrustController->torqueZ, Ogre::Vector3::UNIT_Z);
    angular = angular * Ogre::Quaternion::Slerp(deltaTime, Ogre::Quaternion::IDENTITY, alpha, true);

    turretController->Update(deltaTime);

    return Body::Update(deltaTime);
}

