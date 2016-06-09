#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <boost/filesystem.hpp>

#include "entity.hpp"

namespace sts {

class IBulletStyle;
struct MuzzleFlashStyle;
class Weapon;
class UnitType;
class IWeaponBehaviour;

/* static class, stores all the not-level-specific game data */
class GameData {
public:
    /* read jsons and load data */
    static void load();
	static std::unordered_map<std::string, MuzzleFlashStyle*> muzzleFlashStyles;
	static std::unordered_map<std::string, Entity*> entities;
    static std::unordered_map<std::string, IBulletStyle*> bulletStyles;
	static std::unordered_map<std::string, Weapon*> weapons;
	static std::unordered_map<std::string, UnitType*> unit_types;
private:
    GameData() {}
    static boost::filesystem::path configs_path;

	static void parseMuzzleFlashStyles();
	static void parseEntities();
    static void parseBulletStyles();
	static void parseWeapons();
	static void parseUnitTypes();
};

}
