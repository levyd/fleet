#include "Console.h"

template<> OgreConsole *Ogre::Singleton<OgreConsole>::ms_Singleton = 0;

#define CONSOLE_LINE_LENGTH 85
#define CONSOLE_LINE_COUNT 15

OgreConsole::OgreConsole() {
    this->root = Ogre::Root::getSingletonPtr();
    if(!root->getSceneManagerIterator().hasMoreElements()) {
        OGRE_EXCEPT( Ogre::Exception::ERR_INTERNAL_ERROR, "No scene manager found!", "init" );
    }
    this->root = root;

    lineNumber = 0;
    scene = root->getSceneManagerIterator().getNext();
    root->addFrameListener(this);

    height = 1;

    // Create background rectangle covering the whole screen
    rect = new Ogre::Rectangle2D(true);
    rect->setCorners(-1, 1, 1, 1 - height);
    rect->setMaterial("console/background");
    rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);
    rect->setBoundingBox(Ogre::AxisAlignedBox(-100000.0*Ogre::Vector3::UNIT_SCALE, 100000.0*Ogre::Vector3::UNIT_SCALE));
    node = scene->getRootSceneNode()->createChildSceneNode("#Console");
    node->attachObject(rect);

    textbox = Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea","ConsoleText");
    textbox->setCaption("hello");
    textbox->setMetricsMode(Ogre::GMM_RELATIVE);
    textbox->setPosition(0,0);
    textbox->setParameter("font_name","Console");
    textbox->setParameter("colour_top","1 1 1");
    textbox->setParameter("colour_bottom","1 1 1");
    textbox->setParameter("char_height","0.03");

    overlay = Ogre::OverlayManager::getSingleton().create("Console");   
    overlay->add2D((Ogre::OverlayContainer*)textbox);
    overlay->show();
    Ogre::LogManager::getSingleton().getDefaultLog()->addListener(this);
}

OgreConsole::~OgreConsole() {
    if(this->rect) { delete rect; }
    //if(this->node) { scene->destroySceneNode(node); }
    //if(this->textbox) { delete textbox; }
}

/**
 * Handles keyboard events for the console.
 *
 * If the console is not visible (and the event would not make it visible), then
 * the event is ignored.
 */
void OgreConsole::onKeyPressed(const OIS::KeyEvent &event) {
    if(!this->isVisible && event.key != OIS::KC_GRAVE) { return; }

    switch(event.key) {
    case OIS::KC_GRAVE:
        this->isVisible = !this->isVisible;
        break;
    case OIS::KC_RETURN:
        processCommand();
        break;
    case OIS::KC_BACK:
        prompt = prompt.substr(0,prompt.length()-1);
        break;
    case OIS::KC_PGUP:
        if(lineNumber > 0) {
            lineNumber--;
        }
        break;
    case OIS::KC_PGDOWN:
        if(lineNumber < lines.size()) {
            lineNumber++;
        }
        break;
    default:
        char legalchars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890+!\"#%&/()=?[]\\*-_.:,; ";
        for(unsigned i = 0; i < sizeof(legalchars); i++) {
            if(legalchars[i] == (char)event.text) {
                prompt += (char)event.text;
                break;
            }
        }
    }
    isDirty = true;
}

bool OgreConsole::frameStarted(const Ogre::FrameEvent &evt) {
    // If we are hiding or un-hiding the console, then 'step' the animation.
    if(isVisible && height < 1) {
        height += evt.timeSinceLastFrame * 2;
        textbox->show();
        if(height >= 1){
            height = 1;
        }
    } else if(!isVisible && height > 0){
        height -= evt.timeSinceLastFrame * 2;
        if(height <= 0){
            height = 0;
            textbox->hide();
        }
    }
    textbox->setPosition(0, (height - 1) * 0.5);
    rect->setCorners(-1, 1 + height, 1, 1 - height);

    // If the text to be displayed has changed, re-caption the textbox.
    if(isDirty) {
        isDirty = false;

        std::string text;
        std::list<std::string>::iterator it, start, end;

        // Make sure is in range
        if(lineNumber > lines.size()) {
            lineNumber = lines.size();
        }

        start = lines.begin();
        for(unsigned i = 0; i < lineNumber; i++) {
            ++start;
        }
        end = start;
        for(int i = 0; i < CONSOLE_LINE_COUNT; i++) {
            if(end == lines.end()) {
                break;
            }
            ++end;
        }
        for(it = start; it != end; ++it) {
            text += (*it) + "\n";
        }

        // Add the prompt
        text += "$ " + prompt;

        textbox->setCaption(text);
    }
    return true;
}

void OgreConsole::print(const std::string &text) {
    // Divide the given string into lines
    const char *str = text.c_str();
    int len = text.length();
    std::string line;
    for(int i = 0; i < len; i++) {
        if(str[i] == '\n' || line.length() >= CONSOLE_LINE_LENGTH) {
            lines.push_back(line);
            line = "";
        }
        if(str[i] != '\n') {
            line += str[i];
        }
    }
    if(line.length()) {
        lines.push_back(line);
    }
    if(lines.size() > CONSOLE_LINE_COUNT) {
        lineNumber = lines.size() - CONSOLE_LINE_COUNT;
    } else {
        lineNumber = 0;
    }
    isDirty = true;
}

void OgreConsole::addCommand(const std::string &command, void (*func)(std::vector<std::string>&)){
    commands[command] = func;
}

void OgreConsole::removeCommand(const std::string &command){
    commands.erase(commands.find(command));
}

void OgreConsole::processCommand() {
    // Split the line into arguments
    const char* str = prompt.c_str();
    std::vector<std::string> arguments;
    std::string argument = "";
    for(unsigned i = 0; i < prompt.length(); i++) {
        if(str[i] == ' ') {
            if(argument.length() > 0) {
                arguments.push_back(argument);
            }
            argument = "";
        } else {
            argument += str[i];
        }
    }
    if(argument.length() > 0) {
        arguments.push_back(argument);
    }

    // Locate and execute the command
    std::map<std::string, Command>::iterator it;
    for(it = commands.begin(); it != commands.end(); ++it) {
        if((*it).first == arguments[0]){
            if((*it).second) {
                (*it).second(arguments);
            }
            break;
        }
    }

    print(prompt);
    prompt = "";
}

