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
	sf::Vector2f playerToZombieDistance = player->GetPosition() - position; //플레이어와 좀비 사이 거리 차이(vector2f형)
	float zombieAngle = Utils::Angle(playerToZombieDistance);
	SetRotation(zombieAngle);
	
	Utils::Normalize(playerToZombieDistance); //1 또는 -1로 만들어주는 것 //왜 해주는지 알아보기
	Translate(playerToZombieDistance * speed * dt);

}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
