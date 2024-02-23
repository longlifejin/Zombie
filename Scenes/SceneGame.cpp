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

bool SceneGame::isInTileMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);

	return rect.contains(point); //좌표 안에 있으면 true, 없으면 false 리턴
}

sf::Vector2f SceneGame::ClampByTileMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);
	return Utils::Clamp(point, rect);
}

void SceneGame::Init()
{
	//tileMap이 2개여서 제대로 안움직였던 거였음
	tileMap = new TileMap("Background");
	AddGo(tileMap);


	spawners.push_back(new ZombieSpawner());
	spawners.push_back(new ZombieSpawner());

	for (auto s : spawners)
	{
		s->SetPosition(Utils::RandomOnUnitCircle() * 250.f);
		AddGo(s);
	}

	player = new Player("Player");
	AddGo(player);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release(); //부모 클래스 함수 호출
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

	worldView.setCenter(player->GetPosition()); //플레이어가 계속 중앙에 오게
	
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
		tileMap->sortLayer = 1;
		ResortGo(tileMap);
	}

	//충돌한 좀비 객체 지우기
	//std::list<GameObject*> removeZombieobj; //지울 좀비 객체 담아두기
	//for (auto obj : gameObjects)
	//{
	//	Zombie* zombie = dynamic_cast<Zombie*>(obj);
	//	if (zombie != nullptr)
	//	{
	//		if (Utils::Distance(zombie->GetPosition(), player->GetPosition()) <= 10.f)
	//		{
	//			removeZombieobj.push_back(obj);
	//		}
	//	}
	//}

	//for(auto obj : removeZombieobj)
	//{
	//	gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), obj), gameObjects.end());
	//	delete obj;
	//}
}

void SceneGame::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
