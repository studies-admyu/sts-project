#pragma once

#include "sts_scene_object.hpp"

namespace sts {

class Layer;

class LayeredObject: public SceneObject
{
public:
	LayeredObject(Ogre::SceneNode* node, Renderable* renderable, Layer* layer = nullptr);
	~LayeredObject();

	Layer* layer();
	const Layer* layer() const;

	IAttachable* attachable();

	void setPosition(const Position& pos);
	Position position() const;

	virtual void processObject();

private:
	Layer* _layer;
	/** @todo Replace frameCounter with the timer */
	unsigned int _frameCounter;
};

} // namespace sts
