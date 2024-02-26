#pragma once
#include "GameObject.h"

class SceneGame;

class Spawner :  public GameObject
{

protected:

	float interval = 1.f; //积己 林扁
	int spawnCount = 1; //割 付府究 积己且 瘤
	float radius = 250.f; //积己 馆版

	float timer = 0.f;

	SceneGame* sceneGame = nullptr;

public:
	Spawner(const std::string& name = "");
	~Spawner() override = default;

	virtual GameObject* Create() = 0;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
};
