#include "framework.h"
#include "CCameraManager.h"

#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CGameObject.h"

CCameraManager::CCameraManager()
{
	m_vecLookAt		= Vector(0, 0);
	m_vecTargetPos	= Vector(0, 0);
	m_pTargetObj	= nullptr;
	m_fTimeToTarget = 0;

	m_fTargetBright = 1.f;
	m_fCurBright = 1.f;
	m_fTimeToBright = 0.f;
}

CCameraManager::~CCameraManager()
{
}

Vector CCameraManager::GetLookAt()
{
	return m_vecLookAt;
}

Vector CCameraManager::GetTargetPos()
{
	return m_vecTargetPos;
}

CGameObject* CCameraManager::GetTargetObj()
{
	return m_pTargetObj;
}

void CCameraManager::SetTargetPos(Vector targetPos, float timeToTarget)
{
	m_vecTargetPos = targetPos;
	m_fTimeToTarget = timeToTarget;
}

void CCameraManager::SetTargetObj(CGameObject* pTargetObj)
{
	m_pTargetObj = pTargetObj;
}

Vector CCameraManager::WorldToScreenPoint(Vector worldPoint)
{
	return worldPoint - (m_vecLookAt - Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f));
}

Vector CCameraManager::ScreenToWorldPoint(Vector screenPoint)
{
	return screenPoint + (m_vecLookAt - Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f));
}

void CCameraManager::Scroll(Vector dir, float velocity)
{
	// 스크롤의 방향 크기가 없는 경우 진행하지 않음
	if (dir.Magnitude() == 0)
		return;

	// 스크롤의 목표 위치는 현재위치에서 스크롤 방향으로 떨어진 위치
	m_vecTargetPos = m_vecLookAt;
	m_vecTargetPos += dir.Normalized() * velocity * ABSDT;
	m_fTimeToTarget = 0;	// 스크롤은 시간차를 두지 않은 즉각 이동
}

void CCameraManager::FadeIn(float duration)
{
	m_fTargetBright = 1.f;
	m_fTimeToBright = duration;
}

void CCameraManager::FadeOut(float duration)
{
	m_fTargetBright = 0.f;
	m_fTimeToBright = duration;
}

void CCameraManager::Init()
{
}

void CCameraManager::Update()
{
	// 추적할 게임오브젝트가 있을 경우
	if (nullptr != m_pTargetObj)
	{
		if (m_pTargetObj->GetReserveDelete())
		{
			// 추적할 게임오브젝트가 삭제예정인 경우 추적 해제
			m_pTargetObj = nullptr;
		}
		else
		{
			// 추적할 게임오브젝트가 있을 경우 게임오브젝트의 위치를 목표위치로 지정
			SetTargetPos(m_pTargetObj->GetPos());
		}
	}

	// 목표 위치로 이동
	MoveToTarget();
}

void CCameraManager::Render()
{
	RenderEffect();

	Vector screenPos = ScreenToWorldPoint(Vector(0, 0));
	RENDER->FillRect(screenPos.x, screenPos.y, screenPos.x + WINSIZEX, screenPos.y + WINSIZEY, Color(0, 0, 0, 1 - m_fCurBright));
}

void CCameraManager::Release()
{
}

void CCameraManager::MoveToTarget()
{
	m_fTimeToTarget -= DT;

	if (m_fTimeToTarget <= 0)
	{
		// 목표위치까지 남은 시간이 없을 경우 목적지로 현재위치 고정
		m_vecLookAt = m_vecTargetPos;
	}
	else
	{
		// 목표위치까지 남은 시간이 있을 경우
		// 목적지까지 남은시간만큼의 속도로 이동
		// 이동거리 = 속력 * 시간
		// 속력 = (도착지 - 출발지) / 소요시간
		// 시간 = 프레임단위시간
		m_vecLookAt += (m_vecTargetPos - m_vecLookAt) / m_fTimeToTarget * DT;
	}
}

void CCameraManager::RenderEffect()
{
	m_fTimeToBright -= DT;

	if (m_fTimeToBright <= 0)
	{
		// 카메라 효과가 남은 시간이 없을 경우 목표 밝기로 고정
		m_fCurBright = m_fTargetBright;
	}
	else
	{
		m_fCurBright += (m_fTargetBright - m_fCurBright) / m_fTimeToBright * DT;
	}
}
