#include <OgreRoot.h>
#include <OgreViewport.h>
#include <Shapes/OgreBulletCollisionsSphereShape.h>

#include "Level.h"

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

void Level::loadResources() {
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(this->name);
}

void Level::unloadResources() {
    Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(this->name);
}

void Level::buildScene() {
    scene->setSkyBox(true, "Sky/Stars");
    scene->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));

    EntityProperties planetProperties;
    planetProperties.name = "Planet";
    planetProperties.mass = 10000000.0f;
    planetProperties.position = Ogre::Vector3(200, 0, 0);
    entities->createPlanet(planetProperties);

    Ogre::SceneNode* light = scene->getRootSceneNode()->createChildSceneNode("Light", Ogre::Vector3(200, 20, 0), Ogre::Quaternion::IDENTITY);
    light->attachObject(scene->createLight("Light"));

    camera = scene->createCamera("Camera");
    camera->setNearClipDistance(5);

    EntityProperties shipProperties;
    shipProperties.name = "Ship/Cruiser";
    shipProperties.material = "Steel";
    shipProperties.mesh = "Cruiser.mesh";
    shipProperties.mass = 1000.0f;
    ship = entities->createShip(shipProperties);
    ship->attachCamera(camera, Ogre::Vector3(0, 20, 120));
    ship->setMovementSpeeds(Ogre::Real(1000), Ogre::Real(500), Ogre::Real(1000));
    ship->setRotationSpeeds(Ogre::Real(100000), Ogre::Real(100000), Ogre::Real(100000));

    Keymap* oldKeymap = player->setKeymap(new Keymap("../res/keymap/pilot.xml"));
    delete oldKeymap;
}

void Level::launch(Ogre::RenderWindow* window) {
    window->removeAllViewports();
    Ogre::Viewport* viewport = window->addViewport(camera, 0, 0, 0, 1, 1);
    viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
    player->control(ship);
}

bool Level::update(Ogre::Real deltaTime) {
    entities->update(deltaTime);
    world->stepSimulation(deltaTime);
    return player->update(deltaTime);
}
