#ifndef _BODY_H_
#define _BODY_H_

#include <OgreSceneManager.h>

class Body {
public:
	Body(Ogre::SceneManager* sceneMgr, Ogre::Vector3 position, std::string bodyName);
    virtual ~Body();
      
    virtual bool Update(Ogre::Real deltaTime);
    const Ogre::Vector3 GetPosition() { return this->bodyNode->getPosition(); }
    Ogre::SceneNode* GetSceneNode() { return this->bodyNode; }

protected:
    Ogre::SceneNode* bodyNode;
    const std::string name;
    Ogre::Vector3 velocity;
    Ogre::Quaternion angular;

};

#endif
