#pragma once
#include "SpriteGo.h"

class SpriteGoEffect : public SpriteGo
{
protected:
	float duration = 3.f;
	float timer = 0.f;

public:
	SpriteGoEffect(const std::string& name = "");
	~SpriteGoEffect() override = default;

	void SetDuration(float d) { duration = d; }

	void Reset() override;
	void Update(float dt) override;

};