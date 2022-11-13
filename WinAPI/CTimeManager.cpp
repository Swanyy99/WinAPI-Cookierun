#include "framework.h"
#include "CTimeManager.h"

extern bool pause;
extern bool isDead;
extern bool isDash;

CTimeManager::CTimeManager()
{
	m_uiFPS = 1;
	m_fDT = 1;
	m_fAbsDT = 1;
	updateCount = 0;
	updateOneSecond = 0;

	prevTime = {};
	curTime = {};
}

CTimeManager::~CTimeManager()
{
}

void CTimeManager::Init()
{
	prevTime = chrono::high_resolution_clock::now();
}

void CTimeManager::Update()
{
	// ���������ӿ��� ���������ӱ��� �ɸ� �ð��� ����
	// �����ð� = ���������ӽð� - ���������ӽð�
	curTime = chrono::high_resolution_clock::now();
	chrono::duration<float> elapsed = curTime - prevTime;

	if (pause == false && isDead == false && isDash == false)
	{
		m_fDT = elapsed.count();
		m_fAbsDT = elapsed.count();
	}

	if (isDash == true && pause == false && isDead == false)
	{
		m_fDT = elapsed.count() * 3;
		m_fAbsDT = elapsed.count();
	}
	

	if (pause == true)
	{
		m_fDT = 0;
		m_fAbsDT = 0;
	}

	if (isDead == true)
	{
		m_fDT = 0;
		m_fAbsDT = 0;
	}


	if (m_fDT > 0.1f) m_fDT = 0.1f;
	if (m_fAbsDT > 0.1f) m_fAbsDT = 0.1f;
	prevTime = curTime;

	// 1�ʰ� �ɸ������� �ݺ��� Ƚ���� �ʴ������Ӽ�
	updateCount++;
	updateOneSecond += m_fAbsDT;
	if (updateOneSecond >= 1.0)
	{
		m_uiFPS = updateCount;
		updateOneSecond = 0;
		updateCount = 0;
	}
}

void CTimeManager::Release()
{
}

UINT CTimeManager::GetFPS()
{
	return m_uiFPS;
}

float CTimeManager::GetDT()
{
	return m_fDT;
}

float CTimeManager::GetAbsDT()
{
	return m_fAbsDT;
}