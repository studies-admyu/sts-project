#include "sts_game_root.hpp"

#include <stdexcept>

namespace sts {

GameRoot* mGameRootSingleton = nullptr;

GameRoot::GameRoot(Ogre::SceneManager* oscene, Ogre::Viewport* oviewport)
{
	this->_scene = new SceneManager(oscene, oviewport);
}

GameRoot::GameRoot(const GameRoot&)
{
	throw std::runtime_error("GameRoot is a singleton and can't be copied.");
}

GameRoot::~GameRoot()
{
	releaseResources();

	delete this->_scene;
	this->_scene = nullptr;
}

void GameRoot::releaseScene()
{
	this->_scene->_clearScene();
	this->_renderables.clear();
}

void GameRoot::releaseResources()
{
	this->releaseScene();
}

GameRoot* GameRoot::initRoot(Ogre::SceneManager* oscene, Ogre::Viewport* oviewport)
{
	if (mGameRootSingleton) {
		throw std::runtime_error("Attempt to init GameRoot singleton once again.");
	}
	mGameRootSingleton = new GameRoot(oscene, oviewport);
	return mGameRootSingleton;
}

GameRoot* GameRoot::getObject()
{
	if (!mGameRootSingleton) {
		throw std::runtime_error("Root object hasn't been initialized or has been released yet.");
	}
	return mGameRootSingleton;
}

void GameRoot::releaseRoot()
{
	mGameRootSingleton->releaseResources();
	delete mGameRootSingleton;
	mGameRootSingleton = nullptr;
}

Ogre::SceneManager* GameRoot::_getOSceneManager()
{
	return this->sceneManager()->_getOSceneManager();
}

const Ogre::SceneManager* GameRoot::_getOSceneManager() const
{
	return this->sceneManager()->_getOSceneManager();
}

Ogre::Viewport* GameRoot::_getOViewport()
{
	return this->sceneManager()->_getOViewport();
}

const Ogre::Viewport* GameRoot::_getOViewport() const
{
	return this->sceneManager()->_getOViewport();
}

void GameRoot::_addRenderable(Renderable* renderable)
{
	if (this->_renderables.find(renderable->name()) != this->_renderables.end()) {
		throw std::runtime_error("Renderable with such a name exists.");
	}
	this->_renderables[renderable->name()] = std::unique_ptr<Renderable>(renderable);
}

bool GameRoot::isPaused() const
{
	/** @todo Implement this method */
	return false;
}

void GameRoot::setPaused(bool value)
{
	/** @todo Implement this method */
}

SceneManager* GameRoot::sceneManager()
{
	return this->_scene;
}

const SceneManager* GameRoot::sceneManager() const
{
	return this->_scene;
}

bool GameRoot::hasRenderable(std::string name) const
{
	return (this->_renderables.find(name) != this->_renderables.cend());
}

Renderable* GameRoot::getRenderable(std::string name)
{
	return this->_renderables.at(name).get();
}

const Renderable* GameRoot::getRenderable(std::string name) const
{
	return this->_renderables.at(name).get();
}

}
