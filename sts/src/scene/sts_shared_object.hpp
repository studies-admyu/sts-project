#pragma once

#include "sts_scene_object.hpp"

namespace sts {

class SharedObject: public SceneObject
{
public:
	static SharedObject* create(Renderable* renderable);
	~SharedObject();

protected:
	SharedObject(Renderable* renderable);
};

} // namespace sts
