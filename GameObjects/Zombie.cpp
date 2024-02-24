#include "pch.h"
#include "Zombie.h"
#include "player.h"
#include "SceneGame.h"

Zombie* Zombie::Create(Types zombieType)
{
	Zombie* zombie = new Zombie("Zombie");
	zombie->type = zombieType;

	switch (zombieType)
	{
	case Zombie::Types::Bloater:
		zombie->textureId = "graphics/bloater.png";
		zombie->maxHp = 40;
		zombie->speed = 100;
		zombie->damage = 100;
		zombie->attackInterval = 1.f;
		break;
	case Zombie::Types::Chaser:
		zombie->textureId = "graphics/chaser.png";
		zombie->maxHp = 70;
		zombie->speed = 75;
		zombie->damage = 50;
		zombie->attackInterval = 0.5f;
		break;
	case Zombie::Types::Crawler:
		zombie->textureId = "graphics/crawler.png";
		zombie->maxHp = 20;
		zombie->speed = 50;
		zombie->damage = 75;
		zombie->attackInterval = 0.25f;
		break;
	}
	return zombie;
}

Zombie::Zombie(const std::string& name)
	: SpriteGo(name)
{
}

void Zombie::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);
}

void Zombie::Release()
{
	SpriteGo::Release();
}

void Zombie::Reset()
{
	SpriteGo::Reset();
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	
	isAlive = true;
	hp = maxHp;
	attackTimer = attackInterval; //���� �ð� �ʱ�ȭ
}

void Zombie::Update(float dt)
{
	SpriteGo::Update(dt);

	if (!isAlive) //�׾������� �ؿ� �ִ� �ڵ� �ƹ��͵� ���� ���ϵ���
		return;

	direction = player->GetPosition() - position;
	Utils::Normalize(direction);

	SetRotation(Utils::Angle(direction));
	
	//��� �ȿ��� �����̰� �����
	sf::Vector2f pos = position + direction * speed * dt;
	if (sceneGame != nullptr)
	{
		pos = sceneGame->ClampByTileMap(pos);
	}
	SetPosition(pos);
}

void Zombie::FixedUpdate(float dt)
{
	attackTimer += dt;

	if (attackTimer > attackInterval) //���� �� �ִ� �ð��� �Ǹ�
	{
		if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
		{
			player->OnDamage(damage);
			attackTimer = 0.f;
		}
	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Zombie::OnDamage(int damage)
{
	if (!isAlive) //�׾������� ����
		return;

	hp -= damage;
	if (hp <= 0)
	{
		hp = 0;
		OnDie();
	}
}

void Zombie::OnDie()
{
	if (!isAlive) //�׾������� ����
		return;

	//���� �� �� ��
	isAlive = false;
	SetActive(false);
	sceneGame->RemoveGo(this);
}
