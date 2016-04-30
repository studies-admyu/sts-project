#pragma once

#include "sts_object_group.hpp"
#include "sts_layered_object.hpp"

namespace sts {

class Layer: public ObjectGroup<LayeredObject>
{
public:
	Layer();
	~Layer();

	void addObject(LayeredObject* object);
	std::list<LayeredObject*> objects();
	void removeObject(LayeredObject* object);
	unsigned char opacity();
	void setOpacity(unsigned char value);

private:
	unsigned char _opacity;
	std::list<LayeredObject*> _objects;

	Layer(const Layer&);
};

} // namespace sts
