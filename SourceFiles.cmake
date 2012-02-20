set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall)

set(HDRS
    src/Application.h
    src/Level.h
    src/control/Controller.h
    src/control/Player.h
    src/control/Joystick.h
    src/control/Keymap.h
    src/entity/Actionable.h
    src/entity/Entity.h
    src/entity/EntityManager.h
    src/entity/Pilotable.h
    src/entity/Ship.h
)
 
set(SRCS
    src/Application.cpp
    src/Level.cpp
    src/Main.cpp
    src/control/Controller.cpp
    src/control/Player.cpp
    src/control/Joystick.cpp
    src/control/Keymap.cpp
    src/entity/Entity.cpp
    src/entity/EntityManager.cpp
    src/entity/Pilotable.cpp
    src/entity/Ship.cpp
)
 
