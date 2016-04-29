#pragma once

#include <OGRE/OgreRoot.h>

#include "game_object.hpp"
#include "move.hpp"
#include "entity.hpp"
#include "game_data.hpp"

namespace sts {

class Bullet {

};

class IBulletStyle {
public:
	IBulletStyle(const Entity *e) : entityPtr(e) {}
	// Every bullet style must decide how to handle collisions.
	virtual void collisionAlgorithm(GameObject &o) = 0;
	// Hardcoded, so no arguments now. Should be changed in the future.
	virtual IMoveBehaviour* createMoveBehaviour() = 0;
	// Creates a bullet GameObject, passing itself to it.
	// Currently children are hardcoded and not configurable externally. We should change it in the future.
	static Bullet createNewBullet(double direction);

	const Entity *entityPtr;
};

class RoundBullet : public IBulletStyle {
public:
	// Currently hardcoded, later from json
	RoundBullet() : IBulletStyle(GameData::entities["round_bullet"]) { Ogre::LogManager::getSingleton().logMessage("RoundBullet style created");}
	virtual void collisionAlgorithm(GameObject &o) override { /* handle collision here */ }
	// Currently hardcoded, later from json
	virtual IMoveBehaviour* createMoveBehaviour() override { return IMoveBehaviour::createMoveBehaviour("MoveForward"); }
};

class BlastBullet : public IBulletStyle {
public:
	// Currently hardcoded, later from json
	BlastBullet() : IBulletStyle(GameData::entities["blast_bullet"]) { Ogre::LogManager::getSingleton().logMessage("BlastBullet style created");}
	virtual void collisionAlgorithm(GameObject &o) override { /* handle collision here */ }
	// Currently hardcoded, later from json
	virtual IMoveBehaviour* createMoveBehaviour() override { return IMoveBehaviour::createMoveBehaviour("MoveForward"); }
};


}



