#pragma once

#include <string>

#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreEntity.h>

#include "sts_renderable.hpp"

namespace sts {

class Model3DAttachable: public IAttachable
{
friend class Model3D;

public:
	Ogre::MovableObject* getAttachable();
	const Ogre::MovableObject* getAttachable() const;

private:
	Ogre::Entity* _attachableEntity;

	/** May be created only by a friend class */
	Model3DAttachable(Ogre::Entity* entity);
	/** May be copied only by a friend class */
	Model3DAttachable(const Model3DAttachable&);
};

class Model3D: public IRenderable
{
public:
	/** Creates a 3D model from a *.mesh file
	  * @arg sceneManager - OGRE scene manager instance;
	  * @arg modelFilename - name of the *.mesh file.
	  */
	Model3D(Ogre::SceneManager* sceneManager, std::string modelFilename);
	IAttachable* spawnAttachable() const;
	std::string modelFilename() const;

private:
	Ogre::SceneManager* _sceneManager;
	std::string _modelFilename;

	/** Duplicating is prohibited */
	Model3D(const Model3D&);
};

} // namespace sts
