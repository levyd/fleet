#include <OgreRoot.h>
#include <OgreEntity.h>
#include <OgreViewport.h>

#include "Level.h"

Level::Level() : scene(0), camera(0) {
}

Level::~Level() {
	if(ship != NULL) { delete ship; }
    if(scene != NULL) { Ogre::Root::getSingleton().destroySceneManager(scene); }
    this->UnloadResources();
}

void Level::Initialise(const std::string& levelName, OIS::Keyboard* kb) {
    this->name = levelName;
    scene = Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC, levelName);

    keyboard = kb;

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
	planet->attachObject(scene->createEntity("Planet", Ogre::SceneManager::PT_SPHERE));

    Ogre::SceneNode* light = scene->getRootSceneNode()->createChildSceneNode("Light", Ogre::Vector3(200, 20, 0), Ogre::Quaternion::IDENTITY);
	light->attachObject(scene->createLight("Light"));

    camera = scene->createCamera("Camera");
    camera->setNearClipDistance(5);
    ship = new Ship(scene, Ogre::Vector3(0, 0, 0), keyboard, camera);
}

void Level::Launch(Ogre::RenderWindow* window) {
    window->removeAllViewports();
    Ogre::Viewport* viewport = window->addViewport(camera, 0, 0, 0, 1, 1);
    viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
}

bool Level::Update(Ogre::Real deltaTime) {
    return ship->Update(deltaTime);
}
