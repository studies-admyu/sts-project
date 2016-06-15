#include "sts_scene_object.hpp"

#include <cmath>
#include <stdexcept>

#include <OGRE/OgreSceneNode.h>

#include <sts_game_root.hpp>

namespace sts {

SceneObject::SceneObject(Renderable* renderable)
{
	sts::SceneManager* sceneManager = GameRoot::getObject()->sceneManager();
	Ogre::SceneNode* attachableNode = sceneManager->_spawnObjectNode();
	this->_attachable = std::unique_ptr<IAttachable>(renderable->_spawnAttachable(attachableNode));
}

SceneObject::SceneObject(std::string renderableName):
	SceneObject(sts::GameRoot::getObject()->getRenderable(renderableName)) { }

SceneObject::SceneObject(const SceneObject& sceneobj):
	_attachable(nullptr)
{
	throw std::runtime_error("SceneObject is not copyable");
}

SceneObject::~SceneObject()
{
	Ogre::SceneNode* attachableNode = this->_attachable->node();
	attachableNode->detachAllObjects();
	sts::GameRoot::getObject()->sceneManager()->_destroyNode(attachableNode);
}

IAttachable* SceneObject::attachable()
{
	return this->_attachable.get();
}

const IAttachable* SceneObject::attachable() const
{
	return this->_attachable.get();
}

bool SceneObject::isVisible() const
{
	return this->_attachable->isVisible();
}

void SceneObject::setVisible(bool value)
{
	this->_attachable->setVisible(value);
}

void SceneObject::setPosition(const SceneObject::Position& pos)
{
	int sceneWidth = sts::GameRoot::getObject()->sceneManager()->sceneWidth();
	this->_attachable->setPosition3D(Ogre::Vector3(float(sceneWidth - pos.x), 0.0f, float(pos.y)));
}

SceneObject::Position SceneObject::position() const
{
	Ogre::Vector3 attachablePos = this->_attachable->position3D();
	int sceneWidth = sts::GameRoot::getObject()->sceneManager()->sceneWidth();
	Position returnValue(
		static_cast<int>(floor(sceneWidth - attachablePos.x)),
		static_cast<int>(floor(attachablePos.z))
	);
	return returnValue;
}

void SceneObject::setPlanarRotation(float radians)
{
	this->_attachable->setPlanarRotation(-radians);
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
