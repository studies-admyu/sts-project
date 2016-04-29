#include "sts_scene_manager.hpp"

namespace sts {

SceneManager::SceneManager(Ogre::SceneManager* osceneManager)
{
	
}

SceneManager::SceneManager(const SceneManager& scmgr)
{
	
}

SceneManager::~SceneManager()
{
	
}

Layer* SceneManager::addLayer(unsigned int index)
{
	return nullptr;
}

Layer* SceneManager::layer(unsigned int index)
{
	return nullptr;
}

std::vector<Layer*> SceneManager::layers()
{
	return std::vector<Layer*>();
}

void SceneManager::removeLayer(unsigned int index)
{
	
}

bool SceneManager::moveLayerUp(unsigned int index)
{
	return false;
}

bool SceneManager::moveLayerDown(unsigned int index)
{
	return false;
}

void SceneManager::moveLayeredObject(LayeredObject* object, unsigned int layerIndex)
{
	
}

void SceneManager::removeLayeredObject(LayeredObject* object)
{
	
}

SharedObjectGroup* SceneManager::sharedObjects()
{
	return nullptr;
}

void SceneManager::removeSharedObject(SharedObject* object)
{
	
}

void SceneManager::processScene()
{
	
}

} // namespace sts
