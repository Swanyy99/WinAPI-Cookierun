#include "framework.h"
#include "CSoundManager.h"

#include "CSound.h"

CSoundManager::CSoundManager()
{
	m_pSystem = nullptr;
}

CSoundManager::~CSoundManager()
{
}

System* CSoundManager::GetSystem()
{
	return m_pSystem;
}

void CSoundManager::Play(CSound* pSound, float volume, bool loop)
{
	FMOD_RESULT result;

	FMOD_MODE mode;
	result = pSound->m_pSound->getMode(&mode);
	assert(FMOD_OK == result && L"Get mode failed");

	if (mode & FMOD_LOOP_NORMAL && (pSound->IsPlaying() || pSound->IsPaused()))
	{
		result = pSound->m_pChannel->stop();
		assert(FMOD_OK == result && L"Stop sound failed");
	}

	if (loop)
		result = pSound->m_pSound->setMode(FMOD_LOOP_NORMAL);
	else
		result = pSound->m_pSound->setMode(FMOD_LOOP_OFF);

	assert(FMOD_OK == result && L"Set Loop failed");

	result = m_pSystem->playSound(pSound->m_pSound, nullptr, false, &(pSound->m_pChannel));
	assert(FMOD_OK == result && L"Play sound failed");

	result = pSound->m_pChannel->setVolume(volume);
	assert(FMOD_OK == result && L"Set volume failed");
}

void CSoundManager::Stop(CSound* pSound)
{
	if (!pSound->IsPlaying())
		return;

	FMOD_RESULT result = pSound->m_pChannel->stop();
	assert(FMOD_OK == result && L"Stop sound failed");
}

void CSoundManager::Pause(CSound* pSound)
{
	if (pSound->IsPaused())
		return;

	FMOD_RESULT result = pSound->m_pChannel->setPaused(true);
	assert(FMOD_OK == result && L"SetPaused failed");
}

void CSoundManager::Resume(CSound* pSound)
{
	if (!pSound->IsPaused())
		return;

	FMOD_RESULT result = pSound->m_pChannel->setPaused(false);
	assert(FMOD_OK == result && L"Resume failed");
}

void CSoundManager::Init()
{
	// 사운드 시스템 생성
	FMOD_RESULT result;
	result = System_Create(&m_pSystem);
	assert(FMOD_OK == result && L"Create sound system falied");

	result = m_pSystem->init(32, FMOD_INIT_NORMAL, nullptr);
	assert(FMOD_OK == result && L"Init sound system falied");
}

void CSoundManager::Update()
{
	FMOD_RESULT result = m_pSystem->update();
	assert(FMOD_OK == result && L"Update sound system falied");
}

void CSoundManager::Release()
{
	if (nullptr != m_pSystem)
	{
		m_pSystem->release();
		m_pSystem->close();
	}
}
