#pragma once

#include <iostream>

#include <OIS.h>
#include <OGRE/Ogre.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreFrameListener.h>

#include "scene/sts_shared_object.hpp"
#include "scene/sts_scene_object.hpp"
#include "MyFrameListener.hpp"

class MyFrameListener : public Ogre::FrameListener {
private:
  OIS::InputManager* mInputManager;
  OIS::Keyboard* mKeyboard;
  OIS::Mouse* mMouse;
  sts::SharedObject* mNode;
  Ogre::Camera *mCamera;
  float mMovementspeed;

public:
  MyFrameListener(sts::SharedObject*,Ogre::RenderWindow*);
  ~MyFrameListener();
  bool frameStarted (const Ogre::FrameEvent &evt);
  bool frameEnded (const Ogre::FrameEvent &evt);
  bool frameRenderingQueued (const Ogre::FrameEvent &evt);
};

