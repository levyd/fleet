#include <OgreEntity.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>

#include "Entity.h"

/**
 * Constructor.
 *
 * Assigns a default value to each property. Some defaults are not suitable for
 * construction of the described object, and must be set manually.
 */
EntityProperties::EntityProperties() : name(""), material(""), mesh(""),
    position(Ogre::Vector3::ZERO), orientation(Ogre::Quaternion::IDENTITY),
    linearFactor(0.1f), angularFactor(1.0f),
    restitution(0.3f), friction(0.6f), mass(1000.0f) {
}

/**
 * Constructor.
 *
 * If @a entity has not been specified or is @c null, this constructor will
 * first build a new Ogre::Entity from the fields in @a properties, and then use
 * it to create an @c Entity.
 *
 * If @a entity is not null, this constructor will use it instead of building a
 * new Ogre::Entity.
 */
Entity::Entity(Ogre::SceneManager* scene, OgreBulletDynamics::DynamicsWorld*
        world, EntityProperties& properties, Ogre::Entity* entity) :
    scene(scene), angular(Ogre::Quaternion::IDENTITY) {

    if(entity == NULL) {
        entity = scene->createEntity(properties.name, properties.mesh);
    }

    this->node = scene->getRootSceneNode()->createChildSceneNode(properties.name);

    this->entity = entity;
    if(!properties.material.empty()) {
        this->entity->setMaterialName(properties.material);
    }
    node->attachObject(this->entity);

    Ogre::Vector3 size = this->entity->getBoundingBox().getSize() * 0.48f;
    OgreBulletCollisions::BoxCollisionShape* shape;
    shape = new OgreBulletCollisions::BoxCollisionShape(size);

    this->body = new OgreBulletDynamics::RigidBody(properties.name, world);
    this->body->setShape(this->node, shape, properties.restitution,
            properties.friction, properties.mass, properties.position,
            properties.orientation);
    btVector3 linearFactor = btVector3(properties.linearFactor,
            properties.linearFactor, properties.linearFactor);
    this->body->getBulletRigidBody()->setLinearFactor(linearFactor);
    btVector3 angularFactor = btVector3(properties.angularFactor,
            properties.angularFactor, properties.angularFactor);
    this->body->getBulletRigidBody()->setAngularFactor(angularFactor);
}

/**
 * Destructor.
 *
 * A game entity is responsible for destroying:
 * - The physics simulation's body,
 * - The rendering engine's scene node, and
 * - The rendering engine's visible entity.
 */
Entity::~Entity() {
    if(this->body != NULL) { delete this->body; }
    if(this->node != NULL) { scene->destroySceneNode(this->node); }
    if(this->entity != NULL) { scene->destroyEntity(this->entity); }
}

/**
 * Attach a camera to this entity.
 *
 * An attached camera will maintain a position relative to this Entity, moving
 * around the environment along with it. The relative position is specified as
 * an offset from this Entity's scene node.
 *
 * @param camera
 *     the Ogre Camera to attach to this entity.
 * @param offset
 *     Where to affix the camera in relation to this Entity's central scene
 *     node.
 *
 */
void Entity::attachCamera(Ogre::Camera* camera, Ogre::Vector3 offset) {
    this->node->createChildSceneNode(offset, Ogre::Quaternion::IDENTITY)->attachObject(camera);
    camera->lookAt(node->getPosition());
}


/**
 * Update the state of this object after a game timestep.
 *
 * @param deltaTime 
 *     The interval of time that has passed since the last update.
 */
bool Entity::update(Ogre::Real deltaTime) {
    return true;
}

