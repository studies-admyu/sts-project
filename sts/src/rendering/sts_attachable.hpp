#pragma once

#include <OGRE/OgreNode.h>

namespace sts {

/** Object that is to be spawned by IRenderable inherit classes and to be
  * given to object.
  */

class IAttachable
{
public:
	virtual ~IAttachable()
		{}

	virtual void setPosition3D(const Ogre::Vector3& position) = 0;
	virtual Ogre::Vector3 position3D() const = 0;
	virtual Ogre::SceneNode* node() = 0;
	virtual const Ogre::SceneNode* node() const = 0;
	virtual void setPlanarRotation(float radians) = 0;
	virtual float planarRotation() const = 0;
	virtual void setAxisRotation(float radians) = 0;
	virtual float axisRotation() const = 0;
	virtual void setVisible(bool value) = 0;
	virtual bool isVisible() const = 0;
	virtual void update() = 0;
};

} // namespace sts
