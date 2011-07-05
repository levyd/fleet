#include <OgreRoot.h>
#include <OgreEntity.h>
#include <OgreViewport.h>

#include "Level.h"

Level::Level() : scene(0), camera(0) {
}

Level::~Level() {
    if(scene != NULL) { Ogre::Root::getSingleton().destroySceneManager(scene); }
    this->UnloadResources();
}

void Level::Initialise(const std::string& levelName, OIS::OISKeyboard* kb) {
    this->name = levelName;
    scene = Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC, levelName);

    keyboard = kb;

    this->LoadResources();
    this->BuildScene();
}

void Level::LoadResources() {
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(this->name);
}

void Level::UnloadResources() {
    Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(this->name);
}

void Level::BuildScene() {
    camera = scene->createCamera("Camera");
    camera->setPosition(Ogre::Vector3(0, 0, 80));
    camera->lookAt(Ogre::Vector3(0, 0, -300));
    camera->setNearClipDistance(5);

    ship = new Ship(scene, "OgreHead", keyboard, Ogre::Vector3(0, 0, 0), 1000);

    scene->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));
}

void Level::Launch(Ogre::RenderWindow* window) {
    window->removeAllViewports();
    Ogre::Viewport* viewport = window->addViewport(camera, 0, 0, 0, 1, 1);
    viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
}

bool Level::Update(Ogre::Real deltaTime) {
    return true;
}
