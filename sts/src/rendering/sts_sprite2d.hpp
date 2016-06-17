#pragma once

#include <OGRE/OgreBillboardSet.h>

#include "sts_renderable.hpp"

namespace sts {

class Sprite2D: public Renderable
{
public:
	struct Size
	{
		Size(unsigned int swidth, unsigned int sheight):
			width(swidth), height(sheight) { }

		unsigned int width;
		unsigned int height;
	};

	/** Creates a sprite from OGRE material
	  * @arg sceneManager - OGRE scene manager instance;
	  * @arg spriteFilename - name of the OGRE material.
	  */
	static Sprite2D* create(std::string name, std::string matName, Size ssize);

	~Sprite2D();
	IAttachable* _spawnAttachable(Ogre::SceneNode* node) const;
	std::string materialName() const;
	Size size() const;

private:
	std::string _materialName;
	Size _size;
	Ogre::BillboardSet* _billboardSet;
	Ogre::SceneNode* _node;

	/** Default constructor is private to prevent creation via new */
	Sprite2D(std::string name, std::string matName, Size ssize);

	/** Duplicating is prohibited */
	Sprite2D(const Sprite2D&);
};

} // namespace sts
