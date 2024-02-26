#pragma once
#include "Scene.h"


class Player;
class ZombieSpawner;
class ItemSpawner;
class Spawner;
class TileMap;
class Zombie;
class UiHud;
class SpriteGo;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	TileMap* tileMap; 

	UiHud* uiHud;
	SpriteGo* crosshair;

	std::vector<Spawner*> spawners;
	std::vector<ItemSpawner*> itemSpawners;
	std::list<GameObject*> zombieList;
	std::list<GameObject*> itemList;
	
public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	const std::list<GameObject*>& GetzombieList() const { return zombieList; }

	UiHud* GetHud() const { return uiHud; }

	bool isInTileMap(const sf::Vector2f& point);
	sf::Vector2f ClampByTileMap(const sf::Vector2f& point);

	void Init() override;
	void Release()override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

