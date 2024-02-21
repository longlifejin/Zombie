#include "pch.h"
#include "Player.h"

Player::Player(const std::string& name)
	:SpriteGo(name)
{
}

void Player::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/player.png");
	SetOrigin(Origins::MC);
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	look = mouseWorldPos - position;
	Utils::Normalize(look); //look vector 갱신

	//마우스 포인터 맞춰서 회전//
	SetRotation(Utils::Angle(look));
	/*float angle = Utils::Angle(look);
	sprite.setRotation(angle); */

	// 키입력 받아서 움직이게 하기
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	//대각선 이동할 때 속도 높아지는 걸 막기 위해서 씀
	if (Utils::Magnitude(direction) > 1.f) 
	{
		Utils::Normalize(direction);
	}

	Translate(direction * speed * dt);
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
