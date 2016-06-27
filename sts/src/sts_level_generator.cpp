#include "sts_level_generator.hpp"

#include "sts_game_root.hpp"
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

	/* Create enemies */
	sts::SceneObject::Position shipPosition(0, 0);
	shipPosition.x = lGameRoot->sceneManager()->sceneWidth() / 2;
	shipPosition.y = lGameRoot->sceneManager()->sceneHeight() / 2;

	sts::Unit* lEnemyShip = sts::Unit::create("EnemySprite01", (unsigned int)1, nullptr, std::list<sts::SM::State*>());
	lEnemyShip->setPosition(shipPosition + sts::SceneObject::Position(0, 200));
}
