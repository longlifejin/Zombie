#pragma once
#include "SpriteGo.h"

class SceneGame;

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction = { 0.f, 0.f }; //�̵� ����
	sf::Vector2f look = { 1.f, 0.f }; // ȸ�� ����
	float speed = 400.f;
	int hp = 30;
	
	bool isbeated = false;
	float unbeatableTime = 3.f;
	float beatTime = 0.f;

	SceneGame* sceneGame = nullptr;

	bool isFiring = false; //����ִ��� �ƴ��� üũ���ֱ�
	float fireInterval = 0.1f; //�߻� ����
	float fireTimer = 0.f; //interval�� �ʱ�ȭ�ؼ� ������ ����
	float bulletSpeed = 1000.f;
	int bulletDamage = 10;

public:
	Player(const std::string& name = "");
	~Player() override = default; //���� �Ҹ��� �籸��

	sf::Vector2f GetDirection() { return this->direction; }

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void FixedUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	void Fire(); //�ٶ󺸴� ������ ��� ��
	void OnDamage(int damage); //ȣ��Ǹ� hp�� ����
	void OnDie(); //0�� �Ǹ� ���̴� ��
};

