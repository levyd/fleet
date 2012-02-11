#ifndef _ACTIONABLE_H_
#define _ACTIONABLE_H_

#define PERFORM(actionable, action) ((actionable)->*(action))

/**
 * This class defines, and provides a default implementation for, all
 * performable actions.
 */
class Actionable {
public:
    Actionable();
    virtual ~Actionable();

    virtual bool actionDefault(bool isActive) { return false; };
    virtual bool actionDefault(int position) { return false; };
    virtual bool actionThrustForward(bool isActive) { return false; };
    virtual bool actionThrustReverse(bool isActive) { return false; };
    virtual bool actionThrustLeft(bool isActive) { return false; };
    virtual bool actionThrustRight(bool isActive) { return false; };
    virtual bool actionThrustUp(bool isActive) { return false; };
    virtual bool actionThrustDown(bool isActive) { return false; };
    virtual bool actionYawLeft(bool isActive) { return false; };
    virtual bool actionYawRight(bool isActive) { return false; };
    virtual bool actionPitchUp(bool isActive) { return false; };
    virtual bool actionPitchDown(bool isActive) { return false; };
    virtual bool actionRollLeft(bool isActive) { return false; };
    virtual bool actionRollRight(bool isActive) { return false; };
};

typedef bool ((Actionable::*AxisAction)(int position));
typedef bool ((Actionable::*ButtonAction)(bool isPressed));

#endif

