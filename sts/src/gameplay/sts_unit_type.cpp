#include "sts_unit_type.hpp"

#include <OGRE/OgreRoot.h>

namespace sts {

UnitType::UnitType(std::string _id, Renderable* _renderablePtr, int hm, int sm, const Weapon *w1, const Weapon *w2)
	:id(_id), renderablePtr(_renderablePtr), healthMax(hm), speedMax(sm), weapon1(w1), weapon2(w2)
{
	Ogre::LogManager::getSingleton().logMessage("UnitType created");
}

} // namespace sts
