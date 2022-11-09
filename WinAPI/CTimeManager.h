#pragma once

class CCore;

class CTimeManager : public SingleTon<CTimeManager>
{
	friend SingleTon<CTimeManager>;
	friend CCore;
private:
	CTimeManager();
	virtual ~CTimeManager();

	UINT	m_uiFPS;	// FPS : �ֻ���(������), 1�ʴ� �׷��� ȭ�� ��
	float	m_fDT;		// Delta Time : �����ð�, 1�����Ӵ� �ҿ�� �ð�
	float	m_fAbsDT;	// Absolute Delta Time : �����ð�, 1�����Ӵ� �ҿ�� �ð� (���� �ð��̹Ƿ�, DT�� �ٲ��� �ʾƾ��ϴ� ������Ʈ�� �����)

	UINT	updateCount;
	float	updateOneSecond;
	chrono::high_resolution_clock::time_point prevTime;	// ������������ �ð�
	chrono::high_resolution_clock::time_point curTime;	// ������������ �ð�

	void Init();
	void Update();
	void Release();

public:
	UINT GetFPS();
	float GetDT();
	float GetAbsDT();
};

#define	TIME	CTimeManager::GetInstance()
#define FPS		CTimeManager::GetInstance()->GetFPS()
#define DT		CTimeManager::GetInstance()->GetDT()
#define ABSDT		CTimeManager::GetInstance()->GetAbsDT()

