#include "sts_scene_manager.hpp"

#include <stdexcept>

namespace sts {

SceneManager::SceneManager(Ogre::SceneManager* osceneManager):
	_oscene(osceneManager)
{
	/* Create zero layer */
	this->_layers.push_back(std::shared_ptr<Layer>(new Layer()));
}

SceneManager::SceneManager(const SceneManager& scmgr)
{

}

SceneManager::~SceneManager()
{

}

Layer* SceneManager::addLayer(unsigned int index)
{
	if (index == 0) {
		return nullptr;
	}

	std::shared_ptr<Layer> newLayer(new Layer());

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

bool SceneManager::moveLayerUp(unsigned int index)
{
	if (index < 1) {
		return false;
	}

	std::shared_ptr<Layer> layerToMove(this->_layers.at(index));
	this->_layers.at(index) = this->_layers.at(index - 1);
	this->_layers.at(index - 1) = layerToMove;

	return true;
}

bool SceneManager::moveLayerDown(unsigned int index)
{
	if ( (index == 0) || (index == this->_layers.size() - 1) ) {
		return false;
	}

	std::shared_ptr<Layer> layerToMove(this->_layers.at(index));
	this->_layers.at(index) = this->_layers.at(index + 1);
	this->_layers.at(index + 1) = layerToMove;

	return true;
}

void SceneManager::moveLayeredObject(LayeredObject* object, unsigned int layerIndex)
{
	Layer* layerMoveTo = this->_layers.at(layerIndex).get();
	if (object->layer()) {
		object->layer()->removeObject(object);
	}

	layerMoveTo->addObject(object);
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
	return &(this->_sharedObjects);
}

void SceneManager::removeSharedObject(SharedObject* object)
{
	this->_sharedObjects.removeObject(object);
	delete object;
}

void SceneManager::processScene()
{

}

} // namespace sts
