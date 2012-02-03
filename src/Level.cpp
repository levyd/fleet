#include <OgreRoot.h>
#include <OgreViewport.h>

#include "Level.h"

Level::Level() : scene(0), camera(0), keyboard(0), world(0) {
}

Level::~Level() {
	if(ship != NULL) { delete ship; }
    if(scene != NULL) { Ogre::Root::getSingleton().destroySceneManager(scene); }
    if(world != NULL) { delete world; }
    this->UnloadResources();
}

void Level::Initialise(const std::string& levelName, OIS::Keyboard* kb) {
    this->name = levelName;
    keyboard = kb;

    scene = Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC, levelName);
    Ogre::AxisAlignedBox bounds = Ogre::AxisAlignedBox(
            Ogre::Vector3(-10000, -10000, -10000), Ogre::Vector3(-10000, -10000, -10000));
    world = new OgreBulletDynamics::DynamicsWorld(scene, bounds, Ogre::Vector3(0, 0, 0));

    //this->LoadResources();
    this->BuildScene();
}

void Level::LoadResources() {
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(this->name);
}

void Level::UnloadResources() {
    Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(this->name);
}

void Level::BuildScene() {
	scene->setSkyBox(true, "Sky/Stars");
    scene->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));

    Ogre::SceneNode* planet = scene->getRootSceneNode()->createChildSceneNode("Planet", Ogre::Vector3(200, 0, 0), Ogre::Quaternion::IDENTITY);
	planet->attachObject((Ogre::MovableObject*)scene->createEntity("Planet", Ogre::SceneManager::PT_SPHERE));

    Ogre::SceneNode* light = scene->getRootSceneNode()->createChildSceneNode("Light", Ogre::Vector3(200, 20, 0), Ogre::Quaternion::IDENTITY);
	light->attachObject(scene->createLight("Light"));

    camera = scene->createCamera("Camera");
    camera->setNearClipDistance(5);

    ship = new Ship(scene, world, "Ship/Cruiser", "Cruiser.mesh");
    ship->attachCamera(camera, Ogre::Vector3(0, 20, 120));
    ship->controlThrust(keyboard);
}

void Level::Launch(Ogre::RenderWindow* window) {
    window->removeAllViewports();
    Ogre::Viewport* viewport = window->addViewport(camera, 0, 0, 0, 1, 1);
    viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
}

bool Level::update(Ogre::Real deltaTime) {
    world->stepSimulation(deltaTime);
    return ship->update(deltaTime);
}
