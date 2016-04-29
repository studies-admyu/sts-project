#include "sts_model3d.hpp"

namespace sts {

/* Model3DAttachable class */

Model3DAttachable::Model3DAttachable(Ogre::Entity* entity):
	_node(nullptr), _attachableEntity(entity)
{

}

Model3DAttachable::Model3DAttachable(const Model3DAttachable& m3dattachable):
	_node(m3dattachable._node), _attachableEntity(m3dattachable._attachableEntity)
{

}

Model3DAttachable::~Model3DAttachable()
{

}

void Model3DAttachable::updateRotation()
{
	Ogre::Quaternion orientation = Ogre::Quaternion(Ogre::Radian(this->_axisRotation), Ogre::Vector3(0, 0, 1));
	orientation = orientation * Ogre::Quaternion(Ogre::Radian(this->_planarRotation), Ogre::Vector3(0, 1, 0));
	this->_node->setOrientation(orientation);
}

void Model3DAttachable::attachToNode(Ogre::Node* node)
{
	this->_node = node;
}

void Model3DAttachable::setPosition3D(const Ogre::Vector3& position)
{
	this->_node->setPosition(position);
}

Ogre::Vector3 Model3DAttachable::position3D() const
{
	return this->_node->getPosition();
}

void Model3DAttachable::setPlanarRotation(float radians)
{
	this->_planarRotation = radians;
	this->updateRotation();
}

float Model3DAttachable::planarRotation() const
{
	return this->_planarRotation;
}

void Model3DAttachable::setAxisRotation(float radians)
{
	this->_axisRotation = radians;
	this->updateRotation();
}

float Model3DAttachable::axisRotation() const
{
	return this->_axisRotation;
}

void Model3DAttachable::setVisible(bool value)
{
	this->_attachableEntity->setVisible(value);
}

bool Model3DAttachable::isVisible() const
{
	return this->_attachableEntity->getVisible();
}

void Model3DAttachable::update()
{

}

/* Model3D class */

Model3D::Model3D(Ogre::SceneManager* sceneManager, std::string modelFilename):
	_sceneManager(sceneManager), _modelFilename(modelFilename)
{

}

Model3D::Model3D(const Model3D& model):
	_modelFilename(model._modelFilename)
{

}

Model3D::~Model3D()
{

}

IAttachable* Model3D::spawnAttachable() const
{
	Ogre::Entity* entity = _sceneManager->createEntity(this->_modelFilename);
	/** @todo Make a decision about shadows - switched off for now */
	entity->setCastShadows(false);

	Model3DAttachable* attachable = new Model3DAttachable(entity);
	return attachable;
}

std::string Model3D::modelFilename() const
{
	return this->_modelFilename;
}

} // namespace sts
