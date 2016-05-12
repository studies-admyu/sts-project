#include "sts_game_root.hpp"

#include <stdexcept>

namespace sts {

GameRoot* mGameRootSingleton = nullptr;

GameRoot::GameRoot(Ogre::SceneManager* oscene, Ogre::Viewport* oviewport):
	_oscene(oscene), _oviewport(oviewport)
{

}

GameRoot::GameRoot(const GameRoot&)
{
	throw std::runtime_error("GameRoot is a singleton and can't be copied.");
}

GameRoot::~GameRoot()
{

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
	return mGameRootSingleton;
}

void GameRoot::releaseRoot()
{
	delete mGameRootSingleton;
	mGameRootSingleton = nullptr;
}

Ogre::SceneManager* GameRoot::_getOSceneManager()
{
	return this->_oscene;
}

const Ogre::SceneManager* GameRoot::_getOSceneManager() const
{
	return this->_oscene;
}

Ogre::Viewport* GameRoot::_getViewport()
{
	return this->_oviewport;
}

const Ogre::Viewport* GameRoot::_getViewport() const
{
	return this->_oviewport;
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

IRenderable* GameRoot::getRenderable(std::string name)
{
	return this->_renderables.at(name);
}

const IRenderable* GameRoot::getRenderable(std::string name) const
{
	return this->_renderables.at(name);
}

}
