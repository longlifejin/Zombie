#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"

SceneGame::SceneGame(SceneIds id)
	:Scene(id)
{
}

void SceneGame::Init()
{
	AddGo(new TileMap("Background"));

	player = new Player("Player");
	AddGo(player);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release(); //�θ� Ŭ���� �Լ� ȣ��
}

void SceneGame::Enter()
{
	Scene::Enter();

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f,0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
	tileMap->SetPosition({ 0.f,0.f });
	tileMap->SetOrigin(Origins::MC);
	player->SetPosition({ 0.f,0.f });
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	worldView.setCenter(player->GetPosition()); //�÷��̾ ��� �߾ӿ� ����
	
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		Zombie::Types zombieType = (Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes);
		Zombie* zombie = Zombie::Create(zombieType);
		zombie->Init();
		zombie->Reset();
		zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f); //�ݰ��� 500�� �� �ȿ� ���� ����

		AddGo(zombie);
	}

	//�浹�� ���� ��ü �����
	std::list<GameObject*> removeZombieobj; //���� ���� ��ü ��Ƶα�
	for (auto obj : gameObjects)
	{
		Zombie* zombie = dynamic_cast<Zombie*>(obj);
		if (zombie != nullptr)
		{
			if (Utils::Distance(zombie->GetPosition(), player->GetPosition()) <= 10.f)
			{
				removeZombieobj.push_back(obj);
			}
		}
	}

	for(auto obj : removeZombieobj)
	{
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), obj), gameObjects.end());
		delete obj;
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
