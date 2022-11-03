#include "framework.h"
#include "CSound.h"

#include "CSoundManager.h"

CSound::CSound()
{
	m_pSound = nullptr;
	m_pChannel = nullptr;
}

CSound::~CSound()
{
	if (nullptr != m_pSound)
	{
		m_pSound->release();
	}
}

bool CSound::IsPlaying()
{
	if (nullptr == m_pChannel)
		return false;

	bool playing = false;
	FMOD_RESULT result = m_pChannel->isPlaying(&playing);
	if (FMOD_ERR_INVALID_HANDLE == result)
		return false;
	assert(FMOD_OK == result && L"Channel isPlaying failed");
	return playing;
}

bool CSound::IsPaused()
{
	if (nullptr == m_pChannel)
		return false;

	bool paused = false;
	FMOD_RESULT result = m_pChannel->getPaused(&paused);
	if (FMOD_ERR_INVALID_HANDLE == result)
		return false;
	assert(FMOD_OK == result && L"Channel getPaused failed");
	return paused;
}

void CSound::Load(const wstring& soundName)
{
	char str[255];
	wcstombs_s(nullptr, str, soundName.c_str(), 255);

	FMOD_RESULT result = SOUND->GetSystem()->createSound(str, FMOD_LOOP_OFF, 0, &m_pSound);
	assert(FMOD_OK == result && L"System createSound failed");
}
