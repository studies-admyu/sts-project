#pragma once

#include <map>
#include <memory>
#include <string>

#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreViewport.h>

#include "gameplay/sts_unit_type.hpp"
#include "scene/sts_scene_manager.hpp"

namespace sts {

class GameRoot
{
public:
	static GameRoot* initRoot(Ogre::SceneManager* oscene, Ogre::Viewport* oviewport, Ogre::Timer* otimer);
	static GameRoot* getObject();
	static void releaseRoot();

	Ogre::SceneManager* _getOSceneManager();
	const Ogre::SceneManager* _getOSceneManager() const;

	Ogre::Viewport* _getOViewport();
	const Ogre::Viewport* _getOViewport() const;

	void _addRenderable(Renderable* renderable);
	void _addUnitType(UnitType* unitType);

	bool isPaused() const;
	void setPaused(bool value);

	SceneManager* sceneManager();
	const SceneManager* sceneManager() const;

	bool hasRenderable(std::string name) const;
	Renderable* getRenderable(std::string name);
	const Renderable* getRenderable(std::string name) const;

	bool hasUnitType(std::string name) const;
	UnitType* getUnitType(std::string name);
	const UnitType* getUnitType(std::string name) const;

	void processGame();

private:
	GameRoot(Ogre::SceneManager* oscene, Ogre::Viewport* oviewport, Ogre::Timer* otimer);
	GameRoot(const GameRoot&);
	~GameRoot();

	void releaseScene();
	void releaseResources();

	SceneManager* _scene;
	std::map<std::string, std::unique_ptr<Renderable>> _renderables;
	std::map<std::string, std::unique_ptr<UnitType>> _unitTypes;
};

} // namespace sts
