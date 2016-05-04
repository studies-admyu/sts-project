#pragma once

#include "sts_object_group.hpp"
#include "sts_shared_object.hpp"

namespace sts {

class SharedObjectGroup: public ObjectGroup<SharedObject>
{
public:
	SharedObjectGroup();
	~SharedObjectGroup();

	void addObject(SharedObject* object);
	std::list<SharedObject*> objects();
	void removeObject(SharedObject* object);
	unsigned char opacity() const;
	void setOpacity(unsigned char);

private:
	unsigned char _opacity;
	std::list<SharedObject*> _objects;

	SharedObjectGroup(const SharedObjectGroup&);
};

} // namespace sts
