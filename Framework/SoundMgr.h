#pragma once
#include "Singleton.h"

//bgm ���, ȿ���� ����ϴ� ����
class SoundMgr : public Singleton<SoundMgr>
{
	friend Singleton<SoundMgr>;

private:
	SoundMgr();
	virtual ~SoundMgr();

	sf::Sound bgm[2];
	int frontBgmIndex = 0; //����ϴ� ���� �ε��� ��ȣ
	
	bool isFading = false;
	float crossFadeDuration = 1.f;
	float crossFadeTimer = 0.f; 
	//bgm ��� �� �ִ� ���������� ���� ���ҵǰ�

	std::list<sf::Sound*> playing; //������� ���� ��ü
	std::list<sf::Sound*> waiting; //��������� ���� ���� ��ü

	float sfxVolume = 100.f;
	float bgmVolume = 100.f;

public:

	void SetSfxVolume(float v) { sfxVolume = v; }
	void SetBgmVolume(float v) { bgmVolume = v; }

	void Init(int totalChannels = 1); // ���ÿ� ����� ���� ���� ����
	void Release();
	void Update(float dt);
	
	void PlayBgm(std::string id, bool crossFade = true);
	void StopBgm();

	void PlaySfx(std::string id, bool loop = false); //loop��� ���� ������ �ѱ�
	void PlaySfx(sf::SoundBuffer& buffer, bool loop = false);

	void StopAllSfx();

};

#define SOUND_MGR (Singleton<SoundMgr>::Instance())
