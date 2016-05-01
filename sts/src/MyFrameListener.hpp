#pragma once

#include <iostream>

#include <OIS.h>
#include <OGRE/Ogre.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreFrameListener.h>

#include "MyFrameListener.hpp"

class MyFrameListener : public Ogre::FrameListener {
private:
  OIS::InputManager* mInputManager;
  OIS::Keyboard* mKeyboard;
  OIS::Mouse* mMouse;
  Ogre::SceneNode* mNode;
  Ogre::Camera *mCamera;
  float mMovementspeed;

public:
  MyFrameListener(Ogre::SceneNode*,Ogre::RenderWindow*, Ogre::Camera*);
  ~MyFrameListener();
  bool frameStarted (const Ogre::FrameEvent &evt);
  bool frameEnded (const Ogre::FrameEvent &evt);
  bool frameRenderingQueued (const Ogre::FrameEvent &evt);
};

