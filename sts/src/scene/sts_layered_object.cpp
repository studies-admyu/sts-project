#include "sts_layered_object.hpp"

#include <sts_game_root.hpp>

namespace sts {

LayeredObject::LayeredObject(Renderable* renderable, unsigned int layerIndex):
	SceneObject(renderable)
{
	this->initObject(sts::GameRoot::getObject()->sceneManager()->layer(layerIndex));
}

LayeredObject* LayeredObject::create(std::string renderableName, unsigned int layerIndex)
{
	return LayeredObject::create(
		sts::GameRoot::getObject()->getRenderable(renderableName),
		layerIndex
	);
}

LayeredObject::LayeredObject(Renderable* renderable, Layer* layer):
	SceneObject(renderable)
{
	this->initObject(layer);
}

LayeredObject* LayeredObject::create(std::string renderableName, Layer* layer)
{
	return LayeredObject::create(
		sts::GameRoot::getObject()->getRenderable(renderableName),
		layer
	);
}

LayeredObject::~LayeredObject()
{

}

LayeredObject* LayeredObject::create(Renderable* renderable, unsigned int layerIndex)
{
	return new LayeredObject(renderable, layerIndex);
}

LayeredObject* LayeredObject::create(Renderable* renderable, Layer* layer)
{
	return new LayeredObject(renderable, layer);
}

void LayeredObject::initObject(Layer* layer)
{
	this->_layer = layer;
	this->_frameCounter = 0;
	this->_layer->addObject(this);
}

void LayeredObject::_setLayer(Layer* layer)
{
	this->_layer = layer;
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
	SceneObject::Position returnValue(0, 0);
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
