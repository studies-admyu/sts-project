#pragma once

#include <OGRE/OgreBillboard.h>

#include "sts_attachable.hpp"

namespace sts {

class Sprite2DAttachable: public IAttachable
{
friend class Sprite2D;

public:
	~Sprite2DAttachable();

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
	Ogre::Billboard* _attachableBillboard;
	Ogre::SceneNode* _node;

	/** May be created only by a friend class */
	Sprite2DAttachable(Ogre::SceneNode* node, Ogre::Billboard* billboard);
	/** May be copied only by a friend class */
	Sprite2DAttachable(const Sprite2DAttachable&);
};

} // namespace sts
