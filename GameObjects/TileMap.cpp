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

	va.clear(); //정점 배열이 들고 있는 vertex 배열을 클리어
	va.setPrimitiveType(sf::Quads);
	va.resize(count.x * count.y * 4); //실제 버텍스 배열의 사이즈를 정해줌 (사각형이니까 *4)
	
	sf::Vector2f posOffsets[4] = {
		{ 0, 0 },
		{ size.x, 0 },
		{ size.x, size.y },
		{ 0, size.y },
	};

	//sheet.png에서 사용하고 싶은 부분을 지정해준 것
	sf::Vector2f texCoord0[4] = {
		{ 0, 0 },
		{ 50.f, 0 },
		{ 50.f, 50.f },
		{ 0, 50.f },
	};

	for (int i = 0; i < count.y; ++i) //행마다 돌아가는 for문
	{
		for (int j = 0; j < count.x; ++j) //열
		{
			int texIndex = Utils::RandomRange(0, 3);
			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
			{ //외곽인 경우 정해진 타일 쓰려고
				texIndex = 3; 
			}

			int quadIndex = i * count.x + j; //1차원 배열 형태로 변환
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
	transform = sf::Transform::Identity; //기본값 주는 변환
	//호출하는 순서에 따라 결과가 달라지므로 초기화를 시켜주고 한다.
	
	float scaleX = isFlipX ? -scale.x : scale.x;
	float scaleY = isFlipX ? -scale.y : scale.y;
	transform.scale(scaleX, scaleY, position.x , position.y); //뒤에 중점(position.x, position.y)을 적어준 것
	transform.rotate(rotation, position.x, position.y); //얘도 중점 적어준 것
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
