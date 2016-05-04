#include "sts_shared_object_group.hpp"

namespace sts {

SharedObjectGroup::SharedObjectGroup()
{
	/** @todo Add opacity functionality */
	this->_opacity = 255;
}

SharedObjectGroup::SharedObjectGroup(const SharedObjectGroup& sobjgroup)
{

}

SharedObjectGroup::~SharedObjectGroup()
{

}

void SharedObjectGroup::addObject(SharedObject* object)
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

std::list<SharedObject*> SharedObjectGroup::objects()
{
	return std::list<SharedObject*>(this->_objects);
}

void SharedObjectGroup::removeObject(SharedObject* object)
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

unsigned char SharedObjectGroup::opacity() const
{
	return this->_opacity;
}

void SharedObjectGroup::setOpacity(unsigned char value)
{
	this->_opacity = value;
}

} // namespace sts
