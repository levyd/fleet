#include <OgreRoot.h>
#include <OgreViewport.h>
#include <Shapes/OgreBulletCollisionsSphereShape.h>

#include "Level.h"
#include "entity/weapon/MissileLauncher.h"

/**
 * Constructor.
 *
 * @param levelName
 *     The unique name for this level. This name will be used to load the
 *     level's resource group.
 * @param inputManager
 *     The OIS InputManager to acquire input devices from. This will more than
 *     likely be refactored once Application supports more than one level.
 */
Level::Level(const std::string& levelName, OIS::InputManager* inputManager) :
    camera(0), ship(0) {
    this->name = levelName;

    scene = Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC, levelName);
    Ogre::AxisAlignedBox bounds = Ogre::AxisAlignedBox(
            Ogre::Vector3(-10000, -10000, -10000), Ogre::Vector3(-10000, -10000, -10000));
    world = new OgreBulletDynamics::DynamicsWorld(scene, bounds, Ogre::Vector3(0, 0, 0));

    OgreBulletCollisions::DebugDrawer* debugDrawer;
    debugDrawer = new OgreBulletCollisions::DebugDrawer();
    debugDrawer->setDrawWireframe(true);
    world->setDebugDrawer(debugDrawer);
    world->setShowDebugShapes(true);
    Ogre::SceneNode *debugNode =
        scene->getRootSceneNode()->createChildSceneNode("debugDrawer",
                Ogre::Vector3::ZERO);
    debugNode->attachObject(static_cast <Ogre::SimpleRenderable *>
            (debugDrawer));

    entities = new EntityManager(scene, world);

    player = new Player(inputManager);
    //TODO!
    //player.setKeymap();
}


Level::~Level() {
    if(player != NULL) { delete player; }
    if(entities != NULL) { delete entities; }
    if(world != NULL) { delete world; }
    if(scene != NULL) { Ogre::Root::getSingleton().destroySceneManager(scene); }
}

/** Loads this level's resources. */
void Level::loadResources() {
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(this->name);
}

/** Unloads this level's resources. */
void Level::unloadResources() {
    Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(this->name);
}

/**
 * Constructs the visible entities that are specific to this scene.
 */
void Level::buildScene() {
    scene->setSkyBox(true, "Sky/Galaxy");
    scene->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));

    EntityProperties planetProperties;
    planetProperties.name = "Planet";
    planetProperties.mass = 10000000.0f;
    planetProperties.position = Ogre::Vector3(200, 0, 0);
    entities->createPlanet(planetProperties);

    Ogre::SceneNode* light = scene->getRootSceneNode()->createChildSceneNode(
            "Light", Ogre::Vector3(200, 20, 0), Ogre::Quaternion::IDENTITY);
    light->attachObject(scene->createLight("Light"));

    camera = scene->createCamera("Camera");
    camera->setNearClipDistance(5);

    EntityProperties shipProperties;
    shipProperties.name = "Ship/Fighter";
    shipProperties.material = "Fighter";
    shipProperties.mesh = "Fighter.mesh";
    shipProperties.mass = 1000.0f;
    ship = entities->createShip(shipProperties);
    ship->attachCamera(camera, Ogre::Vector3(0, 5, 20));
    ship->setMovementSpeeds(Ogre::Real(10000), Ogre::Real(5000), Ogre::Real(10000));
    ship->setRotationSpeeds(
            Ogre::Real(10000), Ogre::Real(10000), Ogre::Real(10000));

    MissileLauncher* launcher = 
        new MissileLauncher(ship, Ogre::Vector3(10, 0, 0), this->entities);
    ship->attachWeapon(launcher);

    Keymap* oldKeymap = player->setKeymap(new Keymap("../res/keymap/pilot.xml"));
    delete oldKeymap;

    EntityProperties targetProperties;
    targetProperties.name = "Ship/Cruiser";
    targetProperties.material = "Steel";
    targetProperties.mesh = "Cruiser.mesh";
    targetProperties.position = Ogre::Vector3(0, 0, -70);
    entities->createShip(targetProperties);
}

/**
 * Activates this level.
 *
 * Attaches this level to @a window, which makes the level visible, and
 * activates player control of the appropriate entities.
 *
 * @param window
 *     The Ogre RenderWindow to attach this level to.
 */
void Level::launch(Ogre::RenderWindow* window) {
    window->removeAllViewports();
    Ogre::Viewport* viewport = window->addViewport(camera, 0, 0, 0, 1, 1);
    viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
    player->control(ship);
}

/**
 * Update the state of this level after a game timestep.
 *
 * Updates the elements of this level, in the following order:
 * 1. each Entity's internal state,
 * 2. the physics simulation,
 * 3. player input.
 *
 * @param deltaTime 
 *     The interval of time that has passed since the last update.
 */
bool Level::update(Ogre::Real deltaTime) {
    entities->update(deltaTime);
    world->stepSimulation(deltaTime);
    return player->update(deltaTime);
}
