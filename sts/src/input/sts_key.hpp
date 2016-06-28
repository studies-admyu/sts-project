#pragma once

#include <OIS/OISKeyboard.h>

namespace sts {

class Key
{
public:
	Key();
	Key(OIS::KeyCode keyCode);
	Key(const Key&);
	~Key();

	Key& operator=(const Key&);
	bool operator==(const Key&) const;

private:
	OIS::KeyCode _keyCode;
};

} // namespace sts
