#include <exception>
#include <memory>

#include <vector>

#include "sound/SoundManager.hpp"
#include "ois/MyFrameListener.hpp"
#include "sts_game_root.hpp"
#include "rendering/sts_model3d.hpp"

#include "sts_resources.hpp"
#include "game_data.hpp"
#include "move.hpp"
#include "game_object.hpp"
#include "weapon.hpp"

#include <OGRE/OgreRoot.h>
#include <OGRE/OgreRenderSystem.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreWindowEventUtilities.h>
#include <OGRE/OgreBillboardSet.h>
#include <OGRE/OgreBillboard.h>

typedef std::vector<Ogre::String> Strings;

/** Stores proceeded command line args */
struct ExecutionArgs
{
	/** Defines if config dialog execution is needed */
	bool showConfigDialog;
	/** Define if help prompt is needed */
	bool helpPrompt;

	ExecutionArgs():
		showConfigDialog(false), helpPrompt(false) {}
};

/** Processes command line args */
bool processCommandLineArgs(int argc, char* argv[], ExecutionArgs& exArgs)
{
	exArgs = ExecutionArgs();
	/* No options */
	if (argc <= 1) {
		return true;
	}

	bool returnValue = true;
	for (int i = 1; i < argc; ++i) {
		std::string arg(argv[i]);
		if (arg == "--help") {
			/* Check for other options - they are not allowed */
			if (argc > 2) {
				std::cerr << "ERROR: No additional option with --help is allowed." << std::endl;
				returnValue = false;
				break;
			}
			exArgs.helpPrompt = true;
		} else if (arg == "--config")  {
			exArgs.showConfigDialog = true;
		} else {
			std::cerr << "ERROR: unknown option \"" << arg << "\"" << std::endl;
			returnValue = false;
			break;
		}
	}
	return returnValue;
}

/** Try to use first possible render system. Throw an exception if nothing is found. */
void initSomeRenderSystem(std::unique_ptr<Ogre::Root>& root)
{
	const Ogre::RenderSystemList& lRenderSystemList = root->getAvailableRenderers();
	if (lRenderSystemList.size() == 0) {
		Ogre::LogManager::getSingleton().logMessage("No render system was found.");
		throw Ogre::Exception(1, "Render system was not initialized.", "main.cpp");
	}
	Ogre::RenderSystem* lRenderSystem = lRenderSystemList[0];
	root->setRenderSystem(lRenderSystem);
}

void initResourceMainGroup(const Ogre::String& groupName)
{
	Ogre::ResourceGroupManager& lRcGroupMgr = Ogre::ResourceGroupManager::getSingleton();
	lRcGroupMgr.createResourceGroup(groupName);

	for( auto dataDir : sts::getDataDirs() ) {
		lRcGroupMgr.addResourceLocation(sts::getDataBasePath() + dataDir, "FileSystem", groupName, false);
	}
	lRcGroupMgr.initialiseResourceGroup(groupName);
	lRcGroupMgr.loadResourceGroup(groupName);
}

int main(int argc, char* argv[])
{
	std::unique_ptr<ExecutionArgs> exArgs(new ExecutionArgs());
	if (!processCommandLineArgs(argc, argv, *exArgs)) {
		return -1;
	} else if (exArgs->helpPrompt) {
		std::cout << "Usage: sts [--help] || [--config]" << std::endl;
		std::cout << "Options:" << std::endl;
		std::cout << "\t --help - print this message;" << std::endl;
		std::cout << "\t --config - show config dialog." << std::endl;
		std::cout << std::endl;
		return 0;
	}


	try {
		Ogre::String lConfigFileName = "ogre.cfg";
		Ogre::String lPluginsFileName = "plugins.cfg";
		Ogre::String lLogFileName = "Ogre_STS.log";

		std::unique_ptr<Ogre::Root> lRoot(new Ogre::Root(lPluginsFileName, lConfigFileName, lLogFileName));

		if (exArgs->showConfigDialog) {
			if (!lRoot->showConfigDialog()) {
				return 0;
			}
		}

		Ogre::String lWindowTitle = "STS";
		Ogre::String lCustomCapacities = "";

		/* Check for the valid ogre.cfg */
		bool lCreateAWindowAutomatically = lRoot->restoreConfig();
		if (!lCreateAWindowAutomatically) {
			initSomeRenderSystem(lRoot);
		}
		Ogre::RenderWindow* lWindow = lRoot->initialise(lCreateAWindowAutomatically, lWindowTitle, lCustomCapacities);

		if (!lWindow) {
			/* ogre.cfg is not available - start with hardcoded parameters */
			unsigned int lSizeX = 800;
			unsigned int lSizeY = 600;
			bool lFullscreen = false;

			Ogre::NameValuePairList lParams;
			lParams["FSAA"] = "0";
			lParams["vsync"] = "true";
			lWindow = lRoot->createRenderWindow(lWindowTitle, lSizeX, lSizeY, lFullscreen, &lParams);
		}

		/* Resource manager */
		Ogre::String lRcGroupName = "Main group";
		initResourceMainGroup(lRcGroupName);

		/* Create a scene manager */
		Ogre::SceneManager* lScene = lRoot->createSceneManager(Ogre::ST_GENERIC, "SceneManager");

		/* Declare necessary viewport pointer */
		Ogre::Viewport* vp = nullptr;

		{
			/* We need to create temporary camera due to OGRE requirements */

			/* Create temporary camera */
			Ogre::Camera* lCamera = lScene->createCamera("TempCamera");
			/* Create viewport (camera <-> window) */
			vp = lWindow->addViewport(lCamera);
			/* Init game root object. It will replace temporary camera with its own one */
			sts::GameRoot::initRoot(lScene, vp);
			/* Destroy temporary camera */
			lScene->destroyCamera(lCamera);
		}

		sts::SharedObject* lShipObject = nullptr;
		{
			sts::Model3D* lShipModel = sts::Model3D::create("airship.mesh", "airship.mesh", 3.15f);
			lShipObject = sts::SharedObject::create(lShipModel);
			lShipObject->setPosition(sts::SceneObject::Position(0, -100));
		}

		Ogre::SceneNode* lRootSceneNode = lScene->getRootSceneNode();

		/* Sprite billboard (manually) */
		Ogre::SceneNode* lSpriteNode = lRootSceneNode->createChildSceneNode();
		Ogre::BillboardSet* lBillboardSet = lScene->createBillboardSet();
		lBillboardSet->setMaterialName("enemy_01", lRcGroupName);
		lBillboardSet->setTextureStacksAndSlices(1, 4);
		Ogre::Billboard* lSpriteBillboard = lBillboardSet->createBillboard(Ogre::Vector3(0, 0, 0));
		lSpriteBillboard->setDimensions(48.0f / 2.0f, 58.0f / 2.0f);
		lSpriteBillboard->setTexcoordIndex(1);
		lSpriteNode->attachObject(lBillboardSet);
		lSpriteNode->setPosition(Ogre::Vector3(0, -200, 100));

		/* Obtain the timer pointer */
		Ogre::Timer* lTimer = lRoot->getTimer();

		/* Skip all the messages */
		lWindow->setAutoUpdated(false);
		lRoot->clearEventTimes();

		/* Create sound manager */
		SoundManager* mSoundMgr = new SoundManager();
		mSoundMgr->playMusic(sts::getDataBasePath() + std::string("sounds/Credits_heart-of-the-sea.ogg"));
		mSoundMgr->playSound(sts::getDataBasePath() + std::string("sounds/bell.ogg"));
		
		// Create an instance of the MyFrameListener Class and add it to the root object
		MyFrameListener* myListener = new MyFrameListener(lShipObject, lWindow);
		lRoot->addFrameListener(myListener);

		while (!lWindow->isClosed()) {
			float angle = Ogre::Math::Sin(float(lTimer->getMilliseconds()) * Ogre::Math::PI / 2000.0f) * Ogre::Math::PI / 4.0f;
			float displacement = Ogre::Math::Cos(float(lTimer->getMilliseconds()) * Ogre::Math::PI / 2000.0f) * 100.0f;

			lShipObject->setPlanarRotation(angle);
			lShipObject->setAxisRotation(angle);
//			lShipObject->setPosition(sts::SceneObject::Position(static_cast<int>(displacement), 0));

			unsigned int spriteFrame = (lTimer->getMilliseconds() / 125) % 2;
			lSpriteBillboard->setTexcoordIndex(spriteFrame);

			lWindow->update(false);
			lWindow->swapBuffers();
			lRoot->renderOneFrame();

			Ogre::WindowEventUtilities::messagePump();
		}
		Ogre::LogManager::getSingleton().logMessage("Render window closed.");

		sts::GameRoot::releaseRoot();

		sts::GameData::load();
		sts::GameObject go(1, 1, 1.0);
		sts::Level l("level1.json");
	}
	catch (Ogre::Exception &e) {
		std::cerr << "Ogre::Exception: " << e.what() << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "std::exception: " << e.what() << std::endl;
	}

	return 0;
}
