#include "sts_scene_object.hpp"

namespace sts {

SceneObject::SceneObject(Ogre::SceneNode* node, IRenderable* renderable)
{
	this->_attachable = renderable->spawnAttachable(node);
}

SceneObject::SceneObject(const SceneObject& sceneobj):
	_attachable(sceneobj._attachable)
{

}

SceneObject::~SceneObject()
{

}

IAttachable* SceneObject::attachable()
{
	return this->_attachable;
}

bool SceneObject::isVisible() const
{
	return this->_attachable->isVisible();
}

void SceneObject::setVisible(bool value)
{
	this->_attachable->setVisible(value);
}

void SceneObject::setPlanarRotation(float radians)
{
	this->_attachable->setPlanarRotation(radians);
}

float SceneObject::planarRotation() const
{
	return this->_attachable->planarRotation();
}

void SceneObject::setAxisRotation(float radians)
{
	this->_attachable->setAxisRotation(radians);
}

float SceneObject::axisRotation() const
{
	return this->_attachable->axisRotation();
}

void SceneObject::processObject()
{

}

} // namespace sts
