#pragma once

#include <memory>
#include <vector>

#include <OGRE/OgreSceneManager.h>

#include "sts_layer.hpp"
#include "sts_shared_object_group.hpp"

namespace sts {

class SceneManager
{
public:
	SceneManager(Ogre::SceneManager* osceneManager, Ogre::Viewport* oviewport, Ogre::Timer* otimer);
	~SceneManager();

	Ogre::SceneManager* _getOSceneManager();
	const Ogre::SceneManager* _getOSceneManager() const;

	Ogre::Timer* _getOTimer();
	const Ogre::Timer* _getOTimer() const;

	Ogre::Viewport* _getOViewport();
	const Ogre::Viewport* _getOViewport() const;

	Ogre::SceneNode* _spawnObjectNode();
	Ogre::SceneNode* _spawnRenderableNode();
	void _destroyNode(Ogre::SceneNode* node);

	void _clearScene();

	Layer* addLayer(unsigned int index);
	Layer* layer(unsigned int index);
	const Layer* layer(unsigned int index) const;
	float layerZ(unsigned int index) const;
	std::vector<Layer*> layers();
	void removeLayer(unsigned int index);

	void moveLayeredObject(LayeredObject* object, unsigned int layerIndex);
	void removeLayeredObject(LayeredObject* object);

	SharedObjectGroup* sharedObjects();
	void removeSharedObject(SharedObject* object);

	unsigned int sceneWidth() const;
	unsigned int sceneHeight() const;

	void processScene();

private:
	Ogre::SceneManager* _oscene;
	Ogre::Timer* _otimer;
	Ogre::Viewport* _oviewport;
	Ogre::Camera* _ocamera;

	std::vector<std::shared_ptr<Layer>> _layers;
	std::unique_ptr<SharedObjectGroup> _sharedObjects;

	SceneManager(const SceneManager&);
	void initScene();
};

} // namespace sts
