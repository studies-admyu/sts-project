#pragma once

namespace sts {

class SceneObject;

class IMotionState
{
public:
	virtual void process(SceneObject* obj) = 0;
	/** Virtual destructor to supress warnings. */
	virtual ~IMotionState() { }
};

} // namespace sts
