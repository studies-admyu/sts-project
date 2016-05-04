#include "sts_layer.hpp"

namespace sts {

Layer::Layer()
{
	this->_speed = 0;
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

unsigned char Layer::opacity() const
{
	return this->_opacity;
}

void Layer::setOpacity(unsigned char value)
{
	this->_opacity = value;
}

unsigned int Layer::speed() const
{
	return this->_speed;
}

void Layer::setSpeed(unsigned int value)
{
	this->_speed = value;
}

void Layer::processLayer()
{

}

} // namespace sts
