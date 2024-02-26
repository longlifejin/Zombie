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

bool SceneGame::isInTileMap(const sf::Vector2f& point) //현재 위치를 매개변수로 받아서
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f); //존재하게 만들 경계를 지정해주고

	return rect.contains(point); //좌표 안에 있으면 true, 없으면 false 리턴
}

sf::Vector2f SceneGame::ClampByTileMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds(); //타일맵의 범위를 임시객체로 만들어서
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f); //경계부분을 뺀 크기로 resize
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

	//tileMap이 2개여서 제대로 안움직였던 거였음
	tileMap = new TileMap("Background");
	tileMap->sortLayer = -1; //레이어 순서를 player보다 작게 잡아서 뒤에서 AddGo해도 밑에서 이미지 출력됨
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
	Scene::Release(); //부모 클래스 함수 호출
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

	worldView.setCenter(player->GetPosition()); //뷰 중심점을 플레이어 기준으로 (플레이어가 항상 가운데 옴)
	
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
