#include "GameWindow.h"

GameWindow::GameWindow() : window(0) {
}

GameWindow::~GameWindow() {
    Ogre::WindowEventUtilities::removeWindowEventListener(window, this);
}

void GameWindow::Initialise(Ogre::RenderWindow* w) {
    window = w;
    Ogre::WindowEventUtilities::addWindowEventListener(window, this);
}

bool GameWindow::Update(Ogre::Real deltaTime) {
    if(window->isClosed()) { return false; }
    return true;
}

