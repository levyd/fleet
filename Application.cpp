#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>

#include "Application.h"
#include "Controller.h"

//-------------------------------------------------------------------------------------
Application::Application(void) : root(0) {
}
//-------------------------------------------------------------------------------------
Application::~Application(void)
{
    delete root;
}
//-------------------------------------------------------------------------------------
bool Application::Initialise(void) {
    root = new Ogre::Root("plugins.cfg");

    if(!(root->restoreConfig() || root->showConfigDialog())) { return false; }
    gameWindow.Initialise(root->initialise(true, "Fleet"));

    LoadResources("fleet-resources.cfg");

    Controller::BuildInputManager(gameWindow.window);

    level.Initialise("Level-1");

    root->addFrameListener(this);
    return true;
}
//-------------------------------------------------------------------------------------
void Application::LoadResources(const std::string& resourcesCfg) {
    Ogre::ConfigFile config;
    Ogre::String secName, typeName, archName;

    config.load(resourcesCfg);

    Ogre::ConfigFile::SectionIterator sections = config.getSectionIterator();
    while (sections.hasMoreElements())
    {
        secName = sections.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = sections.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                    archName, typeName, secName);
        }
    }

    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Common");
}
//-------------------------------------------------------------------------------------
void Application::Launch(void)
{
    level.Launch(gameWindow.window);
    root->startRendering();
}
//-------------------------------------------------------------------------------------
bool Application::frameRenderingQueued(const Ogre::FrameEvent& event) {
    if(!gameWindow.Update(event.timeSinceLastFrame)) { return false; }
    if(!level.Update(event.timeSinceLastFrame)) { return false; }
    return true;
}
