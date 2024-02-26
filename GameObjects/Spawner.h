#pragma once
#include "GameObject.h"

class SceneGame;

class Spawner :  public GameObject
{

protected:

	float interval = 1.f; //���� �ֱ�
	int spawnCount = 1; //�� ������ ������ ��
	float radius = 250.f; //���� �ݰ�

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
