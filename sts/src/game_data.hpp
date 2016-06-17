#pragma once

#include <unordered_map>
#include <boost/filesystem.hpp>

namespace sts {

class IBulletStyle;
struct MuzzleFlashStyle;
class Renderable;
class Weapon;
class UnitType;

/** Static class, stores all the not-level-specific game data */
class GameData
{
public:
	/* read jsons and load data */
	static void load();
	static std::unordered_map<std::string, IBulletStyle*> bulletStyles;
	static std::unordered_map<std::string, MuzzleFlashStyle*> muzzleFlashStyles;
	static std::unordered_map<std::string, Renderable*> renderables;
	static std::unordered_map<std::string, Weapon*> weapons;
	static std::unordered_map<std::string, UnitType*> unit_types;

private:
	GameData() {}
	static boost::filesystem::path configs_path;

	static void parseBulletStyles();
	static void parseMuzzleFlashStyles();
	static void parseRenderables();
	static void parseWeapons();
	static void parseUnitTypes();
};

}
