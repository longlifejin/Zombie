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

	//ȸ�� ����
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
		//���� �ε����� �����ϰ�
		if (!sceneGame->isInTileMap(position))
		{
			SetActive(false); //�ٸ� �ֵ��̶� ��ȣ�ۿ� ���� �ʵ���
			sceneGame->RemoveGo(this);
		}
	}
}

void Bullet::FixedUpdate(float dt)
{
	const std::list<GameObject*>& list = sceneGame->GetzombieList();
	//���� �ִ� �浹üũ�� ������� �� �Ѿ��

	//���� ����Ʈ ��ȸ�ϸ鼭 �浹üũ
	for (auto go : list)
	{
		if (!go->GetActive()) //active false�� ����� �׳� �ΰ�
			continue;

		//��ġ�� ��ġ��
		if (GetGlobalBounds().intersects(go->GetGlobalBounds()))
		{
			SetActive(false); //�Ѿ� active false�� �����
			sceneGame->RemoveGo(this); //�Ѿ� �����ֱ�
			//�������� ������Ʈ�� ������ delete�� �ָ� �� delete�ؼ� ������ ���ϱ� ���� ó���������
			
			
			Zombie* zombie = dynamic_cast<Zombie*>(go);
			if(zombie != nullptr)
				zombie->OnDamage(10);
			break;
		}
	}
}
