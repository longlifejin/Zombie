#pragma once
#include "GameObject.h"
#include "Zombie.h"
class ZombieSpawner : public GameObject
{
protected:
	std::vector<Zombie::Types> zombieTypes;

	float interval = 1.f; //积己 林扁
	int spawnCount = 1; //割 付府究 积己且 瘤
	float radius = 250.f; //积己 馆版

	float timer = 0.f;

public:
	ZombieSpawner(const std::string& name = "");
	~ZombieSpawner() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
};

