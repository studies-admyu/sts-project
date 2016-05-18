#include "MyFrameListener.hpp"


//
MyFrameListener::MyFrameListener(sts::SharedObject *node, Ogre::RenderWindow *mWindow)
{
  //
  mNode = node;
//  mCamera = camera;
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
  //std::cout << "Frame Started" << std::endl;
  
  //
  //Ogre::Vector3 translate(0,0,0);
  sts::SceneObject::Position current_pos = mNode->position();
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
    translate = sts::SceneObject::Position(translate.x, translate.y + 1);
  }

  //
  if(mKeyboard->isKeyDown(OIS::KC_S))
  {	
    translate = sts::SceneObject::Position(translate.x, translate.y - 1);
  }
  
  //
  if(mKeyboard->isKeyDown(OIS::KC_A))
  {
    translate = sts::SceneObject::Position(translate.x + 1, translate.y);
  }
  
  //
  if(mKeyboard->isKeyDown(OIS::KC_D))
  {
    translate = sts::SceneObject::Position(translate.x - 1, translate.y);
  }

  if(mKeyboard->isKeyDown(OIS::KC_RETURN))
  {	
    // fire code
  }

  
  //
  float rotX = mMouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1;
  float rotY = mMouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
//  mCamera->yaw(Ogre::Radian(rotX));
//  mCamera->pitch(Ogre::Radian(rotY));
  
  //
//  mCamera->moveRelative(translate * evt.timeSinceLastFrame * mMovementspeed);
//  mNode->setPosition(mNode->getPosition() + translate);
    mNode->setPosition(translate);

  return true;
}

//
bool MyFrameListener::frameEnded(const Ogre::FrameEvent &evt) {
  //std::cout << "Frame Ended" << std::endl;
  return true;
}

//
bool MyFrameListener::frameRenderingQueued(const Ogre::FrameEvent &evt) {
  //std::cout << "Frame Queued" << std::endl;
  return true;
}

