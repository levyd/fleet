#include <OgreConfigFile.h>

#include "Application.h"

Application::Application(void) : root(0), window(0), inputManager(0) {
}

Application::~Application(void) {
    if(level != NULL) { delete level; }
    if(inputManager != NULL) {
        OIS::InputManager::destroyInputSystem(inputManager);
        inputManager = 0;
    }
    if(console) { delete console; }
    delete root;
}

bool Application::initialise(void) {
    size_t windowHandle = 0;

    root = new Ogre::Root("plugins.cfg");
    if(!(root->restoreConfig() || root->showConfigDialog())) { return false; }

    window = root->initialise(true, "Fleet");
    window->getCustomAttribute("WINDOW", &windowHandle);

    inputManager = OIS::InputManager::createInputSystem(windowHandle);

    this->loadResources("resources.cfg");

    this->level = new Level("Level-1", inputManager);
    //this->level->loadResources();
    this->level->buildScene();

    this->console = new OgreConsole();
    OgreConsole::getSingleton().isVisible = true;

    root->addFrameListener(this);
    return true;
}

void Application::launch(void) {
    level->launch(window);
    root->startRendering();
    //this->level->unloadResources();
    this->unloadResources();
}

bool Application::frameRenderingQueued(const Ogre::FrameEvent& event) {
    if(window->isClosed()) { return false; }
    if(!level->update(event.timeSinceLastFrame)) { return false; }
    return true;
}

void Application::loadResources(const std::string& resourcesCfg) {
    Ogre::ConfigFile config;
    Ogre::String secName, typeName, archName;

    config.load(resourcesCfg);

    Ogre::ConfigFile::SectionIterator sections = config.getSectionIterator();
    while (sections.hasMoreElements()) {
        secName = sections.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = sections.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i) {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                    archName, typeName, secName);
        }
    }

    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Common");
}

void Application::unloadResources() {
    Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("Common");
}
