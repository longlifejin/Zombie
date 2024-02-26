#pragma once
#include "Spawner.h"
#include "Zombie.h"

class SceneGame;

class ZombieSpawner : public Spawner
{
protected:
	std::vector<Zombie::Types> zombieTypes;
	int wave1ZombieCount = 30;
	int wave2ZombieCount = 50;

	SceneGame* sceneGame;

public:
	ZombieSpawner(const std::string& name = "");
	~ZombieSpawner() override = default;

	GameObject* Create() override;
	void Reset() override;

};

