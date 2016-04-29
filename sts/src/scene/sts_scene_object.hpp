#pragma once

#include <OGRE/OgreNode.h>

#include <rendering/sts_attachable.hpp>

namespace sts {

class SceneObject
{
friend class SceneManager;

public:
	struct Position
	{
		int x;
		int y;
	};

	SceneObject(Ogre::Node* node, IAttachable* attachable);
	~SceneObject();

	bool isVisible() const;
	void setVisible(bool value);
	virtual void setPosition(const Position& pos) = 0;
	virtual Position position() const = 0;
	void setPlanarRotation(float radians);
	float planarRotation() const;
	void setAxisRotation(float radians);
	float axisRotation() const;

protected:
	IAttachable* attachable();

private:
	Ogre::Node* _objectNode;
	IAttachable* _attachable;

	SceneObject(const SceneObject&);
};

} // namespace sts
