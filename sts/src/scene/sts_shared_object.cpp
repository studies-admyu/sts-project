#include "sts_shared_object.hpp"

namespace sts {

SharedObject::SharedObject(Ogre::Node* node, IAttachable* attachable):
	SceneObject(node, attachable)
{
	
}

SharedObject::~SharedObject()
{
	
}

void SharedObject::setPosition(const SceneObject::Position& pos)
{
	
}

SceneObject::Position SharedObject::position() const
{
	SceneObject::Position returnValue = {0, 0};
	return returnValue;
}

} // namespace sts
