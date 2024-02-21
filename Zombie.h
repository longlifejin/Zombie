#pragma once
#include "SpriteGo.h"
#include "Player.h"

class Zombie : public SpriteGo
{
public:
	enum class Types
	{
		Bloater,
		Chase,
		Crawler,
	};
	static const int TotalTypes = 3;
	static Zombie* Create(Types zombieType);

protected:
	Types type;

	int maxHp;
	float speed;
	sf::Vector2f zombieDirection;
	sf::Vector2f zombieLook;

	int hp; //���� hp
	
	Player* player;

	Zombie(const std::string& name = ""); //create�Լ� ���ؼ��� ���� ������� protected ���

public:
	~Zombie() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;





};

