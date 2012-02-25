# Target properties:
# WIN32 - Launches as GUI instead of console application on Windows (I think)
# EXCLUDE_FROM_ALL - Exclude the target from make's 'all' target, i.e. the
#                    default target

# Test: keymap
add_executable(keymap EXCLUDE_FROM_ALL
    src/control/Keymap.h src/control/NameMap.h src/entity/Actionable.h src/util/Xml.h test/TestFramework.h
    test/Keymap.cpp src/control/Keymap.cpp src/control/NameMap.cpp src/util/Xml.cpp
)
set_target_properties(keymap PROPERTIES DEBUG_POSTFIX _d)
target_link_libraries(keymap ${OIS_LIBRARIES})

