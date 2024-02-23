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
	//tileMap�� ������ null�� ������

	isFiring = false;
	fireTimer = fireInterval;
	
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	look = mouseWorldPos - position;
	Utils::Normalize(look); //look vector ����

	//���콺 ������ ���缭 ȸ��//
	SetRotation(Utils::Angle(look));
	/*float angle = Utils::Angle(look);
	sprite.setRotation(angle); */

	// Ű�Է� �޾Ƽ� �����̰� �ϱ�
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	//�밢�� �̵��� �� �ӵ� �������� �� ���� ���ؼ� ��
	if (Utils::Magnitude(direction) > 1.f) 
	{
		Utils::Normalize(direction);
	}

	//��� �ȿ��� �����̰� �ϱ�
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
		fireTimer = 0.f; //��������� ���� ���ݶ� ������ ���ϰԵǴ� ��
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
	//���� �ִ� �浹üũ�� ������� �� �Ѿ��

	//���� ����Ʈ ��ȸ�ϸ鼭 �浹üũ
	for (auto go : list)
	{
		if (!go->GetActive())
			continue;

		//��ġ�� ��ġ��
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
