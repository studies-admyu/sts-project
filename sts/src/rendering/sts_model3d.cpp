#include "sts_model3d.hpp"

namespace sts {

/* Model3DAttachable class */

Model3DAttachable::Model3DAttachable(Ogre::Entity* entity):
	_attachableEntity(entity)
{

}

Model3DAttachable::Model3DAttachable(const Model3DAttachable& m3dattachable):
	_attachableEntity(m3dattachable._attachableEntity)
{

}

Ogre::MovableObject* Model3DAttachable::getAttachable()
{
	return this->_attachableEntity;
}

const Ogre::MovableObject* Model3DAttachable::getAttachable() const
{
	return this->_attachableEntity;
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
