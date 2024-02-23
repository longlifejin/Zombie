#include "pch.h"
#include "Player.h"
#include "TileMap.h"
#include "SceneGame.h"
#include "Bullet.h"

Player::Player(const std::string& name)
	:SpriteGo(name)
{
}

void Player::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/player.png");
	SetOrigin(Origins::MC);

	isFiring = false;
	fireTimer = fireInterval;
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();

	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	//tileMap이 없으면 null을 리턴함

	isFiring = false;
	fireTimer = fireInterval;
	
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	look = mouseWorldPos - position;
	Utils::Normalize(look); //look vector 갱신

	//마우스 포인터 맞춰서 회전//
	SetRotation(Utils::Angle(look));
	/*float angle = Utils::Angle(look);
	sprite.setRotation(angle); */

	// 키입력 받아서 움직이게 하기
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	//대각선 이동할 때 속도 높아지는 걸 막기 위해서 씀
	if (Utils::Magnitude(direction) > 1.f) 
	{
		Utils::Normalize(direction);
	}

	//경계 안에서 움직이게 하기
	sf::Vector2f pos = position + direction * speed * dt;

	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (sceneGame != nullptr)
	{
		pos = sceneGame->ClampByTileMap(pos);
	}
	SetPosition(pos);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		isFiring = true;
	}

	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
	{
		isFiring = false;
	}

	fireTimer += dt;
	if (isFiring && fireTimer > fireInterval)
	{
		Fire();
		fireTimer = 0.f; //리셋해줘야 다음 간격때 동작을 안하게되는 것
	}

	beatTime += dt;
	if (isbeated && beatTime > unbeatableTime)
	{
		OnDamage(10);
		beatTime = 0.f;
		isbeated = false;
	}
}

void Player::FixedUpdate(float dt)
{
	const std::list<GameObject*>& list = sceneGame->GetzombieList();
	//씬에 있는 충돌체크할 좀비들이 다 넘어옴

	//위의 리스트 순회하면서 충돌체크
	for (auto go : list)
	{
		if (!go->GetActive())
			continue;

		//위치가 겹치면
		if (GetGlobalBounds().intersects(go->GetGlobalBounds()))
		{
			isbeated = true;
			break;
		}
	}
	
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Player::Fire()
{
	Bullet* bullet = new Bullet();
	bullet->Init();
	bullet->Reset();
	bullet->SetPosition(position);
	bullet->Fire(look, bulletSpeed, bulletDamage);
	sceneGame->AddGo(bullet);
}

void Player::OnDamage(int damage)
{
	hp -= damage;

	if (hp <= 0)
	{
		hp = 0;
		OnDie();
	}
}

void Player::OnDie()
{
	
	SetActive(false);
	//sceneGame->RemoveGo(this);
}
