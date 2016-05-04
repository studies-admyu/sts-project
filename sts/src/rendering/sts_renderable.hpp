#pragma once

#include <OGRE/OgreSceneNode.h>

#include "sts_attachable.hpp"

namespace sts {

class IRenderable
{
public:
	virtual IAttachable* spawnAttachable(Ogre::SceneNode* node) const = 0;
};

} // namespace sts
