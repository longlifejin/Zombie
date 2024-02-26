#pragma once
#include "SpriteGo.h"
#include "Player.h"

class SceneGame;

class Zombie : public SpriteGo
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler,
		None,
	};
	static const int TotalTypes = 3;
	static Zombie* Create(Types zombieType);


protected:
	Types type;

	int maxHp;
	float speed;
	int damage;
	float attackInterval;
	float attackTimer = 0.f;

	sf::Vector2f zombieDirection = { 0.f, 0.f };
	sf::Vector2f zombieLook = { 1.f, 0.f };

	int hp; //���� hp
	int zombieCount = 30;

	Player* player;
	SceneGame* sceneGame;

	sf::Vector2f direction;
	bool isAlive = true; //zombie �׾��� ���׾��� �˻�

	Zombie(const std::string& name = ""); //create�Լ� ���ؼ��� ���� ������� protected ���

public:
	~Zombie() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void OnDamage(int damage); //ȣ��Ǹ� hp�� ����
	void OnDie(); //0�� �Ǹ� ���̴� ��
	void PlayBloodEffect();


};

