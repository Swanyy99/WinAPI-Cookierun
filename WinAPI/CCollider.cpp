#include "framework.h"
#include "CCollider.h"

#include "CRenderManager.h"
#include "CGameObject.h"

UINT CCollider::s_uiID = 0;

extern bool isDebugMode;

CCollider::CCollider()
{
	m_uiID = s_uiID++;
	m_uiCollisionCount = 0;

	m_type = ColliderType::Rect;
	m_vecPos = Vector(0, 0);
	m_vecOffsetPos = Vector(0, 0);
	m_vecScale = Vector(0, 0);
}

CCollider::~CCollider()
{
}

ColliderType CCollider::GetType()
{
	return m_type;
}

wstring CCollider::GetObjName()
{
	return GetOwner()->GetName();
}

UINT CCollider::GetID()
{
    return m_uiID;
}

Vector CCollider::GetPos()
{
	return m_vecPos;
}

void CCollider::SetType(ColliderType type)
{
	m_type = type;
}

void CCollider::SetPos(Vector pos)
{
	m_vecPos = pos;
}

Vector CCollider::GetOffsetPos()
{
	return m_vecOffsetPos;
}

void CCollider::SetOffsetPos(Vector offset)
{
	m_vecOffsetPos = offset;
}

Vector CCollider::GetScale()
{
	return m_vecScale;
}

void CCollider::SetScale(Vector scale)
{
	m_vecScale = scale;
}

void CCollider::Init()
{
}

void CCollider::Update()
{
}

void CCollider::PhysicsUpdate()
{
	m_vecPos = m_vecOffsetPos + GetOwner()->GetPos();
}

void CCollider::Render()
{
	Color color = Color(0, 0, 0, 0);

	if (m_uiCollisionCount > 0)
	{
		if(isDebugMode == true)
			color = Color(255, 0, 0, 1.f);
		if (isDebugMode == false)
			color = Color(255, 0, 0, 0);
	}
	else
	{
		if (isDebugMode == true)
			color = Color(0, 255, 0, 1.f);
		if (isDebugMode == false)
			color = Color(0, 255, 0, 0);
	}

	if (m_type == ColliderType::Rect)
	{
		RENDER->FrameRect(
			m_vecPos.x - m_vecScale.x * 0.5f,
			m_vecPos.y - m_vecScale.y * 0.5f,
			m_vecPos.x + m_vecScale.x * 0.5f,
			m_vecPos.y + m_vecScale.y * 0.5f,
			color);
	}
	else if (m_type == ColliderType::Circle)
	{
		RENDER->FrameCircle(
			m_vecPos.x,
			m_vecPos.y,
			m_vecScale.x,
			color
		);
	}
}

void CCollider::Release()
{
}

void CCollider::OnCollisionEnter(CCollider* pOtherCollider)
{
	m_uiCollisionCount++;
	GetOwner()->OnCollisionEnter(pOtherCollider);
}

void CCollider::OnCollisionStay(CCollider* pOtherCollider)
{
	GetOwner()->OnCollisionStay(pOtherCollider);
}

void CCollider::OnCollisionExit(CCollider* pOtherCollider)
{
	m_uiCollisionCount--;
	GetOwner()->OnCollisionExit(pOtherCollider);
}
