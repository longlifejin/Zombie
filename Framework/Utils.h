#pragma once

class Utils
{
public:
	static float Clamp(float v, float min, float max);

	//�簢�� �ȿ� position �������� �߶��ִ� ����
	static sf::Vector2f Clamp(const sf::Vector2f& v, const sf::FloatRect& rect);

	//���� �����ϴ� ����, delta = ��ȭ��
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
	static float SqrMagnitude(const sf::Vector2f& vec); // ������ ������ ����
	static float Magnitude(const sf::Vector2f& vec); // ������ ����
	static void Normalize(sf::Vector2f& vec); //������ ���̸� 1�� �ٲ� ����
	static sf::Vector2f GetNormal(const sf::Vector2f& vec);
	static float Distance(const sf::Vector2f& p1, const sf::Vector2f& p2); //�������� �޾Ƽ� �� ���� �Ÿ� ��ȯ

	static float RadianToDegree(float radian); //2���� = 360��
	static float DegreeToRadian(float degree);
	static float Angle(const sf::Vector2f& vec); //���� ����

};