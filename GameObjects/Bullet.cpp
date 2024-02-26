#include "pch.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "Zombie.h"

Bullet::Bullet(const std::string& name)
	: SpriteGo(name)
{
}

void Bullet::Fire(const sf::Vector2f& dir, float s, int d)
{
	direction = dir;
	speed = s;
	damage = d;

	//회전 세팅
	SetRotation(Utils::Angle(direction));
}

void Bullet::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/bullet.png");
	SetOrigin(Origins::ML);
}

void Bullet::Reset()
{
	SpriteGo::Reset();
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
}

void Bullet::Update(float dt)
{
	SetPosition(position + direction * speed * dt);

	if (sceneGame != nullptr)
	{
		//벽에 부딪히면 삭제하게
		if (!sceneGame->isInTileMap(position))
		{
			SetActive(false); //다른 애들이랑 상호작용 하지 않도록
			sceneGame->RemoveGo(this);
		}
	}
}

void Bullet::FixedUpdate(float dt)
{
	const std::list<GameObject*>& list = sceneGame->GetzombieList();
	//씬에 있는 충돌체크할 좀비들이 다 넘어옴

	//위의 리스트 순회하면서 충돌체크
	for (auto go : list)
	{
		if (!go->GetActive()) //active false인 좀비는 그냥 두게
			continue;

		//위치가 겹치면
		if (GetGlobalBounds().intersects(go->GetGlobalBounds()))
		{
			SetActive(false); //총알 active false로 만들고
			sceneGame->RemoveGo(this); //총알 지워주기
			//겹쳐지는 오브젝트가 있으면 delete한 애를 또 delete해서 에러가 나니까 따로 처리해줘야함
			
			
			Zombie* zombie = dynamic_cast<Zombie*>(go);
			if(zombie != nullptr)
				zombie->OnDamage(10);
			break;
		}
	}
}
