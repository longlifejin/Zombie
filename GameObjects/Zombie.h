#pragma once
#include "SpriteGo.h"
#include "Player.h"

class Zombie : public SpriteGo
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler,
	};
	static const int TotalTypes = 3;
	static Zombie* Create(Types zombieType);

protected:
	Types type;

	int maxHp;
	float speed;
	sf::Vector2f zombieDirection = { 0.f, 0.f };
	sf::Vector2f zombieLook = { 1.f, 0.f };

	int hp; //���� hp

	Player* player;

	sf::Vector2f zomdirection;

	Zombie(const std::string& name = ""); //create�Լ� ���ؼ��� ���� ������� protected ���

public:
	~Zombie() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;





};

