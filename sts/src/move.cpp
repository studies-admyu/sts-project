#include <exception>

#include <OGRE/OgreRoot.h>

#include "move.hpp"

namespace sts {

IMoveBehaviour* IMoveBehaviour::createMoveBehaviour(std::string mb_name) {
	if (mb_name == "MoveForward")
		return new MoveForward();
	else if (mb_name == "MoveIdle")
		return new MoveIdle();
	else if (mb_name == "MoveStay")
		return new MoveStay();
	else
		throw MoveBehaviourException("Bad move behaviour name");
}

void MoveForward::move(GameObject &o) {
	Ogre::LogManager::getSingleton().logMessage("Moving forward");
}

void MoveIdle::move(GameObject &o) {
	Ogre::LogManager::getSingleton().logMessage("Idle moving");
}

void MoveStay::move(GameObject &o) {
	Ogre::LogManager::getSingleton().logMessage("Staying quietly");
}

}