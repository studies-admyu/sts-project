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
	void move();
private:
	Weapon *weapon;
};

/*
 * Specifies how a bullet looks like, how it moves and how it handles collisions.
 * All BulletStyles are singltones with hardcoded behaviours.
 * Creates bullets of this style on demand.
 * */
class IBulletStyle {
public:
	IBulletStyle(const Entity *e) : entityPtr(e) {}
	// Every bullet style must decide how to handle collisions.
	virtual void collisionAlgorithm(GameObject &o) const = 0;
	// Every bullet style must decide how to move the bullet
	virtual void move(Bullet *bullet) const = 0;
protected:
	const Entity *entityPtr;
};

class RoundBullet : public IBulletStyle {
public:
	static RoundBullet* getInstance();
	virtual void collisionAlgorithm(GameObject &o) const { /* handle collision here */ }
	virtual void move(Bullet *bullet) const { return Ogre::LogManager::getSingleton().logMessage("Moving RoundBullet"); }
private:
	RoundBullet() : IBulletStyle(GameData::entities["RoundBullet"]) { Ogre::LogManager::getSingleton().logMessage("RoundBullet style created");}
	RoundBullet(RoundBullet const&): IBulletStyle(GameData::entities["RoundBullet"]) { };
	RoundBullet& operator=(RoundBullet const&) { return *this; };
	static RoundBullet *instance;

};

class BlastBullet : public IBulletStyle {
public:
	static BlastBullet* getInstance();
	virtual void collisionAlgorithm(GameObject &o) const { /* handle collision here */ }
	virtual void move(Bullet *bullet) const { return Ogre::LogManager::getSingleton().logMessage("Moving BlastBullet"); }
private:
	BlastBullet() : IBulletStyle(GameData::entities["BlastBullet"]) { Ogre::LogManager::getSingleton().logMessage("BlastBullet style created");}
	BlastBullet(BlastBullet const&): IBulletStyle(GameData::entities["BlastBullet"]) { }
	BlastBullet& operator=(BlastBullet const&) { return *this; }
	static BlastBullet *instance;
};


}



