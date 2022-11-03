#include "framework.h"
#include "CGameObject.h"

#include "CComponent.h"
#include "CCollider.h"

CGameObject::CGameObject()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(0, 0);
	m_layer = Layer::Default;
	m_bReservedDelete = false;
	m_bSafeToDelete = false;

	m_pCollider = nullptr;
}

CGameObject::~CGameObject()
{
}

Vector CGameObject::GetPos()
{
	return m_vecPos;
}

void CGameObject::SetPos(Vector pos)
{
	m_vecPos = pos;
}

void CGameObject::SetPos(float x, float y)
{
	m_vecPos.x = x;
	m_vecPos.y = y;
}

Vector CGameObject::GetScale()
{
	return m_vecScale;
}

void CGameObject::SetScale(Vector scale)
{
	m_vecScale = scale;
}

void CGameObject::SetScale(float x, float y)
{
	m_vecScale.x = x;
	m_vecScale.y = y;
}

Layer CGameObject::GetLayer()
{
	return m_layer;
}

void CGameObject::SetLayer(Layer layer)
{
	m_layer = layer;
}

wstring CGameObject::GetName()
{
	return m_strName;
}

void CGameObject::SetName(wstring name)
{
	m_strName = name;
}

bool CGameObject::GetReserveDelete()
{
    return m_bReservedDelete;
}

void CGameObject::AddComponent(CComponent* component)
{
	m_listComponent.push_back(component);
	component->Init();
	component->SetOwner(this);
}

void CGameObject::RemoveComponent(CComponent* component)
{
	component->Release();
	m_listComponent.remove(component);
	delete component;
}

void CGameObject::ComponentRender()
{
	for (CComponent* pComponent : m_listComponent)
	{
		pComponent->Render();
	}
}

CCollider* CGameObject::GetCollider()
{
	return m_pCollider;
}

void CGameObject::AddCollider(ColliderType type, Vector scale, Vector offsetPos)
{
	if (nullptr != m_pCollider)
		return;

	m_pCollider = new CCollider();
	m_pCollider->SetType(type);
	m_pCollider->SetScale(scale);
	m_pCollider->SetOffsetPos(offsetPos);
	AddComponent(m_pCollider);
}

void CGameObject::RemoveCollider()
{
	if (nullptr == m_pCollider)
		return;

	RemoveComponent(m_pCollider);
	m_pCollider = nullptr;
}

void CGameObject::SetReserveDelete()
{
	m_bReservedDelete = true;
}

bool CGameObject::GetSafeToDelete()
{
	return m_bSafeToDelete;
}

void CGameObject::SetSafeToDelete()
{
	m_bSafeToDelete = true;
}

void CGameObject::GameObjectInit()
{
	// 게임오브젝트 내에 모든 컴포넌트 초기화
	for (CComponent* pComponent : m_listComponent)
	{
		pComponent->Init();
	}

	// 상속한 자식 초기화
	Init();
}

void CGameObject::GameObjectUpdate()
{
	// 상속한 자식 로직갱신
	Update();

	// 게임오브젝트 내에 모든 컴포넌트 로직갱신
	for (CComponent* pComponent : m_listComponent)
	{
		pComponent->Update();
	}
}

void CGameObject::GameObjectPhysicsUpdate()
{
	// 게임오브젝트 내에 모든 컴포넌트 물리처리갱신
	for (CComponent* pComponent : m_listComponent)
	{
		pComponent->PhysicsUpdate();
	}
}

void CGameObject::GameObjectRender()
{
	// 상속한 자식 표현갱신
	Render();

	// 게임오브젝트 내에 모든 컴포넌트 표현갱신
	for (CComponent* pComponent : m_listComponent)
	{
		pComponent->Render();
	}
}

void CGameObject::GameObjectRelease()
{
	// 게임오브젝트 내에 모든 컴포넌트 마무리
	for (CComponent* pComponent : m_listComponent)
	{
		pComponent->Release();
		delete pComponent;
	}
	m_listComponent.clear();

	// 상속한 자식 마무리
	Release();
}