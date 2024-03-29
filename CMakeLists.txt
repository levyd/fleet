cmake_minimum_required(VERSION 2.6)
 
project(fleet)
 
if(WIN32)
    set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
    set(OGRE_SAMPLES_INCLUDEPATH
        $ENV{OGRE_HOME}/Samples/include
    )
endif(WIN32)
 
if(UNIX)
    if(EXISTS "/usr/local/lib/OGRE/cmake")

      set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
      set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/")

    elseif(EXISTS "/usr/lib/OGRE/cmake")

      set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
      set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/")

    else ()
      message(SEND_ERROR "Failed to find module path.")
    endif(EXISTS "/usr/local/lib/OGRE/cmake")
endif(UNIX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
 
set(CMAKE_DEBUG_POSTFIX "_d")
 
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}")
 
find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)
find_package(BULLET REQUIRED)
find_package(OGREBULLET REQUIRED)

# Find Boost
if (NOT OGRE_BUILD_PLATFORM_IPHONE)
    if (WIN32 OR APPLE)
        set(Boost_USE_STATIC_LIBS TRUE)
    else ()
        # Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
        set(Boost_USE_STATIC_LIBS ${OGRE_STATIC})
    endif ()
    if (MINGW)
        # this is probably a bug in CMake: the boost find module tries to look for
        # boost libraries with name libboost_*, but CMake already prefixes library
        # search names with "lib". This is the workaround.
        set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
    endif ()
    set(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
    # Components that need linking (NB does not include header-only components like bind)
    set(OGRE_BOOST_COMPONENTS thread date_time)
    find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
    if (NOT Boost_FOUND)
        # Try again with the other type of libs
        set(Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
        find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
    endif()
    find_package(Boost QUIET)
 
    # Set up referencing of Boost
    include_directories(${Boost_INCLUDE_DIR})
    add_definitions(-DBOOST_ALL_NO_LIB)
    set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
endif()
 
include(SourceFiles.cmake)

include_directories(
    ./lib/rapidxml-1.13
    ${OIS_INCLUDE_DIRS}
    ${OGRE_INCLUDE_DIRS}
    ${BULLET_INCLUDE_DIRS}
    ${OGREBULLET_INCLUDE_DIRS}
    ${OGRE_SAMPLES_INCLUDEPATH}
)
 
add_executable(fleet WIN32 ${HDRS} ${SRCS})

include(test/Tests.cmake)
 
set_target_properties(fleet PROPERTIES DEBUG_POSTFIX _d)
 
target_link_libraries(fleet ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${BULLET_LIBRARIES} ${OGREBULLET_LIBRARIES})
 
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
 
add_custom_command(TARGET fleet POST_BUILD COMMAND ctags -R ${CMAKE_SOURCE_DIR}/src
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating ctags" VERBATIM
)

# post-build copy for win32
if(WIN32 AND NOT MINGW)
    add_custom_command( TARGET fleet PRE_BUILD
        COMMAND if not exist .\\bin mkdir .\\bin )
    add_custom_command( TARGET fleet POST_BUILD
        COMMAND copy "\"$(TargetPath)\"" .\\bin )
endif(WIN32 AND NOT MINGW)

if(MINGW OR UNIX)
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
endif(MINGW OR UNIX)
 
if(WIN32)
 
    install(TARGETS fleet
        RUNTIME DESTINATION bin
        CONFIGURATIONS All)
 
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/res
        DESTINATION ./
        CONFIGURATIONS Release RelWithDebInfo Debug
    )
 
    install(FILES ${CMAKE_SOURCE_DIR}/bin/plugins.cfg
        ${CMAKE_SOURCE_DIR}/bin/resources.cfg
        DESTINATION bin
        CONFIGURATIONS Release RelWithDebInfo
    )
 
    install(FILES ${CMAKE_SOURCE_DIR}/bin/plugins_d.cfg
        ${CMAKE_SOURCE_DIR}/bin/resources_d.cfg
        DESTINATION bin
        CONFIGURATIONS Debug
    )
 
        # NOTE: for the 1.7.1 sdk the OIS dll is called OIS.dll instead of libOIS.dll
        # so you'll have to change that to make it work with 1.7.1
    install(FILES ${OGRE_PLUGIN_DIR_REL}/OgreMain.dll
        ${OGRE_PLUGIN_DIR_REL}/RenderSystem_Direct3D9.dll
        ${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL.dll
        ${OGRE_PLUGIN_DIR_REL}/libOIS.dll
        DESTINATION bin
        CONFIGURATIONS Release RelWithDebInfo
    )
 
    install(FILES ${OGRE_PLUGIN_DIR_DBG}/OgreMain_d.dll
        ${OGRE_PLUGIN_DIR_DBG}/RenderSystem_Direct3D9_d.dll
        ${OGRE_PLUGIN_DIR_DBG}/RenderSystem_GL_d.dll
        ${OGRE_PLUGIN_DIR_DBG}/libOIS_d.dll
        DESTINATION bin
        CONFIGURATIONS Debug
    )
 
   # as of sdk 1.7.2 we need to copy the boost dll's as well
   # because they're not linked statically (it worked with 1.7.1 though)
   install(FILES ${Boost_DATE_TIME_LIBRARY_RELEASE}
      ${Boost_THREAD_LIBRARY_RELEASE}
      DESTINATION bin
      CONFIGURATIONS Release RelWithDebInfo
   )
 
   install(FILES ${Boost_DATE_TIME_LIBRARY_DEBUG}
      ${Boost_THREAD_LIBRARY_DEBUG}
      DESTINATION bin
      CONFIGURATIONS Debug
   )
endif(WIN32)

if(UNIX)
 
    install(TARGETS fleet
        RUNTIME DESTINATION bin
        CONFIGURATIONS All)
 
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/res
        DESTINATION ./
        CONFIGURATIONS Release RelWithDebInfo Debug
    )
 
    install(FILES ${CMAKE_SOURCE_DIR}/bin/plugins.cfg
        ${CMAKE_SOURCE_DIR}/bin/resources.cfg
        DESTINATION bin
        CONFIGURATIONS Release RelWithDebInfo Debug
    )
 
endif(UNIX)
 
