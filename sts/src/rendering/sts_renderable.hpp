#pragma once

#include <string>

#include <OGRE/OgreSceneNode.h>

#include "sts_attachable.hpp"

namespace sts {

class Renderable
{
public:
	Renderable(std::string name);
	virtual ~Renderable();

	std::string name() const;
	virtual IAttachable* _spawnAttachable(Ogre::SceneNode* node) const = 0;

private:
	std::string _name;
};

} // namespace sts
