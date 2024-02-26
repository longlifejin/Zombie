#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"

class UiHud : public GameObject
{
protected:
	std::string formatScore = "SCORE:";
	std::string formatHighScore = "HIGH SCORE:";
	std::string formatAmmo = "{0}/{1}";
	std::string formatWave = "WAVE:";
	std::string formatZombieCount = "ZOMBIES:";

	TextGo textScore;
	TextGo textHiScore;

	int score = 0;
	int hiScore = 0;

	SpriteGo imgAmmoIcon;
	TextGo textAmmo;

	sf::RectangleShape gaugeHp;
	sf::Vector2f gaugeHpSize = { 300.f, 50.f };

	TextGo textWave;
	TextGo textZombieCount;
	
	sf::Vector2f referenceResolution = { 1920.f,1080.f }; //처음 Init()해서 배치할 때 
	sf::Vector2f resolution; // 변경할 값


public:
	UiHud(const std::string& name = "");
	~UiHud() override = default;

	void SetResolution(const sf::Vector2f resolution);

	void SetScore(int s);
	void SetHiScore(int s);

	void SetAmmo(int current, int total);
	void SetHp(int hp, int max);
	void SetWave(int w);
	void SetZombieCount(int count);

	int AddScore(int addScore);
	int AddHiScore(int addHiScore);
	int GetCurrentScore() { return score; }
	int GetHighestScore() { return hiScore; }



	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};