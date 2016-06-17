#include "sts_motion_behavior.hpp"

#include <OGRE/OgreRoot.h>

namespace sts {

IMotionBehavior* IMotionBehavior::createMotionBehavior(std::string mb_name)
{
	if (mb_name == "MoveForward") {
		return new MoveForward();
	} else if (mb_name == "MoveIdle") {
		return new MoveIdle();
	} else if (mb_name == "MoveStay") {
		return new MoveStay();
	} else {
		throw MoveBehaviorException("Bad move behavior name");
	}
}

void MoveForward::move(SceneObject& o)
{
	Ogre::LogManager::getSingleton().logMessage("Moving forward");
}

void MoveIdle::move(SceneObject& o)
{
	Ogre::LogManager::getSingleton().logMessage("Idle moving");
}

void MoveStay::move(SceneObject& o)
{
	Ogre::LogManager::getSingleton().logMessage("Staying quietly");
}

} // namespace sts