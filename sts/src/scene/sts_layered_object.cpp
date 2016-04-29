#include "sts_layered_object.hpp"

namespace sts {

LayeredObject::LayeredObject(Ogre::Node* node, IAttachable* attachable, Layer* layer):
	SceneObject(node, attachable), _layer(layer)
{
	attachable->attachToNode(node);
}

LayeredObject::~LayeredObject()
{
	
}
	
Layer* LayeredObject::layer()
{
	return this->_layer;
}

const Layer* LayeredObject::layer() const
{
	return this->_layer;
}
	
void LayeredObject::setPosition(const SceneObject::Position& pos)
{
	
}

SceneObject::Position LayeredObject::position() const
{
	SceneObject::Position returnValue = {0, 0};
	return returnValue;
}

} // namespace sts
