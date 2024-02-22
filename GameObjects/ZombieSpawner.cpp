#include "pch.h"
#include "ZombieSpawner.h"

ZombieSpawner::ZombieSpawner(const std::string& name)
	:GameObject(name)
{
}

void ZombieSpawner::Init()
{
	GameObject::Init();
}

void ZombieSpawner::Release()
{
	GameObject::Release();

}

void ZombieSpawner::Reset()
{
	GameObject::Reset();

	zombieTypes.clear();
	zombieTypes.push_back(Zombie::Types::Bloater); //제일 적게 나오게
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Crawler);
	zombieTypes.push_back(Zombie::Types::Crawler);

	interval = 1.f;
	spawnCount = 1;
	radius = 250.f;
	timer = 0.f;
}

void ZombieSpawner::Update(float dt)
{
	GameObject::Update(dt);

	timer += dt;
	if (timer > interval) //interval초마다 할 일 적어주기
	{
		timer = 0.f;

		for (int i = 0; i < spawnCount; ++i)
		{
			sf::Vector2f pos = position + Utils::RandomInUnitCircle() * radius;
			Zombie::Types zombieType = zombieTypes[Utils::RandomRange(0, zombieTypes.size())];
		
			Zombie* zombie = Zombie::Create(zombieType);
			zombie->Init();
			zombie->Reset();
			zombie->SetPosition(pos);
			SCENE_MGR.GetCurrentScene()->AddGo(zombie);
		}
	}
}
