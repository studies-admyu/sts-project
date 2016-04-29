#pragma once

#include "sts_scene_object.hpp"

namespace sts {

class Layer;

class LayeredObject: public SceneObject
{
public:
	LayeredObject(Ogre::Node* node, IAttachable* attachable, Layer* layer = nullptr);
	~LayeredObject();
	
	Layer* layer();
	const Layer* layer() const;
	
	void setPosition(const Position& pos);
	Position position() const;

private:
	Layer* _layer;
};

} // namespace sts
