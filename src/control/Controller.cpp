#include "Controller.h"

Controller::Controller() : actor(0) {
}

Controller::~Controller() {
}

/**
 * Begin controlling the specified Actionable.
 *
 * Designates the supplied Actionable entity as the actor that will perform the
 * actions received by this Controller.
 */
void Controller::control(Actionable* actor) {
    this->actor = actor;
}

/**
 * Cease controlling the stored Actionable.
 *
 * Releases the stored Actionable entity, so that no actor will perform the
 * actions received by this Controller.
 */
void Controller::release() {
    this->actor = NULL;
}

