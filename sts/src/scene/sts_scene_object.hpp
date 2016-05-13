#pragma once

#include <OGRE/OgreSceneNode.h>

#include <rendering/sts_renderable.hpp>

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

	SceneObject(Ogre::SceneNode* node, Renderable* renderable);
	virtual ~SceneObject();

	bool isVisible() const;
	void setVisible(bool value);
	virtual void setPosition(const Position& pos) = 0;
	virtual Position position() const = 0;
	void setPlanarRotation(float radians);
	float planarRotation() const;
	void setAxisRotation(float radians);
	float axisRotation() const;
	virtual void processObject();

protected:
	IAttachable* attachable();

private:
	IAttachable* _attachable;

	SceneObject(const SceneObject&);
};

} // namespace sts
