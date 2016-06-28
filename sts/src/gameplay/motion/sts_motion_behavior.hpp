#pragma once

#include <exception>

#include <string>

#include <sts_cross_platform.hpp>
#include <input/sts_key.hpp>
#include <scene/sts_scene_object.hpp>

namespace sts {

class IMotionState;

class IMotionBehavior
{
public:
	virtual IMotionState* _createMotionState() = 0;
	/** Virtual destructor to supress warnings. */
	virtual ~IMotionBehavior() { }
};

class MoveIdle: public IMotionBehavior
{
public:
	MoveIdle();
	~MoveIdle();

	IMotionState* _createMotionState();

private:
	MoveIdle(const MoveIdle&);
};

class MoveStay : public IMotionBehavior
{
public:
	MoveStay();
	~MoveStay();

	IMotionState* _createMotionState();

private:
	MoveStay(const MoveStay&);
};

class MoveForward: public IMotionBehavior
{
public:
	MoveForward();
	~MoveForward();

	IMotionState* _createMotionState();

private:
	MoveForward(const MoveForward&);
};

class MoveByKeys: public IMotionBehavior
{
public:
	MoveByKeys(Key mvUpKey, Key mvDownKey, Key mvLeftKey, Key mvRightKey);
	~MoveByKeys();

	IMotionState* _createMotionState();

private:
	Key _moveUpKey;
	Key _moveDownKey;
	Key _moveLeftKey;
	Key _moveRightKey;

	MoveByKeys(const MoveByKeys&);
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
