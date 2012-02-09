#include "Controller.h"

Controller::Controller() : entity(0) {
}

Controller::~Controller() {
}

void Controller::control(Entity* entity) {
    this->entity = entity;
}

