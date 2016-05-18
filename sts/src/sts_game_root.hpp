#pragma once

#include <map>
#include <memory>
#include <string>

#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreViewport.h>

#include "rendering/sts_renderable.hpp"
#include "scene/sts_scene_manager.hpp"

namespace sts {

class GameRoot
{
public:
	static GameRoot* initRoot(Ogre::SceneManager* oscene, Ogre::Viewport* oviewport);
	static GameRoot* getObject();
	static void releaseRoot();

	Ogre::SceneManager* _getOSceneManager();
	const Ogre::SceneManager* _getOSceneManager() const;

	Ogre::Viewport* _getOViewport();
	const Ogre::Viewport* _getOViewport() const;

	void _addRenderable(Renderable* renderable);

	bool isPaused() const;
	void setPaused(bool value);

	SceneManager* sceneManager();
	const SceneManager* sceneManager() const;

	bool hasRenderable(std::string name) const;
	Renderable* getRenderable(std::string name);
	const Renderable* getRenderable(std::string name) const;

private:
	GameRoot(Ogre::SceneManager* oscene, Ogre::Viewport* oviewport);
	GameRoot(const GameRoot&);
	~GameRoot();

	void releaseScene();
	void releaseResources();

	SceneManager* _scene;
	std::map<std::string, std::unique_ptr<Renderable>> _renderables;
};

} // namespace sts