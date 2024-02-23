#pragma once
#include "Scene.h"


class Player;
class ZombieSpawner;
class TileMap;
class Zombie;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	TileMap* tileMap;

	std::vector<ZombieSpawner*> spawners;
	std::list<GameObject*> zombieList;
	
public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	const std::list<GameObject*>& GetzombieList() const { return zombieList; }

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

