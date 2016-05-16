#include "sts_scene_manager.hpp"

#include <stdexcept>

namespace sts {

SceneManager::SceneManager(Ogre::SceneManager* osceneManager, Ogre::Viewport* oviewport):
	_oscene(osceneManager), _oviewport(oviewport)
{
	this->initScene();
	this->_clearScene();
}

SceneManager::SceneManager(const SceneManager& scmgr)
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::initScene()
{
	/* Set viewport options */
	this->_oviewport->setAutoUpdated(true);
	this->_oviewport->setBackgroundColour(Ogre::ColourValue(1, 0, 1));

	/* Create camera */
	this->_ocamera = this->_oscene->createCamera("SceneCamera");

	/* Attach it to the viewport */
	this->_oviewport->setCamera(this->_ocamera);

	/* Set camera options */
	/* Orthographic projectsion */
	this->_ocamera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	/* Window & scene coordinates must correspond */
	this->_ocamera->setAspectRatio(
		float(this->_oviewport->getActualWidth()) / this->_oviewport->getActualHeight()
	);
	this->_ocamera->setOrthoWindowWidth(this->_oviewport->getActualWidth());

	this->_ocamera->setNearClipDistance(1.5f);
	this->_ocamera->setFarClipDistance(3000.0f);

	Ogre::Vector3 screenCenter(
		this->_oviewport->getActualWidth() / 2,
		0,
		this->_oviewport->getActualHeight() / 2
	);

	this->_ocamera->setPosition(screenCenter + Ogre::Vector3(0, 100, -1));
	this->_ocamera->lookAt(screenCenter);

	/* Create light */
	Ogre::Light* sceneLight = this->_oscene->createLight("SceneLight");
	sceneLight->setPosition(this->_ocamera->getPosition());
}

Ogre::SceneManager* SceneManager::_getOSceneManager()
{
	return this->_oscene;
}

const Ogre::SceneManager* SceneManager::_getOSceneManager() const
{
	return this->_oscene;
}

Ogre::Viewport* SceneManager::_getOViewport()
{
	return this->_oviewport;
}

const Ogre::Viewport* SceneManager::_getOViewport() const
{
	return this->_oviewport;
}

Ogre::SceneNode* SceneManager::_spawnObjectNode()
{
	return this->_oscene->getRootSceneNode()->createChildSceneNode();
}

Ogre::SceneNode* SceneManager::_spawnRenderableNode()
{
	/* No difference for now */
	return this->_spawnObjectNode();
}

void SceneManager::_destroyNode(Ogre::SceneNode*)
{
	/* Do nothing for now - wait for the whole scene cleanup */
}

void SceneManager::_clearScene()
{
	this->_layers.clear();
	this->_sharedObjects.reset(new SharedObjectGroup);

	/* Scene cleanup */
	this->_oscene->clearScene();

	/* Create zero layer */
	this->_layers.push_back(std::shared_ptr<Layer>(new Layer(this, 0)));
}

Layer* SceneManager::addLayer(unsigned int index)
{
	if (index == 0) {
		return nullptr;
	}

	std::shared_ptr<Layer> newLayer(new Layer(this, this->_layers.size()));

	if (index > this->_layers.size()) {
		this->_layers.push_back(newLayer);
	} else {
		this->_layers.insert(this->_layers.begin() + index, newLayer);
	}
	return newLayer.get();
}

Layer* SceneManager::layer(unsigned int index)
{
	return this->_layers.at(index).get();
}

const Layer* SceneManager::layer(unsigned int index) const
{
	return this->_layers.at(index).get();
}

float SceneManager::layerZ(unsigned int index) const
{
	/* Check the layer */
	this->layer(index);

	if (this->_layers.size() > 1) {
		return index * 1000.0 / (this->_layers.size() - 1);
	} else {
		return 0.0;
	}
}

std::vector<Layer*> SceneManager::layers()
{
	std::vector<Layer*> returnVector;
	returnVector.reserve(this->_layers.size());

	for (auto layer = this->_layers.begin(); layer != this->_layers.end(); ++layer) {
		returnVector.push_back(layer->get());
	}

	return returnVector;
}

void SceneManager::removeLayer(unsigned int index)
{
	if (index == 0) {
		throw std::runtime_error("Impossible operation: Attempt to remove zero layer.");
		return;
	}

	/* Move all the objects to the zero layer */
	std::shared_ptr<Layer> layerToRemove(this->_layers.at(index));
	/** @todo Make it thread safe is necessary. */
	auto objects = layerToRemove->objects();
	for (auto obj = objects.begin(); obj != objects.end(); ++obj) {
		this->moveLayeredObject(*obj, 0);
	}

	this->_layers.erase(this->_layers.begin() + index);
}

void SceneManager::moveLayeredObject(LayeredObject* object, unsigned int layerIndex)
{
	Layer* layerMoveTo = this->_layers.at(layerIndex).get();
	if (object->layer()) {
		object->layer()->removeObject(object);
	}

	layerMoveTo->addObject(object);
	object->_setLayer(layerMoveTo);
}

void SceneManager::removeLayeredObject(LayeredObject* object)
{
	if (object->layer()) {
		object->layer()->removeObject(object);
	}
	delete object;
}

SharedObjectGroup* SceneManager::sharedObjects()
{
	return this->_sharedObjects.get();
}

void SceneManager::removeSharedObject(SharedObject* object)
{
	this->_sharedObjects->removeObject(object);
	delete object;
}

unsigned int SceneManager::sceneWidth() const
{
	return this->_oviewport->getActualWidth();
}

unsigned int SceneManager::sceneHeight() const
{
	return this->_oviewport->getActualHeight();
}

void SceneManager::processScene()
{

}

} // namespace sts
