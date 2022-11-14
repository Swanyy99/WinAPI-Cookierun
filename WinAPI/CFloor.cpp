#include "framework.h"
#include "CFloor.h"

extern bool isDash;

CFloor::CFloor()
{
	m_vecScale = Vector(10, 10);
	m_vecDir = Vector(0, 0);
	m_fVelocity = 300;
	m_layer = Layer::Floor;
	m_strName = L"바닥";
	m_pImg = nullptr;
}

CFloor::~CFloor()
{
}

void CFloor::Init()
{
}

void CFloor::Update()
{

	m_vecPos -= m_vecDir * m_fVelocity * DT;

	// 화면 좌측 밖으로 나갈경우 화면 우측 밖에 재배치
	if (m_vecPos.x <= -160)
	{
		this->SetPos(WINSIZEX + 160, WINSIZEY * 0.9);

	}
}

void CFloor::Render()
{
	m_pImg = RESOURCE->LoadImg(L"Floor", L"Image\\FloorSet1.png");
	AddCollider(ColliderType::Rect, Vector(320, 90), Vector(0, 0));

	RENDER->Image(
		m_pImg,
		m_vecPos.x - m_pImg->GetWidth() * 0.5f,
		m_vecPos.y - m_pImg->GetHeight() * 0.5f,
		m_vecPos.x + m_pImg->GetWidth() * 0.5f,
		m_vecPos.y + m_pImg->GetHeight() * 0.5f);

}

void CFloor::Release()
{
}

void CFloor::OnCollisionEnter(CCollider* pOtherCollider)
{
}

void CFloor::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CFloor::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
