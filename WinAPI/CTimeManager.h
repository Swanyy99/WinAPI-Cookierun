#pragma once

class CCore;

class CTimeManager : public SingleTon<CTimeManager>
{
	friend SingleTon<CTimeManager>;
	friend CCore;
private:
	CTimeManager();
	virtual ~CTimeManager();

	UINT	m_uiFPS;	// FPS : 주사율(프레임), 1초당 그려진 화면 수
	float	m_fDT;		// Delta Time : 단위시간, 1프레임당 소요된 시간

	UINT	updateCount;
	float	updateOneSecond;
	chrono::high_resolution_clock::time_point prevTime;	// 이전프레임의 시간
	chrono::high_resolution_clock::time_point curTime;	// 현재프레임의 시간

	void Init();
	void Update();
	void Release();

public:
	UINT GetFPS();
	float GetDT();
};

#define	TIME	CTimeManager::GetInstance()
#define FPS		CTimeManager::GetInstance()->GetFPS()
#define DT		CTimeManager::GetInstance()->GetDT()

