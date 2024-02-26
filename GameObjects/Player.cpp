#include "pch.h"
#include "Player.h"
#include "TileMap.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "Item.h"
#include "UiHud.h"

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
	hp = maxHp;
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
	//uiHud = dynamic_cast<UiHud*>();

	isFiring = false;
	fireTimer = fireInterval;
	hp = maxHp;
	ammo = maxAmmo;
	reloadingAmmo = 0;

	sceneGame->GetHud()->SetHp(hp, maxHp);
	sceneGame->GetHud()->SetAmmo(ammo, ammo + reloadingAmmo);
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
	if (isFiring && fireTimer > fireInterval && ammo + reloadingAmmo > 0)
	{
		Fire();
		fireTimer = 0.f; //��������� ���� ���ݶ� ������ ���ϰԵǴ� ��
	}

	if (isNoDamage)
	{
		noDamageTimer += dt;
		if (noDamageTimer > noDamageTime)
		{
			isNoDamage = false;
		}
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Player::Fire()
{
	if (ammo + reloadingAmmo == 0)
		return;

	if (ammo == 0 && reloadingAmmo >= 5)
	{
		ammo += 5;
		reloadingAmmo -= 5;
	}
		
	ammo -= 1;
	sceneGame->GetHud()->SetAmmo(ammo, ammo + reloadingAmmo);

	Bullet* bullet = new Bullet();
	bullet->Init();
	bullet->Reset();
	bullet->SetPosition(position);
	bullet->Fire(look, bulletSpeed, bulletDamage);
	sceneGame->AddGo(bullet);

	//���� ���
	//SOUND_MGR.PlaySfx("sound/shoot.wav");


}

void Player::OnDamage(int damage)
{
	if (isAlive && isNoDamage) // ����ְ� �����ð��̸� �׳� �Լ� ��������
		return;

	hp -= damage;
	sceneGame->GetHud()->SetHp(hp, maxHp);

	//�ѹ� �¾����ϱ� �����ð� true�ϰ� ����Ÿ�̸� �ʱ�ȭ
	isNoDamage = true;
	noDamageTimer = 0.f;

	if (hp <= 0)
	{
		hp = 0;
		OnDie();
	}
}

void Player::OnDie()
{
	if (!isAlive) //�̹� �׾������� �Լ� ��������
		return;

	//����־����� active false�� �̹��� �����ֱ�
	isAlive = false;
	SetActive(false);
}

void Player::OnItem(Item* item)
{
	switch (item->GetType())
	{case Item::Types::Ammo:
		reloadingAmmo += item->GetValue();
		if (ammo + item->GetValue() > maxAmmo)
		{
			ammo = maxAmmo;
		}
		sceneGame->GetHud()->SetAmmo(ammo, reloadingAmmo);
		break;
	case Item::Types::Health:
		hp += item->GetValue();
		if (hp + item->GetValue() > maxHp)
		{
			hp = maxHp;
		}
		sceneGame->GetHud()->SetHp(hp, maxHp);
		break;
	}
}