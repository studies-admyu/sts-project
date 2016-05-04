#include "sts_shared_object.hpp"

namespace sts {

SharedObject::SharedObject(Ogre::SceneNode* node, IRenderable* renderable):
	SceneObject(node, renderable)
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
