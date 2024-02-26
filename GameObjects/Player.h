#pragma once
#include "SpriteGo.h"

class SceneGame;
class Item;
class UiHud;

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction = { 0.f, 0.f }; //�̵� ����
	sf::Vector2f look = { 1.f, 0.f }; // ȸ�� ����
	float speed = 500.f;
	
	SceneGame* sceneGame = nullptr;
	UiHud* uiHud = nullptr;
	
	//player ü�� ����
	int maxHp = 300;
	int hp;
	bool isAlive = true;
	bool isNoDamage = false; //�����ð����� �ƴ���
	float noDamageTime = 1.f;
	float noDamageTimer = 0.f;

	//�߻�ü ����
	float bulletSpeed = 1000.f;
	int bulletDamage = 10;

	bool isFiring = false; //����ִ��� �ƴ��� üũ���ֱ�
	float fireInterval = 0.1f; //�߻� ����
	float fireTimer = 0.f; //interval�� �ʱ�ȭ�ؼ� ������ ����

	//Item ����
	int maxAmmo = 20;
	int ammo = 0;


public:
	Player(const std::string& name = "");
	~Player() override = default; //���� �Ҹ��� �籸��

	sf::Vector2f GetDirection() { return this->direction; }


	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	void Fire(); //�ٶ󺸴� ������ ��� ��

	void OnDamage(int damage); //ȣ��Ǹ� hp�� ����
	void OnDie(); //0�� �Ǹ� ���̴� ��
	void OnItem(Item* item);
};

