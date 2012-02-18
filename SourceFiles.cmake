set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall)

set(HDRS
    src/Application.h
    src/Controller.h
    src/ControllerPlayer.h
    src/Keymap.h
    src/Level.h
    src/entity/Actionable.h
    src/entity/Entity.h
    src/entity/EntityManager.h
    src/entity/Pilotable.h
    src/entity/Ship.h
)
 
set(SRCS
    src/Application.cpp
    src/Controller.cpp
    src/ControllerPlayer.cpp
    src/Keymap.cpp
    src/Level.cpp
    src/Main.cpp
    src/entity/Actionable.cpp
    src/entity/Entity.cpp
    src/entity/EntityManager.cpp
    src/entity/Pilotable.cpp
    src/entity/Ship.cpp
)
 
