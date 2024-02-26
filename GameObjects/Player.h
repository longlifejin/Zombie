#pragma once
#include "SpriteGo.h"

class SceneGame;
class Item;
class UiHud;

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction = { 0.f, 0.f }; //이동 방향
	sf::Vector2f look = { 1.f, 0.f }; // 회전 방향
	float speed = 500.f;
	
	SceneGame* sceneGame = nullptr;
	UiHud* uiHud = nullptr;
	
	//player 체력 관련
	int maxHp = 300;
	int hp;
	bool isAlive = true;
	bool isNoDamage = false; //무적시간인지 아닌지
	float noDamageTime = 1.f;
	float noDamageTimer = 0.f;

	//발사체 관련
	float bulletSpeed = 1000.f;
	int bulletDamage = 10;

	bool isFiring = false; //쏘고있는지 아닌지 체크해주기
	float fireInterval = 0.1f; //발사 간격
	float fireTimer = 0.f; //interval로 초기화해서 빼기할 거임

	//Item 관련
	int maxAmmo = 20;
	int ammo = 0;


public:
	Player(const std::string& name = "");
	~Player() override = default; //가상 소멸자 재구현

	sf::Vector2f GetDirection() { return this->direction; }


	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	void Fire(); //바라보는 방향대로 쏘는 것

	void OnDamage(int damage); //호출되면 hp가 깎임
	void OnDie(); //0이 되면 죽이는 일
	void OnItem(Item* item);
};

