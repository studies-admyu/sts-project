#pragma once

#include <OGRE/OgreRoot.h>

#include "game_object.hpp"
#include "move.hpp"
#include "game_data.hpp"

#include "rendering/sts_renderable.hpp"

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
	IBulletStyle(const Renderable *r) : renderablePtr(r) {}
	// Every bullet style must decide how to handle collisions.
	virtual void collisionAlgorithm(GameObject &o) const = 0;
	// Every bullet style must decide how to move the bullet
	virtual void move(Bullet *bullet) const = 0;
protected:
	const Renderable* renderablePtr;
};

class RoundBullet : public IBulletStyle {
public:
	static RoundBullet* getInstance();
	virtual void collisionAlgorithm(GameObject &o) const { /* handle collision here */ }
	virtual void move(Bullet *bullet) const { return Ogre::LogManager::getSingleton().logMessage("Moving RoundBullet"); }
private:
	RoundBullet() : IBulletStyle(GameData::renderables["RoundBullet"]) { Ogre::LogManager::getSingleton().logMessage("RoundBullet style created");}
	RoundBullet(RoundBullet const&): IBulletStyle(GameData::renderables["RoundBullet"]) { };
	RoundBullet& operator=(RoundBullet const&) { return *this; };
	static RoundBullet *instance;

};

class BlastBullet : public IBulletStyle {
public:
	static BlastBullet* getInstance();
	virtual void collisionAlgorithm(GameObject &o) const { /* handle collision here */ }
	virtual void move(Bullet *bullet) const { return Ogre::LogManager::getSingleton().logMessage("Moving BlastBullet"); }
private:
	BlastBullet() : IBulletStyle(GameData::renderables["BlastBullet"]) { Ogre::LogManager::getSingleton().logMessage("BlastBullet style created");}
	BlastBullet(BlastBullet const&): IBulletStyle(GameData::renderables["BlastBullet"]) { }
	BlastBullet& operator=(BlastBullet const&) { return *this; }
	static BlastBullet *instance;
};


}



