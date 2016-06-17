#pragma once

#include <string>

#include <sts_cross_platform.hpp>
#include <scene/sts_scene_object.hpp>

namespace sts {

class IMotionBehavior
{
public:
	virtual void move(SceneObject& o) = 0;
	// Factory method, chooses child type and creates it.
	// Currently children are hardcoded and not configurable externally. We should change it in the future.
	static IMotionBehavior* createMotionBehavior(std::string mb_name);
};

class MoveForward: public IMotionBehavior
{
public:
	virtual void move(SceneObject& o);

private:
	double speed;
};

class MoveIdle: public IMotionBehavior
{
public:
	virtual void move(SceneObject& o);
};

class MoveStay : public IMotionBehavior
{
public:
	virtual void move(SceneObject& o);
};

class MoveBehaviorException: public std::exception
{
public:
	MoveBehaviorException(const std::string m="MoveBehavior exception was thrown") : msg(m) {}
	virtual ~MoveBehaviorException() {}
	virtual const char* what() const noexcept { return msg.c_str(); }

private:
	std::string msg;
};

} // namespace sts
