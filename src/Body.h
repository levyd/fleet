#ifndef _BODY_H_
#define _BODY_H_

#include <OgreSceneManager.h>

class Body {
public:
	Body(Ogre::SceneManager* sceneMgr, Ogre::Vector3 position);
    virtual ~Body();
      
    void AttachCamera(Ogre::Camera*& camera, Ogre::Vector3 offset);

    virtual bool Update(Ogre::Real deltaTime);

    Ogre::SceneNode* getSceneNode() { return this->bodyNode; }
    const Ogre::Vector3 getPosition() { return this->bodyNode->getPosition(); }
    const Ogre::Vector3 getVelocity() { return this->velocity; }
    const Ogre::Quaternion getAngular() { return this->angular; }

protected:
    Ogre::SceneManager* scene;
    Ogre::SceneNode* bodyNode;
    Ogre::Vector3 velocity;
    Ogre::Quaternion angular;

};

#endif
