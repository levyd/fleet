#ifndef _ACTIONABLE_H_
#define _ACTIONABLE_H_

#define PERFORM(actionable, action) ((actionable)->*(action))

#include <OgreMath.h>

/**
 * An actionable Entity can be manipulated by user input through the use of
 * actions. Any Entity (or module) which derives from this class should
 * provide an implementation for some or all @ref actions defined in this file.
 *
 * This class provides a default implementation for all performable actions.
 */
class Actionable {
public:
    Actionable() { };
    virtual ~Actionable() { };

    /**
     * @defgroup actions
     *     Events that can be triggered by user input.
     * 
     * @{
     *     @defgroup axis-actions
     *         Events that can be triggered by input on an axis (e.g. a
     *         joystick).
     *         @see AxisAction
     *     @ {
     */
    /** Default implementations have no effect */
    virtual bool actionDefault(int old, int abs) { return false; };
    virtual bool actionThrustForwardReverse(int old, int abs) { return false; };
    virtual bool actionThrustLeftRight(int old, int abs) { return false; };
    virtual bool actionThrustUpDown(int old, int abs) { return false; };
    virtual bool actionYaw(int old, int abs) { return false; };
    virtual bool actionPitch(int old, int abs) { return false; };
    virtual bool actionRoll(int old, int abs) { return false; };

    /**
     *     @}
     *     @defgroup button-actions
     *         Events that can be triggered by input on a button (e.g. a
     *         keyboard).
     *         @see ButtonAction
     *     @{
     */
    /** Default implementations have no effect */
    virtual bool actionDefault(bool isActive) { return false; };
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
    /**
     *     @}
     * @}
     */
};

/**
 * Axis actions are triggered when an axis is moved.
 *
 * The action is provided with the old absolute position of the axis, along with
 * the new absolute position of the axis.
 */
typedef bool ((Actionable::*AxisAction)(int old, int abs));

/**
 * Button actions are triggered when a button state has changed.
 *
 * The action is provided with the current state of the button.
 */
typedef bool ((Actionable::*ButtonAction)(bool isPressed));

#endif

