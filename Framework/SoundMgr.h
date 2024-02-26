#pragma once
#include "Singleton.h"

//bgm 재생, 효과음 재생하는 역할
class SoundMgr : public Singleton<SoundMgr>
{
	friend Singleton<SoundMgr>;

private:
	SoundMgr();
	virtual ~SoundMgr();

	sf::Sound bgm[2];
	int frontBgmIndex = 0; //재생하는 사운드 인덱스 번호
	
	bool isFading = false;
	float crossFadeDuration = 1.f;
	float crossFadeTimer = 0.f; 
	//bgm 재생 끌 애는 순차적으로 볼륨 감소되게

	std::list<sf::Sound*> playing; //재생중인 사운드 객체
	std::list<sf::Sound*> waiting; //재생중이지 않은 사운드 객체

	float sfxVolume = 100.f;
	float bgmVolume = 100.f;

public:

	void SetSfxVolume(float v) { sfxVolume = v; }
	void SetBgmVolume(float v) { bgmVolume = v; }

	void Init(int totalChannels = 1); // 동시에 재생할 사운드 갯수 제한
	void Release();
	void Update(float dt);
	
	void PlayBgm(std::string id, bool crossFade = true);
	void StopBgm();

	void PlaySfx(std::string id, bool loop = false); //loop재생 할지 말지도 넘김
	void PlaySfx(sf::SoundBuffer& buffer, bool loop = false);

	void StopAllSfx();

};

#define SOUND_MGR (Singleton<SoundMgr>::Instance())
