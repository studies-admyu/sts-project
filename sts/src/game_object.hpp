#pragma once

#include <string>
#include <list>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>

namespace sts {

class IFiringStyle;
class Entity;
class Weapon;
class IWeaponBehaviour;

namespace pt = boost::property_tree;


class GameObject {
public:
	GameObject(int _x, int _y, double _d) : x(_x), y(_y), direction(_d) {}
	double direction;
	int x;
	int y;
};

class LayeredObject : public GameObject {
public:
	LayeredObject(int x, int y, double d) : GameObject(x, y, d) {}
};

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
	UnitType(std::string id, Entity *entityPtr, int hm, int sm, const Weapon *w1, const Weapon *w2);

	std::string id;
	Entity *entityPtr;
	int healthMax;
	int speedMax;
	const Weapon *weapon1;
	const Weapon *weapon2;
};

class Unit : public LayeredObject {
public:
	Unit(int x, int y, double d, const UnitType* utptr, std::list<State> states);
	const UnitType *unitTypePtr;
	IFiringStyle *firingStyleW1Ptr;
	IFiringStyle *firingStyleW2Ptr;
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