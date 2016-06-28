#include "sts_key.hpp"

namespace sts {

Key::Key()
	: _keyCode(OIS::KC_RETURN)
{

}

Key::Key(OIS::KeyCode keyCode)
	: _keyCode(keyCode)
{

}

Key::Key(const Key& k)
	: _keyCode(k._keyCode)
{

}

Key::~Key()
{

}

Key& Key::operator=(const Key& k)
{
	this->_keyCode = k._keyCode;
	return *this;
}

bool Key::operator==(const Key& k) const
{
	return this->_keyCode == k._keyCode;
}

} // namespace sts
