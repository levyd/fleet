#include "TestFramework.h"
#include "../src/control/Keymap.h"

int main(int argc, char* argv[]) {
    BEGINTEST(argv[0]);
    Keymap keymap("../res/keymap/pilot.xml");

    AxisAction axisActionDefault = &Actionable::actionDefault;
    AxisAction actionFwd = keymap.js[0]->getAxisAction(0);
    ASSERT(actionFwd != axisActionDefault);

    ButtonAction buttonActionDefault = &Actionable::actionDefault;
    ButtonAction actionW = keymap.kb.getButtonAction(OIS::KC_W);
    ASSERT(actionW != buttonActionDefault);

    TESTSUCCEED;
}

