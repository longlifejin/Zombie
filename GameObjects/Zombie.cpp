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
	hp = maxHp;
	isAlive = true;
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	attackInterval = 5.f;
}

void Zombie::Update(float dt)
{
	SpriteGo::Update(dt);

	if (!isAlive) //죽어있으면 밑에 있는 코드 아무것도 동작 안하도록
		return;

	zomdirection = player->GetPosition() - position;
	Utils::Normalize(zomdirection);
	SetRotation(Utils::Angle(zomdirection));
	
	//경계 안에서 움직이게 만들기
	sf::Vector2f pos = position + zomdirection * speed * dt;

	if (sceneGame != nullptr)
	{
		pos = sceneGame->ClampByTileMap(pos);
	}
	SetPosition(pos);

	//sf::Vector2f playerToZombieDistance = player->GetPosition() - position; //플레이어와 좀비 사이 거리 차이(vector2f형)
	//float zombieAngle = Utils::Angle(playerToZombieDistance);
	//SetRotation(zombieAngle);
	//
	//Utils::Normalize(playerToZombieDistance); //1 또는 -1로 만들어주는 것 //왜 해주는지 알아보기
	//Translate(playerToZombieDistance * speed * dt);
}

void Zombie::FixedUpdate(float dt)
{
	attackTimer += dt;

	if (attackTimer > attackInterval)
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
	if (!isAlive) //죽어있으면 리턴
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
	if (!isAlive) //죽어있으면 리턴
		return;

	//죽을 때 할 일
	isAlive = false;
	SetActive(false);
	sceneGame->RemoveGo(this);
}
