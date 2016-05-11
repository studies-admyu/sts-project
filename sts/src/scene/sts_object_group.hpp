#pragma once

#include <list>

namespace sts {

template <typename T>
class ObjectGroup
{
public:
	virtual void addObject(T*) = 0;
	virtual std::list<T*> objects() = 0;
	virtual void removeObject(T*) = 0;
	virtual unsigned char opacity() const = 0;
	virtual void setOpacity(unsigned char) = 0;
};

} // namespace sts
