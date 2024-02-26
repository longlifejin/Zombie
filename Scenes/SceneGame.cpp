#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "ItemSpawner.h"
#include "UiHud.h"

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
	spawners.push_back(new ItemSpawner());
	
	for (auto s : spawners)
	{
		s->SetPosition(Utils::RandomOnUnitCircle() * 250.f);
		AddGo(s);
	}

	/*for (auto item : itemSpawners)
	{
		item->SetPosition(Utils::RandomOnUnitCircle() * 250.f);
		AddGo(item);
	}*/

	player = new Player("Player");
	AddGo(player);

	//tileMap�� 2������ ����� �ȿ������� �ſ���
	tileMap = new TileMap("Background");
	tileMap->sortLayer = -1; //���̾� ������ player���� �۰� ��Ƽ� �ڿ��� AddGo�ص� �ؿ��� �̹��� ��µ�
	tileMap->sortOrder = 0;
	AddGo(tileMap);

	crosshair = new SpriteGo("crosshair");
	crosshair->SetTexture("graphics/crosshair.png");
	crosshair->sortLayer = -1;
	crosshair->SetOrigin(Origins::MC);
	AddGo(crosshair, Scene::Layers::Ui);

	uiHud = new UiHud();
	AddGo(uiHud, Layers::Ui);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release(); //�θ� Ŭ���� �Լ� ȣ��
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	Scene::Enter();

	uiHud->SetScore(0);
	uiHud->SetHiScore(0);
	uiHud->SetAmmo(0,10);
	uiHud->SetWave(1);
	uiHud->SetZombieCount(0);
	
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
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);

	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	FindGoAll("Zombie", zombieList, Layers::World);
	FindGoAll("item", itemList, Layers::World);

	Scene::Update(dt);

	crosshair->SetPosition(ScreenToUi((sf::Vector2i)(InputMgr::GetMousePos())));

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

void SceneGame::FixedUpdate(float dt)
{
	FindGoAll("Zombie", zombieList, Layers::World);
	Scene::FixedUpdate(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
