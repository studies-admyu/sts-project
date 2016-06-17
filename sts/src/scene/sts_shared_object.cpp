#include "sts_shared_object.hpp"

#include <sts_game_root.hpp>

namespace sts {

SharedObject::SharedObject(Renderable* renderable):
	SceneObject(renderable)
{
	sts::GameRoot::getObject()->sceneManager()->sharedObjects()->addObject(this);
}

SharedObject::~SharedObject()
{

}

SharedObject* SharedObject::create(Renderable* renderable)
{
	return new SharedObject(renderable);
}

SharedObject* SharedObject::create(std::string renderableName)
{
	return SharedObject::create(sts::GameRoot::getObject()->getRenderable(renderableName));
}

} // namespace sts
