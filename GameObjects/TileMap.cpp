#include "pch.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
	: GameObject(name)
{
}

sf::FloatRect TileMap::GetLocalBounds()
{
	sf::FloatRect bounds = va.getBounds();
	bounds.left = origin.x;
	bounds.top = origin.y;
	return bounds;
}

sf::FloatRect TileMap::GetGlobalBounds()
{
	sf::FloatRect bounds = va.getBounds();
	return transform.transformRect(bounds);
}

void TileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
{
	cellCount = count;
	cellSize = size;

	va.clear(); //���� �迭�� ��� �ִ� vertex �迭�� Ŭ����
	va.setPrimitiveType(sf::Quads);
	va.resize(count.x * count.y * 4); //���� ���ؽ� �迭�� ����� ������ (�簢���̴ϱ� *4)
	
	sf::Vector2f posOffsets[4] = {
		{ 0, 0 },
		{ size.x, 0 },
		{ size.x, size.y },
		{ 0, size.y },
	};

	//sheet.png���� ����ϰ� ���� �κ��� �������� ��
	sf::Vector2f texCoord0[4] = {
		{ 0, 0 },
		{ 50.f, 0 },
		{ 50.f, 50.f },
		{ 0, 50.f },
	};

	for (int i = 0; i < count.y; ++i) //�ึ�� ���ư��� for��
	{
		for (int j = 0; j < count.x; ++j) //��
		{
			int texIndex = Utils::RandomRange(0, 3);
			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
			{ //�ܰ��� ��� ������ Ÿ�� ������
				texIndex = 3; 
			}

			int quadIndex = i * count.x + j; //1���� �迭 ���·� ��ȯ
			sf::Vector2f quadPos(size.x * j, size.y * i);

			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = (quadIndex * 4) + k;
				va[vertexIndex].position = quadPos + posOffsets[k];
				va[vertexIndex].texCoords = texCoord0[k];
				va[vertexIndex].texCoords.y += texIndex * 50.f;
			}
		}
	}
}

void TileMap::SetSpriteSheetId(const std::string& id)
{
	spriteSheetId = id;
	texture = &RES_MGR_TEXTURE.Get(spriteSheetId);
}

void TileMap::UpdateTransform()
{
	transform = sf::Transform::Identity; //�⺻�� �ִ� ��ȯ
	//ȣ���ϴ� ������ ���� ����� �޶����Ƿ� �ʱ�ȭ�� �����ְ� �Ѵ�.
	
	float scaleX = isFlipX ? -scale.x : scale.x;
	float scaleY = isFlipX ? -scale.y : scale.y;
	transform.scale(scaleX, scaleY, position.x , position.y); //�ڿ� ����(position.x, position.y)�� ������ ��
	transform.rotate(rotation, position.x, position.y); //�굵 ���� ������ ��
	transform.translate(position-origin);
}

void TileMap::SetOrigin(Origins preset)
{
	if (preset == Origins::Custom)
		return;

	originPreset = preset;
	sf::FloatRect bound = va.getBounds();
	origin.x = bound.width * ((int)originPreset % 3) * 0.5f;
	origin.y = bound.height * ((int)originPreset / 3) * 0.5f;
	UpdateTransform();

}

void TileMap::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	UpdateTransform();
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	UpdateTransform();
}


void TileMap::Translate(const sf::Vector2f& delta)
{
	GameObject::Translate(delta);
	UpdateTransform();
}

void TileMap::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	UpdateTransform();
}

void TileMap::SetRotation(float r)
{
	GameObject::SetRotation(r);
	UpdateTransform();
}

void TileMap::SetFlipX(bool flip)
{
	GameObject::SetFlipX(flip);
	UpdateTransform();
}


void TileMap::SetFlipY(bool flip)
{
	GameObject::SetFlipY(flip);
	UpdateTransform();
}

void TileMap::Init()
{
	GameObject::Init();
	SetSpriteSheetId("graphics/background_sheet.png");
	Set({ 10, 10 }, { 50.f, 50.f });
	//SetOrigin(Origins::MC);
}

void TileMap::Release()
{
	GameObject::Release();
}

void TileMap::Reset()
{
	GameObject::Reset();

	
}

void TileMap::Update(float dt)
{
	GameObject::Update(dt);

}

void TileMap::Draw(sf::RenderWindow& window)
{
	//GameObject::Draw(window);
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform;

	window.draw(va, state);

}
