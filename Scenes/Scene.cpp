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
	//���ӿ�����Ʈ initȣ���ϵ���
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
		if (it != gameObjects.end()) //ã�� ���
		{
			gameObjects.remove(obj);
			AddGo(obj, Layers::World);
			continue;
		}

		it = std::find(uiGameObjects.begin(), uiGameObjects.end(), obj);
		if (it != uiGameObjects.end()) //ã�� ���
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
	removeGameObjects.clear(); //�� ����� ��� ���� (�ٽ� delete�ϴ� ���� ����)
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
	//�����ϰ���� �����̳� ������ �ѱ�
	//gameObjects.sort([](auto a, auto b) {
	//		if (a->sortLayer != b->sortLayer)
	//		{
	//			return a->sortLayer < b->sortLayer;
	//		}
	//		return a->sortOrder < b->sortOrder;
	//	}); //���ٽ� : �Լ� ��ü�� ������ �����ϴ� ��

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
	//���� �����̳ʰ� 2����, find�� �̸��� �Ű����� ���ؼ� ���ϰ� ��
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
		//��ȸ�ϸ鼭 �� �ڸ� ����ֱ�
		if (std::find(gameObjects.begin(), gameObjects.end(), obj) == gameObjects.end())
		{
			if (gameObjects.empty()) //��������� �׳� �ٷ� �־��ֱ�
			{
				gameObjects.push_back(obj);
				return obj;
			}

			//������� ������ ��ġ ����ֱ�
			auto it = gameObjects.begin();
			while (it != gameObjects.end()) //gameObjects ����Ʈ�� ó������ ������ ��ȸ
			{
				if (GameObject::CompareDrawOrder(obj, *it))
				{
					gameObjects.insert(it, obj); //it�ڸ��� obj�� ���Ե�
					return obj;
				}
				++it;
			}
			//list�ȿ� ��� obj�� ������ �� ���� layer�� order�� ū ��쿡��
			gameObjects.push_back(obj); //�������� ���� ��
			return obj;
		}
	}

	if (layer == Layers::Ui)
	{
		if (std::find(uiGameObjects.begin(), uiGameObjects.end(), obj) == uiGameObjects.end())
		{
			if (uiGameObjects.empty()) //��������� �׳� �ٷ� �־��ֱ�
			{
				uiGameObjects.push_back(obj);
				return obj;
			}

			//������� ������ ��ġ ����ֱ�
			auto it = uiGameObjects.begin();
			while (it != uiGameObjects.end())
			{
				if (GameObject::CompareDrawOrder(obj, *it))
				{
					uiGameObjects.insert(it, obj); //it�ڸ��� obj�� ���Ե�
					return obj;
				}
				++it;
			}
			uiGameObjects.push_back(obj); //�������� ���� ���
			return obj;
		}
	}
	return nullptr;
}

void Scene::ResortGo(GameObject* obj)
{
	//�ߺ��Ǵ°� ����
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
