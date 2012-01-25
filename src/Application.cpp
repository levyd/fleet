#include <OgreConfigFile.h>

#include "Application.h"
#include "Controller.h"

//------------------------------------------------------------------------------
Application::Application(void) : root(0), window(0), input(0), keyboard(0) {
}
//------------------------------------------------------------------------------
Application::~Application(void) {

    Ogre::WindowEventUtilities::removeWindowEventListener(window, this);
    windowClosed(window);
    delete root;
}
//------------------------------------------------------------------------------
bool Application::Initialise(void) {
    size_t windowHandle = 0;

    root = new Ogre::Root("plugins.cfg");
    if(!(root->restoreConfig() || root->showConfigDialog())) { return false; }

    window = root->initialise(true, "Fleet");
    Ogre::WindowEventUtilities::addWindowEventListener(window, this);

    window->getCustomAttribute("WINDOW", &windowHandle);
    input = OIS::InputManager::createInputSystem(windowHandle);
    keyboard = static_cast<OIS::Keyboard*>(input->createInputObject(OIS::OISKeyboard, true));

    LoadResources("resources.cfg");

    level.Initialise("Level-1", keyboard);

    root->addFrameListener(this);
    return true;
}
//------------------------------------------------------------------------------
void Application::Launch(void) {
    level.Launch(window);
    root->startRendering();
}
//------------------------------------------------------------------------------
bool Application::frameRenderingQueued(const Ogre::FrameEvent& event) {
    if(keyboard->isKeyDown(OIS::KC_ESCAPE)) {
        windowClosed(window);
        return false;
    }
    if(window->isClosed()) { return false; }
    if(!level.update(event.timeSinceLastFrame)) { return false; }
    return true;
}
//------------------------------------------------------------------------------
void Application::windowClosed(Ogre::RenderWindow* rw) {
    if(rw != window) { return; }
    if(input != NULL) {
        if(keyboard != NULL) { input->destroyInputObject(keyboard); }
        OIS::InputManager::destroyInputSystem(input);
        input = 0;
    }
}
//------------------------------------------------------------------------------
void Application::LoadResources(const std::string& resourcesCfg) {
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

