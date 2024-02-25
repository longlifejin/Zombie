#pragma once

class Utils
{
public:
	static float Clamp(float v, float min, float max);

	//사각형 안에 position 들어오도록 잘라주는 역할
	static sf::Vector2f Clamp(const sf::Vector2f& v, const sf::FloatRect& rect);

	//범위 수정하는 역할, delta = 변화량
	static sf::FloatRect ResizeRect(const sf::FloatRect& rect, const sf::Vector2f& delta);

	// Random
	static float RandomValue(); // 0.f ~ 1.f
	static float RandomRange(float min, float max);
	static sf::Vector2f RandomOnUnitCircle();
	static sf::Vector2f RandomInUnitCircle();
	static int RandomRange(int min, int maxExclude);


	// Origin
	static sf::Vector2f SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect);
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Text& obj, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Shape& obj, Origins originPreset);


	//Math
	static float SqrMagnitude(const sf::Vector2f& vec); // 벡터의 길이의 제곱
	static float Magnitude(const sf::Vector2f& vec); // 벡터의 길이
	static void Normalize(sf::Vector2f& vec); //벡터의 길이를 1로 바꾼 벡터
	static sf::Vector2f GetNormal(const sf::Vector2f& vec);
	static float Distance(const sf::Vector2f& p1, const sf::Vector2f& p2); //포지션을 받아서 둘 사이 거리 반환

	static float RadianToDegree(float radian); //2파이 = 360도
	static float DegreeToRadian(float degree);
	static float Angle(const sf::Vector2f& vec); //각도 리턴

};