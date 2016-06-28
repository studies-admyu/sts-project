#include "MyFrameListener.hpp"

#include <sts_game_root.hpp>

//
MyFrameListener::MyFrameListener(sts::SceneObject* object, Ogre::RenderWindow* mWindow)
{
	//
	mObject = object;
	mMovementspeed = 5.0f;

	//
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");

	//
	size_t windowHnd = 0;
	mWindow->getCustomAttribute("WINDOW", &windowHnd);

	//
	std::stringstream windowHndStr;
	windowHndStr << windowHnd;

	//
	OIS::ParamList pl;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	mInputManager = OIS::InputManager::createInputSystem(pl);

	//
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true ));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
}

//
MyFrameListener::~MyFrameListener()
{
	//
	mInputManager->destroyInputObject(mKeyboard);
	mInputManager->destroyInputObject(mMouse);
	OIS::InputManager::destroyInputSystem(mInputManager);
}


//
bool MyFrameListener::frameStarted(const Ogre::FrameEvent &evt) {
	sts::SceneObject::Position current_pos = mObject->position();
	sts::SceneObject::Position translate(current_pos.x, current_pos.y);

	//
	mKeyboard->capture();
	mMouse->capture();

	//
	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		return false;
	}

	//
	if(mKeyboard->isKeyDown(OIS::KC_W))
	{
		int sceneHeight = sts::GameRoot::getObject()->sceneManager()->sceneHeight();
		if (translate.y < sceneHeight) {
			translate = sts::SceneObject::Position(translate.x, translate.y + 1);
		}
	}

	//
	if(mKeyboard->isKeyDown(OIS::KC_S))
	{
		if (translate.y > 0) {
			translate = sts::SceneObject::Position(translate.x, translate.y - 1);
		}
	}

	//
	if(mKeyboard->isKeyDown(OIS::KC_A))
	{
		if (translate.x > 0) {
			translate = sts::SceneObject::Position(translate.x - 1, translate.y);
		}
	}

	//
	if(mKeyboard->isKeyDown(OIS::KC_D))
	{
		int sceneWidth = sts::GameRoot::getObject()->sceneManager()->sceneWidth();
		if (translate.x < sceneWidth) {
			translate = sts::SceneObject::Position(translate.x + 1, translate.y);
		}
	}

	if(mKeyboard->isKeyDown(OIS::KC_RETURN))
	{
		// fire code
	}

	mObject->setPosition(translate);

	return true;
}

//
bool MyFrameListener::frameEnded(const Ogre::FrameEvent &evt) {
	return true;
}

//
bool MyFrameListener::frameRenderingQueued(const Ogre::FrameEvent &evt) {
	return true;
}

