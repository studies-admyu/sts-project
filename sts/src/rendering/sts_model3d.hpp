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
	~Model3DAttachable();

	void setPosition3D(const Ogre::Vector3& position);
	Ogre::Vector3 position3D() const;
	Ogre::SceneNode* node();
	const Ogre::SceneNode* node() const;
	void setPlanarRotation(float radians);
	float planarRotation() const;
	void setAxisRotation(float radians);
	float axisRotation() const;
	void setVisible(bool value);
	bool isVisible() const;
	void update();

private:
	Ogre::SceneNode* _node;
	Ogre::Entity* _attachableEntity;
	float _planarRotation;
	float _axisRotation;

	/** May be created only by a friend class */
	Model3DAttachable(Ogre::SceneNode* node, Ogre::Entity* entity);
	/** May be copied only by a friend class */
	Model3DAttachable(const Model3DAttachable&);

	/** Updates model rotation */
	void updateRotation();
};

class Model3D: public IRenderable
{
public:
	/** Creates a 3D model from a *.mesh file
	  * @arg sceneManager - OGRE scene manager instance;
	  * @arg modelFilename - name of the *.mesh file.
	  */
	Model3D(Ogre::SceneManager* sceneManager, std::string modelFilename, float scale = 1.0f);
	~Model3D();
	IAttachable* spawnAttachable(Ogre::SceneNode* node) const;
	std::string modelFilename() const;
	float scale() const;

private:
	Ogre::SceneManager* _sceneManager;
	std::string _modelFilename;
	float _modelScale;

	/** Duplicating is prohibited */
	Model3D(const Model3D&);
};

} // namespace sts
