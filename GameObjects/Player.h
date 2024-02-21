#pragma once
#include "SpriteGo.h"

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction = { 0.f, 0.f }; //�̵� ����
	sf::Vector2f look = { 1.f, 0.f }; // ȸ�� ����
	float speed = 400.f;


public:
	Player(const std::string& name = "");
	~Player() override = default; //���� �Ҹ��� �籸��

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

