#pragma once

#include <string>
#include <list>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>

#include "sts_cross_platform.hpp"
#include "scene/sts_layered_object.hpp"

namespace sts {

class Renderable;
class Weapon;
class IWeaponBehaviour;

namespace pt = boost::property_tree;

class Transition {

};

class State {
public:
	IWeaponBehaviour *iwb1;
	IWeaponBehaviour *iwb2;
	std::list<Transition> transitions;
};

class UnitType {
public:
	UnitType(std::string id, Renderable *renderablePtr, int hm, int sm, const Weapon *w1, const Weapon *w2);

	std::string id;
	Renderable* renderablePtr;
	int healthMax;
	int speedMax;
	const Weapon *weapon1;
	const Weapon *weapon2;
};

class Unit : public LayeredObject {
public:
	Unit(Renderable* renderable, unsigned int layerIndex, const UnitType* utptr, std::list<State> states);
	Unit(Renderable* renderable, Layer* layer, const UnitType* utptr, std::list<State> states);
	const UnitType *unitTypePtr;
	std::list<State> states;
};


class Level {
public:
	Level(std::string level_json_name);
	static boost::filesystem::path configs_path;
	static std::list<State> parseStates(pt::ptree);
	static State parseState(pt::ptree);

	std::list<Unit> units;
};

}
