#include "framework.h"
#include "CBackground.h"

CBackground::CBackground()
{
	m_vecScale = Vector(10, 10);
	m_vecDir = Vector(0, 0);
	m_fVelocity = 300;
	m_layer = Layer::BackGround;
	m_strName = L"배경";
	m_pImg = nullptr;
}

CBackground::~CBackground()
{
}

void CBackground::Init()
{
}

void CBackground::Update()
{
	m_vecPos -= m_vecDir * m_fVelocity * DT * 0.3;

	// 화면 좌측 밖으로 나갈경우 화면 우측 밖에 재배치
	if (m_vecPos.x < -1280)
		this->SetPos(WINSIZEX + 1280, WINSIZEY * 0.5);
}

void CBackground::Render()
{
	m_pImg = RESOURCE->LoadImg(L"BackGround", L"Image\\Stage1_BackGround2.png");

	RENDER->Image(
		m_pImg,
		m_vecPos.x - m_pImg->GetWidth() * 0.5,
		m_vecPos.y - m_pImg->GetHeight() * 0.5,
		m_vecPos.x + m_pImg->GetWidth() * 0.5,
		m_vecPos.y + m_pImg->GetHeight() * 0.5);

}

void CBackground::Release()
{
}

void CBackground::OnCollisionEnter(CCollider* pOtherCollider)
{
}

void CBackground::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CBackground::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
