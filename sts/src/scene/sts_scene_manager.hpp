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
	SceneManager(Ogre::SceneManager* osceneManager, Ogre::Viewport* osceneViewport);
	~SceneManager();

	Layer* addLayer(unsigned int index);
	Layer* layer(unsigned int index);
	std::vector<Layer*> layers();
	void removeLayer(unsigned int index);

	bool moveLayerUp(unsigned int index);
	bool moveLayerDown(unsigned int index);

	void moveLayeredObject(LayeredObject* object, unsigned int layerIndex);
	void removeLayeredObject(LayeredObject* object);

	SharedObjectGroup* sharedObjects();
	void removeSharedObject(SharedObject* object);

	void processScene();

private:
	Ogre::SceneManager* _oscene;
	Ogre::Viewport* _oviewport;
	Ogre::Camera* _ocamera;

	std::vector<std::shared_ptr<Layer>> _layers;
	SharedObjectGroup _sharedObjects;

	SceneManager(const SceneManager&);
	void initScene();
};

} // namespace sts
