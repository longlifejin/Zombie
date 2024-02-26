#include "pch.h"
#include "UiHud.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::SetResolution(const sf::Vector2f resolution)
{
}

void UiHud::SetScore(int s)
{
	textScore.SetString(formatScore + std::to_string(s));
}

void UiHud::SetHiScore(int s)
{
	textHiScore.SetString(formatHighScore + std::to_string(s));

}

void UiHud::SetAmmo(int current, int total) //재장전시 호출하기
{
	textAmmo.SetString(std::to_string(current) + "/" + std::to_string(total - current));
}

void UiHud::SetHp(int hp, int max)
{
	float value = (float)hp / max;
	gaugeHp.setSize({ gaugeHpSize.x * value, gaugeHpSize.y });

	if (hp <= 0)
	{
		gaugeHp.setSize({ 0, gaugeHpSize.y });
	}
}

void UiHud::SetWave(int w)
{
	textWave.SetString(formatWave + std::to_string(w));

}

void UiHud::SetZombieCount(int count)
{
	textZombieCount.SetString(formatZombieCount + std::to_string(count));
}

int UiHud::AddScore(int addscore)
{
	return score += addscore;
}

int UiHud::AddHiScore(int addHiScore)
{
	return hiScore += addHiScore;
}

void UiHud::Init()
{
	textScore.Init();
	textHiScore.Init();
	imgAmmoIcon.Init();
	textAmmo.Init();
	textWave.Init();
	textZombieCount.Init();

	float textSize = 50.f;
	sf::Font& font = RES_MGR_FONT.Get("fonts/zombiecontrol.ttf");
	textScore.Set(font, "", textSize, sf::Color::White);
	textHiScore.Set(font, "", textSize, sf::Color::White);
	textAmmo.Set(font, "", textSize, sf::Color::White);
	textWave.Set(font, "", textSize, sf::Color::White);
	textZombieCount.Set(font, "", textSize, sf::Color::White);
	imgAmmoIcon.SetTexture("graphics/ammo_icon.png");
	gaugeHp.setFillColor(sf::Color::Red);
	gaugeHp.setSize(gaugeHpSize);

	textScore.SetOrigin(Origins::TL);
	textHiScore.SetOrigin(Origins::TR);
	imgAmmoIcon.SetOrigin(Origins::BL);
	textAmmo.SetOrigin(Origins::BL);
	textWave.SetOrigin(Origins::BL);

	gaugeHp.setSize(gaugeHpSize);
	Utils::SetOrigin(gaugeHp, Origins::BL);
	textWave.SetOrigin(Origins::BR);
	textZombieCount.SetOrigin(Origins::BR);

	//Top
	float topY = 150.f;
	textScore.SetPosition({ 150.f, topY });
	textHiScore.SetPosition({ referenceResolution.x - 150.f, topY });

	//Bottom
	float bottomY = referenceResolution.y - 100.f;
	imgAmmoIcon.SetPosition({ 150.f, bottomY });
	textAmmo.SetPosition({ 400.f, bottomY });
	gaugeHp.setPosition({ 800.f, bottomY });
	textWave.SetPosition({ referenceResolution.x - 400.f, bottomY });
	textZombieCount.SetPosition({ referenceResolution.x - 150.f, bottomY });
}

void UiHud::Release()
{
	GameObject::Release();
}

void UiHud::Reset()
{
	GameObject::Reset();

	textScore.Reset();
	textHiScore.Reset();
	imgAmmoIcon.Reset();
	textAmmo.Reset();
	textWave.Reset();
	textZombieCount.Reset();
}

void UiHud::Update(float dt)
{
	GameObject::Update(dt);
	textScore.Update(dt);
	textHiScore.Update(dt);
	imgAmmoIcon.Update(dt);
	
	textAmmo.Update(dt);
	textWave.Update(dt);
	textZombieCount.Update(dt);
}

void UiHud::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);
}

void UiHud::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);

	textScore.Draw(window);
	textHiScore.Draw(window);
	imgAmmoIcon.Draw(window);
	window.draw(gaugeHp); //drawable상속받은 도형이니까 이렇게 사용
	textAmmo.Draw(window);
	textWave.Draw(window);
	textZombieCount.Draw(window);
}
