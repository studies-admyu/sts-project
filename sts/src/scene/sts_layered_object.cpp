#include "sts_layered_object.hpp"

#include "sts_layer.hpp"

namespace sts {

LayeredObject::LayeredObject(Ogre::SceneNode* node, Renderable* renderable, Layer* layer):
	SceneObject(node, renderable), _layer(layer)
{
	this->_frameCounter = 0;
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

IAttachable* LayeredObject::attachable()
{
	return SceneObject::attachable();
}

void LayeredObject::setPosition(const SceneObject::Position& pos)
{

}

SceneObject::Position LayeredObject::position() const
{
	SceneObject::Position returnValue = {0, 0};
	return returnValue;
}

void LayeredObject::processObject()
{
	SceneObject::processObject();

	Ogre::Vector3 attachablePosition = this->attachable()->position3D();
	/* We use y coordinate instead of z */
	attachablePosition.y = this->layer()->z();
	this->attachable()->setPosition3D(attachablePosition);

	++this->_frameCounter;
	this->_frameCounter = this->_frameCounter % 1000;
	if (this->_frameCounter == 0) {
		SceneObject::Position objPosition = this->position();
		objPosition.y -= this->layer()->speed();
		this->setPosition(objPosition);
	}
}

} // namespace sts
