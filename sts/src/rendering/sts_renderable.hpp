#pragma once

#include "sts_attachable.hpp"

namespace sts {

class IRenderable
{
public:
	virtual IAttachable* spawnAttachable() const = 0;
};

} // namespace sts
