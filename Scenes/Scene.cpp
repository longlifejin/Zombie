#include "pch.h"
#include "Scene.h"

Scene::Scene(SceneIds id) :
	id(id),
	texResMgr(RES_MGR_TEXTURE),
	fontResMgr(RES_MGR_FONT),
	soundResMgr(RES_MGR_SOUND_BUFFER)
{
}

sf::Vector2f Scene::ScreenToWorld(sf::Vector2i screenPos)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, worldView);
}

sf::Vector2i Scene::WorldToScreen(sf::Vector2f worldPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(worldPos, worldView);
}

sf::Vector2f Scene::ScreenToUi(sf::Vector2i screenPos)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, uiView);
}

sf::Vector2i Scene::UiToScreen(sf::Vector2f uiPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(uiPos, uiView);
}

void Scene::Init()
{
	//게임오브젝트 init호출하도록
	for (auto obj : gameObjects)
	{
		obj->Init();
	}

	for (auto obj : uiGameObjects)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	for (auto obj : gameObjects)
	{
		delete obj;
	}
	gameObjects.clear();

	for (auto obj : uiGameObjects)
	{
		delete obj;
	}
	uiGameObjects.clear();
}

void Scene::Enter()
{
	for (auto obj : gameObjects)
	{
		obj->Reset();
	}
	for (auto obj : uiGameObjects)
	{
		obj->Reset();
	}
}

void Scene::Update(float dt)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}

	for (auto obj : uiGameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}
}

void Scene::LateUpdate(float dt)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->LateUpdate(dt);
		}
	}

	for (auto obj : uiGameObjects)
	{
		if (obj->GetActive())
		{
			obj->LateUpdate(dt);
		}
	}

	for (auto obj : resortingGameObjects)
	{
		auto it = std::find(gameObjects.begin(), gameObjects.end(), obj);
		if (it != gameObjects.end()) //찾은 경우
		{
			gameObjects.remove(obj);
			AddGo(obj, Layers::World);
			continue;
		}

		it = std::find(uiGameObjects.begin(), uiGameObjects.end(), obj);
		if (it != uiGameObjects.end()) //찾은 경우
		{
			uiGameObjects.remove(obj);
			AddGo(obj, Layers::Ui);
			continue;
		}
	}
	resortingGameObjects.clear(); //

	for (auto obj : removeGameObjects)
	{
		gameObjects.remove(obj);
		uiGameObjects.remove(obj);

		delete obj;
	}
	removeGameObjects.clear(); //다 지우고 목록 비우기 (다시 delete하는 현상 방지)
}

void Scene::FixedUpdate(float dt)
{
	


	for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->FixedUpdate(dt);
		}
	}

	for (auto obj : uiGameObjects)
	{
		if (obj->GetActive())
		{
			obj->FixedUpdate(dt);
		}
	}

}

void Scene::Draw(sf::RenderWindow& window)
{ 
	//정렬하고싶은 컨테이너 구간을 넘김
	//gameObjects.sort([](auto a, auto b) {
	//		if (a->sortLayer != b->sortLayer)
	//		{
	//			return a->sortLayer < b->sortLayer;
	//		}
	//		return a->sortOrder < b->sortOrder;
	//	}); //람다식 : 함수 자체를 식으로 구현하는 것

	//uiGameObjects.sort([](auto a, auto b) {
	//	if (a->sortLayer != b->sortLayer)
	//	{
	//		return a->sortLayer < b->sortLayer;
	//	}
	//	return a->sortOrder < b->sortOrder;
	//	});

	const sf::View& saveView = window.getView();

	window.setView(worldView);
	for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}

	window.setView(uiView);
	for (auto obj : uiGameObjects)
	{
		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}

	window.setView(saveView);
}

GameObject* Scene::FindGo(const std::string& name, Layers layer)
{
	//게임 컨테이너가 2종류, find할 이름을 매개변수 통해서 정하게 됨
	if ((layer & Layers::World) == Layers::World)
	{
		for (auto obj : gameObjects)
		{
			if (obj->name == name)
			{
				return obj;
			}
		}
	}

	if ((layer & Layers::Ui) == Layers::Ui)
	{
		for (auto obj : uiGameObjects)
		{
			if (obj->name == name)
			{
				return obj;
			}
		}
	}
	return nullptr;
}

int Scene::FindGoAll(const std::string& name, std::list<GameObject*>& list, Layers layer)
{
	list.clear();

	if ((layer & Layers::World) == Layers::World)
	{
		for (auto obj : gameObjects)
		{
			if (obj->name == name)
			{
				list.push_back(obj);
			}
		}
	}

	if ((layer & Layers::Ui) == Layers::Ui)
	{
		for (auto obj : uiGameObjects)
		{
			if (obj->name == name)
			{
				list.push_back(obj);
			}
		}

	}
	return list.size();
}

GameObject* Scene::AddGo(GameObject* obj, Layers layer)
{
	if (layer == Layers::World)
	{
		//순회하면서 들어갈 자리 잡아주기
		if (std::find(gameObjects.begin(), gameObjects.end(), obj) == gameObjects.end())
		{
			if (gameObjects.empty()) //비어있으면 그냥 바로 넣어주기
			{
				gameObjects.push_back(obj);
				return obj;
			}

			//비어있지 않으면 위치 잡아주기
			auto it = gameObjects.begin();
			while (it != gameObjects.end()) //gameObjects 리스트의 처음부터 끝까지 순회
			{
				if (GameObject::CompareDrawOrder(obj, *it))
				{
					gameObjects.insert(it, obj); //it자리에 obj가 삽입됨
					return obj;
				}
				++it;
			}
			//list안에 모든 obj와 비교했을 때 제일 layer와 order가 큰 경우에는
			gameObjects.push_back(obj); //마지막에 들어가게 됨
			return obj;
		}
	}

	if (layer == Layers::Ui)
	{
		if (std::find(uiGameObjects.begin(), uiGameObjects.end(), obj) == uiGameObjects.end())
		{
			if (uiGameObjects.empty()) //비어있으면 그냥 바로 넣어주기
			{
				uiGameObjects.push_back(obj);
				return obj;
			}

			//비어있지 않으면 위치 잡아주기
			auto it = uiGameObjects.begin();
			while (it != uiGameObjects.end())
			{
				if (GameObject::CompareDrawOrder(obj, *it))
				{
					uiGameObjects.insert(it, obj); //it자리에 obj가 삽입됨
					return obj;
				}
				++it;
			}
			uiGameObjects.push_back(obj); //마지막에 들어가는 경우
			return obj;
		}
	}
	return nullptr;
}

void Scene::ResortGo(GameObject* obj)
{
	//중복되는거 방지
	if (std::find(resortingGameObjects.begin(), resortingGameObjects.end(), obj) == resortingGameObjects.end())
	{
		resortingGameObjects.push_back(obj);
	}
}

void Scene::RemoveGo(GameObject* obj)
{
	//obj->SetActive(false);
	if (std::find(removeGameObjects.begin(), removeGameObjects.end(), obj) == removeGameObjects.end())
	{
		removeGameObjects.push_back(obj);
	}
}
