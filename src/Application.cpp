#include <OgreConfigFile.h>

#include "Application.h"
#include "Controller.h"

Application::Application(void) : root(0), window(0), inputManager(0) {
}

Application::~Application(void) {

    Ogre::WindowEventUtilities::removeWindowEventListener(window, this);
    windowClosed(window);
    delete root;
}

bool Application::initialise(void) {
    size_t windowHandle = 0;

    root = new Ogre::Root("plugins.cfg");
    if(!(root->restoreConfig() || root->showConfigDialog())) { return false; }

    window = root->initialise(true, "Fleet");
    Ogre::WindowEventUtilities::addWindowEventListener(window, this);

    window->getCustomAttribute("WINDOW", &windowHandle);
    inputManager = OIS::InputManager::createInputSystem(windowHandle);

    this->loadResources("resources.cfg");

    level.initialise("Level-1", inputManager);

    root->addFrameListener(this);
    return true;
}

void Application::launch(void) {
    level.launch(window);
    root->startRendering();
}

bool Application::frameRenderingQueued(const Ogre::FrameEvent& event) {
    if(window->isClosed()) { return false; }
    if(!level.update(event.timeSinceLastFrame)) { return false; }
    return true;
}

void Application::windowClosed(Ogre::RenderWindow* rw) {
    if(rw != window) { return; }
    if(inputManager != NULL) {
        OIS::InputManager::destroyInputSystem(inputManager);
        inputManager = 0;
    }
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

