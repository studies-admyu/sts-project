#pragma once

#include <OGRE/OgreEntity.h>

#include "sts_attachable.hpp"

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

} // namespace sts
