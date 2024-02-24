#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"

SceneGame::SceneGame(SceneIds id)
	:Scene(id)
{
}

bool SceneGame::isInTileMap(const sf::Vector2f& point) //���� ��ġ�� �Ű������� �޾Ƽ�
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f); //�����ϰ� ���� ��踦 �������ְ�

	return rect.contains(point); //��ǥ �ȿ� ������ true, ������ false ����
}

sf::Vector2f SceneGame::ClampByTileMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds(); //Ÿ�ϸ��� ������ �ӽð�ü�� ����
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f); //���κ��� �� ũ��� resize
	return Utils::Clamp(point, rect);
}

void SceneGame::Init()
{
	spawners.push_back(new ZombieSpawner());
	spawners.push_back(new ZombieSpawner());

	for (auto s : spawners)
	{
		s->SetPosition(Utils::RandomOnUnitCircle() * 250.f);
		AddGo(s);
	}

	player = new Player("Player");
	AddGo(player);

	//tileMap�� 2������ ����� �ȿ������� �ſ���
	tileMap = new TileMap("Background");
	tileMap->sortLayer = -1; //���̾� ������ player���� �۰� ��Ƽ� �ڿ��� AddGo�ص� �ؿ��� �̹��� ��µ�
	AddGo(tileMap);

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
	FindGoAll("Zombie", zombieList, Layers::World);

	Scene::Update(dt);

	worldView.setCenter(player->GetPosition()); //�� �߽����� �÷��̾� �������� (�÷��̾ �׻� ��� ��)
	
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
		if (tileMap->sortLayer == 1)
		{
			tileMap->sortLayer = -1;
		}
		else
		{
			tileMap->sortLayer = 1;
		}
		ResortGo(tileMap);
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
