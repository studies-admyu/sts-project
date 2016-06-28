#include "sts_renderable.hpp"

#include <stdexcept>

#include <sts_game_root.hpp>

namespace sts {

Renderable::Renderable(std::string name):
	_name(name)
{
	if (name.size() == 0) {
		throw std::runtime_error("Attempt to create a Renderable with empty name.");
	}
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
