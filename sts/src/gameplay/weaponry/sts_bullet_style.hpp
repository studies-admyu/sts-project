#pragma once

#include <scene/sts_scene_object.hpp>

namespace sts {

class Bullet;

/**
  * Specifies how to create bullet.
  * All the BulletStyles are singltones with hardcoded behaviours.
  * Creates bullets of this style on demand.
  */
class IBulletStyle
{
public:
	/** Creates a bullet in the specified position */
	virtual Bullet* _createBullet(SceneObject::Position pos) = 0;

protected:
	/** Virtual destructor to supress warnings */
	virtual ~IBulletStyle() { }
};

class RoundBulletStyle: public IBulletStyle
{
public:
	static RoundBulletStyle* getObject();
	static void releaseObject();
	Bullet* _createBullet(SceneObject::Position pos);

private:
	RoundBulletStyle();
	RoundBulletStyle(const RoundBulletStyle&);
	~RoundBulletStyle();
};

class BlastBulletStyle: public IBulletStyle
{
public:
	static BlastBulletStyle* getObject();
	static void releaseObject();
	Bullet* _createBullet(SceneObject::Position pos);

private:
	BlastBulletStyle();
	BlastBulletStyle(const BlastBulletStyle&);
	~BlastBulletStyle();
};

} // namespace sts
