#include "sts_sprite2d.hpp"
#include "sts_sprite2d_attachable.hpp"

#include <stdexcept>

#include <sts_game_root.hpp>

namespace sts {

/* Sprite2DAttachable class */

Sprite2DAttachable::Sprite2DAttachable(Ogre::SceneNode* node, Ogre::Billboard* billboard):
	_node(node), _attachableBillboard(billboard)
{

}

Sprite2DAttachable::Sprite2DAttachable(const Sprite2DAttachable& s2dattachable):
	_node(s2dattachable._node), _attachableBillboard(s2dattachable._attachableBillboard)
{

}

Sprite2DAttachable::~Sprite2DAttachable()
{

}

void Sprite2DAttachable::setPosition3D(const Ogre::Vector3& position)
{
	this->_node->setPosition(position);
	this->update();
}

Ogre::Vector3 Sprite2DAttachable::position3D() const
{
	return this->_node->getPosition();
}

Ogre::SceneNode* Sprite2DAttachable::node()
{
	return this->_node;
}

const Ogre::SceneNode* Sprite2DAttachable::node() const
{
	return this->_node;
}

void Sprite2DAttachable::setPlanarRotation(float radians)
{
	/** @todo Implement this correctly */
}

float Sprite2DAttachable::planarRotation() const
{
	return 0.0f;
}

void Sprite2DAttachable::setAxisRotation(float radians)
{
	/* It's impossible to rotate 2D sprite around the axis.
	 * Thus do nothing here.
	 */
}

float Sprite2DAttachable::axisRotation() const
{
	/* It's impossible to rotate 2D sprite around the axis.
	 * Thus always return no rotation.
	 */
	return 0.0;
}

void Sprite2DAttachable::setVisible(bool value)
{
	/** @todo Implement this */
}

bool Sprite2DAttachable::isVisible() const
{
	return true;
}

void Sprite2DAttachable::update()
{
	this->_attachableBillboard->setPosition(this->_node->getPosition());
}

/* Sprite2D class */

Sprite2D::Sprite2D(std::string name, std::string matName, Size ssize):
	Renderable(name), _materialName(matName), _size(ssize)
{
	Ogre::SceneManager* lSceneMgr = sts::GameRoot::getObject()->_getOSceneManager();

	this->_billboardSet = lSceneMgr->createBillboardSet();
	this->_billboardSet->setMaterialName(this->_materialName);
	/** @todo Add setTextureStacksAndSlices if necessary */

	/* Create a node (engine requirement */
	Ogre::SceneNode* lRootNode = lSceneMgr->getRootSceneNode();
	this->_node = lRootNode->createChildSceneNode();
	this->_node->attachObject(this->_billboardSet);
}

Sprite2D::Sprite2D(const Sprite2D& sprite):
	Renderable(sprite.name()), _size(sprite._size)
{
	throw std::runtime_error("Sprite2D is not copyable");
}

Sprite2D::~Sprite2D()
{

}

Sprite2D* Sprite2D::create(std::string name, std::string matName, Size ssize)
{
	return new Sprite2D(name, matName, ssize);
}

IAttachable* Sprite2D::_spawnAttachable(Ogre::SceneNode* node) const
{
	Ogre::Billboard* billboard = this->_billboardSet->createBillboard(Ogre::Vector3(0, 0, 0));
	billboard->setDimensions(this->_size.width, this->_size.height);
	/** @todo Add animation support if necessary */
	billboard->setTexcoordIndex(0);

    Sprite2DAttachable* attachable = new Sprite2DAttachable(node, billboard);
    return attachable;
}

std::string Sprite2D::materialName() const
{
	return this->_materialName;
}

Sprite2D::Size Sprite2D::size() const
{
	return this->_size;
}

} // namespace sts
