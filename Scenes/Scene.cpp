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

void Scene::Draw(sf::RenderWindow& window)
{
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
		if (std::find(gameObjects.begin(), gameObjects.end(), obj) == gameObjects.end())
		{
			gameObjects.push_back(obj);
			return obj;
		}

	}

	if (layer == Layers::Ui)
	{
		if (std::find(uiGameObjects.begin(), uiGameObjects.end(), obj) == uiGameObjects.end())
		{
			uiGameObjects.push_back(obj);
			return obj;
		}
	}
	return nullptr;
}

void Scene::RemoveGo(GameObject* obj)
{
	gameObjects.remove(obj); //없으면 아무것도 안해서 조건문 안 넣음
	uiGameObjects.remove(obj);
}
