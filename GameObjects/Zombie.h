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

	int hp; //현재 hp
	int zombieCount = 30;

	Player* player;
	SceneGame* sceneGame;

	sf::Vector2f direction;
	bool isAlive = true; //zombie 죽었나 안죽었나 검사

	Zombie(const std::string& name = ""); //create함수 통해서만 좀비 만들려고 protected 멤버

public:
	~Zombie() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void OnDamage(int damage); //호출되면 hp가 깎임
	void OnDie(); //0이 되면 죽이는 일
	void PlayBloodEffect();


};

