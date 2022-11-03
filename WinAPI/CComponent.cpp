#include "framework.h"
#include "CComponent.h"

CComponent::CComponent()
{
	m_pOwner = nullptr;
}

CComponent::~CComponent()
{
}

void CComponent::SetOwner(CGameObject* pOwner)
{
	m_pOwner = pOwner;
}

CGameObject* CComponent::GetOwner()
{
	return m_pOwner;
}