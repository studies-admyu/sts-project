#include "sts_renderable.hpp"

#include <sts_game_root.hpp>

namespace sts {

Renderable::Renderable(std::string name):
	_name(name)
{
	sts::GameRoot::getObject()->_addRenderable(this);
}

Renderable::~Renderable()
{

}

std::string Renderable::name() const
{
	return this->_name;
}

} // namespace sts
