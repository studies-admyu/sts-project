#include "sts_layer.hpp"

namespace sts {

Layer::Layer()
{
	this->_opacity = 255;
}

Layer::Layer(const Layer& clayer)
{

}

Layer::~Layer()
{

}

void Layer::addObject(LayeredObject* object)
{
	if (!object) {
		return;
	}

	bool addObject = true;
	for (auto obj = this->_objects.begin(); obj != this->_objects.end(); ++obj) {
		addObject = (*obj != object);
		if (!addObject) {
			break;
		}
	}

	if (addObject) {
		this->_objects.push_back(object);
	}
}

std::list<LayeredObject*> Layer::objects()
{
	return std::list<LayeredObject*>(this->_objects);
}

void Layer::removeObject(LayeredObject* object)
{
	if (!object) {
		return;
	}

	bool removeObject = false;
	auto obj = this->_objects.begin();
	for (; obj != this->_objects.end(); ++obj) {
		if (*obj != object) {
			removeObject = true;
			break;
		}
	}
	if (removeObject) {
		this->_objects.erase(obj);
	}
}

unsigned char Layer::opacity()
{
	return this->_opacity;
}

void Layer::setOpacity(unsigned char value)
{
	this->_opacity = value;
}

} // namespace sts
