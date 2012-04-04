#pragma once
#include <OgreFrameListener.h>
#include <Ogre.h>
#include <OIS/OIS.h>
#include <list>
#include <vector>
#include <string>

typedef void (*Command)(std::vector<std::string>&);

class OgreConsole : public Ogre::Singleton<OgreConsole>, Ogre::FrameListener,
    Ogre::LogListener {
public:
    OgreConsole();
    ~OgreConsole();

    void print(const std::string &text);

    void onKeyPressed(const OIS::KeyEvent &arg);

    void addCommand(const std::string &command, void (*action)(std::vector<std::string>&));
    void removeCommand(const std::string &command);

    // Inherited from FrameListener
    virtual bool frameStarted(const Ogre::FrameEvent &evt);

    // Inherited from LogListener
    void messageLogged(const std::string& message, Ogre::LogMessageLevel lml, bool maskDebug, const std::string &logName ) {print(logName+": "+message);}

    bool isVisible;

private:
    void processCommand();

    Ogre::Root *root;
    Ogre::SceneManager *scene;
    Ogre::Rectangle2D *rect;
    Ogre::SceneNode *node;
    Ogre::OverlayElement *textbox;
    Ogre::Overlay *overlay;

    float height;
    bool isDirty;
    unsigned lineNumber;
    std::string prompt;
    std::list<std::string>      lines;
    std::map<std::string, Command> commands;
};

