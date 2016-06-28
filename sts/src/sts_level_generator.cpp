#include "sts_level_generator.hpp"

#include "sts_game_root.hpp"
#include "gameplay/weaponry/sts_weapon.hpp"
#include "gameplay/weaponry/sts_bullet_style.hpp"
#include "gameplay/weaponry/sts_firing_style.hpp"
#include "gameplay/sts_unit.hpp"
#include "rendering/sts_model3d.hpp"
#include "rendering/sts_sprite2d.hpp"

void generateLevel()
{
	sts::GameRoot* lGameRoot = sts::GameRoot::getObject();

	/* Create layers */
	lGameRoot->sceneManager()->addLayer(1)->setSpeed(-60);

	/* Load renderables */
	sts::Model3D::create("ShipModel", "airship.mesh", 6.3f);
	sts::Sprite2D::create("EnemySprite01", "enemy_01", sts::Sprite2D::Size(48, 58));

	/* Create weapons */
	sts::Weapon::create(
		"EnemyWeapon", sts::RoundBulletStyle::getObject(),
		new sts::SingleFiringStyle(), 10, 500, false
	);

	/* Create unit types */
	sts::UnitType::create("HeroShip", "ShipModel", 100, 100, nullptr, nullptr);
	sts::UnitType::create("Enemy01", "EnemySprite01", 100, 100, "EnemyWeapon", "");

	/* Create enemies */
	sts::SceneObject::Position shipPosition(0, 0);
	shipPosition.x = lGameRoot->sceneManager()->sceneWidth() / 2;
	shipPosition.y = lGameRoot->sceneManager()->sceneHeight() / 2;

	sts::Unit* lEnemyShip = sts::Unit::create("Enemy01", (unsigned int)1, 2, nullptr);
	lEnemyShip->setPosition(shipPosition + sts::SceneObject::Position(0, 200));
}
