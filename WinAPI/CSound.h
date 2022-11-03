#pragma once
#include "CResource.h"

class CSoundManager;

class CSound : public CResource
{
	friend CSoundManager;
public:
	CSound();
	virtual ~CSound();

private:
	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;

public:
	bool IsPlaying();
	bool IsPaused();

	void Load(const wstring& soundName);
};