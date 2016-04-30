#pragma once

#include <OGRE/OgreRoot.h>

#include "game_object.hpp"
#include "move.hpp"
#include "entity.hpp"
#include "game_data.hpp"

namespace sts {

class Weapon;

class Bullet : public GameObject {
public:
	Bullet(int x, int y, double direction, Weapon *w) : GameObject(x, y, direction), weapon(w) {}
private:
	Weapon *weapon;
};

class IBulletStyle {
public:
	IBulletStyle(const Entity *e) : entityPtr(e) {}
	// Every bullet style must decide how to handle collisions.
	virtual void collisionAlgorithm(GameObject &o) const = 0;
	// Hardcoded, so no arguments now. Should be changed in the future.
	virtual IMoveBehaviour* createMoveBehaviour() const = 0;
	// Creates a bullet GameObject, passing itself to it.
	// Currently children are hardcoded and not configurable externally. We should change it in the future.
	static Bullet createNewBullet(double direction);

	const Entity *entityPtr;
};

class RoundBullet : public IBulletStyle {
public:
	// Currently hardcoded, later from json
	RoundBullet() : IBulletStyle(GameData::entities["round_bullet"]) { Ogre::LogManager::getSingleton().logMessage("RoundBullet style created");}
	virtual void collisionAlgorithm(GameObject &o) const override { /* handle collision here */ }
	// Currently hardcoded, later from json
	virtual IMoveBehaviour* createMoveBehaviour() const override { return IMoveBehaviour::createMoveBehaviour("MoveForward"); }
};

class BlastBullet : public IBulletStyle {
public:
	// Currently hardcoded, later from json
	BlastBullet() : IBulletStyle(GameData::entities["blast_bullet"]) { Ogre::LogManager::getSingleton().logMessage("BlastBullet style created");}
	virtual void collisionAlgorithm(GameObject &o) const override { /* handle collision here */ }
	// Currently hardcoded, later from json
	virtual IMoveBehaviour* createMoveBehaviour() const override { return IMoveBehaviour::createMoveBehaviour("MoveForward"); }
};


}



