#include "sts_layered_object.hpp"

#include <cmath>

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
	this->_zeroMsec = 0;
	this->_offsetY = 0;
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
	SceneObject::Position newPos = pos + SceneObject::Position(0, this->_offsetY);
	SceneObject::setPosition(newPos);
}

SceneObject::Position LayeredObject::position() const
{
	SceneObject::Position returnValue = SceneObject::position();
	returnValue = returnValue - SceneObject::Position(0, this->_offsetY);
	return returnValue;
}

void LayeredObject::processObject(unsigned int msec)
{
	SceneObject::processObject(msec);

	if (this->isVisible()) {
		/* Update position */
		float offsetYf = float(msec - this->_zeroMsec);
		offsetYf = offsetYf * float(this->layer()->speed()) / 1000.0;
		sts::SceneObject::Position currentPosition = this->position();
		this->_offsetY = std::floor(offsetYf);
		this->setPosition(currentPosition);
	} else {
		this->_zeroMsec = msec;
	}
}

} // namespace sts
