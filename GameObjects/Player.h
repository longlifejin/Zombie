#pragma once
#include "SpriteGo.h"

class SceneGame;

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction = { 0.f, 0.f }; //이동 방향
	sf::Vector2f look = { 1.f, 0.f }; // 회전 방향
	float speed = 400.f;
	int hp = 30;
	
	bool isbeated = false;
	float unbeatableTime = 3.f;
	float beatTime = 0.f;

	SceneGame* sceneGame = nullptr;

	bool isFiring = false; //쏘고있는지 아닌지 체크해주기
	float fireInterval = 0.1f; //발사 간격
	float fireTimer = 0.f; //interval로 초기화해서 빼기할 거임
	float bulletSpeed = 1000.f;
	int bulletDamage = 10;

public:
	Player(const std::string& name = "");
	~Player() override = default; //가상 소멸자 재구현

	sf::Vector2f GetDirection() { return this->direction; }

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void FixedUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	void Fire(); //바라보는 방향대로 쏘는 것
	void OnDamage(int damage); //호출되면 hp가 깎임
	void OnDie(); //0이 되면 죽이는 일
};

