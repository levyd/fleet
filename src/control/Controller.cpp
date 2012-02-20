#include "Controller.h"

Controller::Controller() : actor(0) {
}

Controller::~Controller() {
}

void Controller::control(Actionable* actor) {
    this->actor = actor;
}

void Controller::release() {
    this->actor = NULL;
}

