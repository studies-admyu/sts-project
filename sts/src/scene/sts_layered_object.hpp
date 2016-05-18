#pragma once

#include "sts_scene_object.hpp"

namespace sts {

class Layer;

class LayeredObject: public SceneObject
{
public:
	static LayeredObject* create(Renderable* renderable, unsigned int layerIndex);
	static LayeredObject* create(Renderable* renderable, Layer* layer);
	~LayeredObject();

	void _setLayer(Layer* layer);

	Layer* layer();
	const Layer* layer() const;

	IAttachable* attachable();

	void setPosition(const Position& pos);
	Position position() const;

	virtual void processObject();

protected:
	LayeredObject(Renderable* renderable, unsigned int layerIndex);
	LayeredObject(Renderable* renderable, Layer* layer);

private:
	Layer* _layer;
	/** @todo Replace frameCounter with the timer */
	unsigned int _frameCounter;

	LayeredObject(const LayeredObject&);
};

} // namespace sts