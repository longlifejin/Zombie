#include "pch.h"
#include "Zombie.h"
#include "player.h"

Zombie* Zombie::Create(Types zombieType)
{
	Zombie* zombie = new Zombie();
	zombie->type = zombieType;

	switch (zombieType)
	{
	case Zombie::Types::Bloater:
		zombie->textureId = "graphics/bloater.png";
		zombie->maxHp = 40;
		zombie->speed = 100;
		break;
	case Zombie::Types::Chase:
		zombie->textureId = "graphics/chaser.png";
		zombie->maxHp = 70;
		zombie->speed = 75;
		break;
	case Zombie::Types::Crawler:
		zombie->textureId = "graphics/crawler.png";
		zombie->maxHp = 20;
		zombie->speed = 50;
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
}

void Zombie::Update(float dt)
{
	SpriteGo::Update(dt);

	////////////////////숙제에에에에에에에에ㅔ에///////////////////
	//player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));

	//Zombie* zombie = dynamic_cast<Zombie*>(SCENE_MGR.GetCurrentScene()->FindGo("zombie"));
	//zombie->SetRotation(player->GetRotation());
	//zombie->zombieDirection = player->direction;
	//zombie->Translate(zombie->zombieDirection * speed * dt);
}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
