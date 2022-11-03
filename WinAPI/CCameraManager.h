#pragma once

class CCore;
class CGameObject;

class CCameraManager : public SingleTon<CCameraManager>
{
	friend SingleTon<CCameraManager>;
	friend CCore;
private:
	CCameraManager();
	virtual ~CCameraManager();

private:
	Vector			m_vecLookAt;		// 카메라가 현재 보고있는 위치
	Vector			m_vecTargetPos;		// 카메라의 목표 위치
	CGameObject*	m_pTargetObj;		// 카메라가 추적할 오브젝트

	float			m_fTimeToTarget;	// 카메라가 목적지까지 가는데 남은시간

	float			m_fTargetBright;	// 카메라의 목표 밝기
	float			m_fCurBright;		// 카메라의 현재 밝기
	float			m_fTimeToBright;	// 카메라의 밝기 변화 남은시간

public:
	Vector			GetLookAt();
	Vector			GetTargetPos();
	CGameObject*	GetTargetObj();

	// 오브젝트를 지정할 경우 목표위치는 목표 오브젝트의 위치로 지정됨
	void SetTargetPos(Vector targetPos, float timeToTarget = 0);	// 카메라의 목표 위치 지정
	void SetTargetObj(CGameObject* pTargetObj);						// 카메라의 목표 오브젝트 지정

	Vector WorldToScreenPoint(Vector worldPoint);	// 게임위치->화면위치
	Vector ScreenToWorldPoint(Vector screenPoint);	// 화면위치->게임위치

	void Scroll(Vector dir, float velocity);		// 카메라 스크롤

	void FadeIn(float duration);		// 씬 진입 효과
	void FadeOut(float duration);		// 씬 탈출 효과

private:
	void Init();
	void Update();
	void Render();
	void Release();

private:
	void MoveToTarget();
	void RenderEffect();
};

#define CAMERA	CCameraManager::GetInstance()