#ifndef _ARMED_H_
#define _ARMED_H_

#include "Actionable.h"
#include "weapon/Weapon.h"

/**
 * Manages and fires weapon systems.
 *
 * @ingroup entity-modules
 */
class Armed : virtual public Actionable {
public:
    Armed();
    virtual ~Armed();

    void attachWeapon(Weapon* weapon);
    void removeWeapon(Weapon* weapon);
    bool update(Ogre::Real deltaTime);

    virtual bool actionWeaponFire(bool isActive);
    virtual bool actionWeaponNext(bool isActive);
    virtual bool actionWeaponPrevious(bool isActive);
    //virtual bool actionTargetNext(bool isActive);
    //virtual bool actionTargetPrevious(bool isActive);

private:
    std::vector<Weapon*> weapons;
    unsigned index;
};

#endif

