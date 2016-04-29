#pragma once

#include <OGRE/OgreMovableObject.h>

namespace sts {

/** Object that is to be spawned by IRenderable inherit classes and to be
  * given to object.
  */

class IAttachable
{
public:
	virtual Ogre::MovableObject* getAttachable() = 0;
	virtual const Ogre::MovableObject* getAttachable() const = 0;
};

} // namespace sts
