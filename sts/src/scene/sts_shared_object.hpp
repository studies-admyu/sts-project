#pragma once

#include "sts_scene_object.hpp"

namespace sts {

class SharedObject: public SceneObject
{
public:
	SharedObject(Ogre::Node* node, IAttachable* attachable);
	~SharedObject();
	
	void setPosition(const Position& pos);
	Position position() const;
};

} // namespace sts
