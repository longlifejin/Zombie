#include "pch.h"
#include "ItemSpawner.h"
#include "SceneGame.h"
#include "Item.h"

ItemSpawner::ItemSpawner(const std::string& name)
	:Spawner(name)
{
}

GameObject* ItemSpawner::Create()
{
	Item::Types itemType = itemTypes[Utils::RandomRange(0, itemTypes.size())];
	//itemtype에 따라서 value값 주게 switch문 추가하기

	return Item::Create(itemType, 5);
}

void ItemSpawner::Reset()
{
	Spawner::Reset();

	itemTypes.clear();
	itemTypes.push_back(Item::Types::Ammo);
	itemTypes.push_back(Item::Types::Health);
}