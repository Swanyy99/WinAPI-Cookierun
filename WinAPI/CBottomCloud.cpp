#include "framework.h"
#include "CBottomCloud.h"

extern bool isDash;

CBottomCloud::CBottomCloud()
{
	m_vecScale = Vector(10, 10);
	m_vecDir = Vector(0, 0);
	m_fVelocity = 300;
	//m_layer = Layer::BottomBackGround;
	m_layer = Layer::BottomBackGround;
	m_strName = L"배경";
	m_pImg = nullptr;
}

CBottomCloud::~CBottomCloud()
{
}

void CBottomCloud::Init()
{
}

void CBottomCloud::Update()
{

	m_vecPos -= m_vecDir * m_fVelocity * DT * 1.2;


	// 화면 좌측 밖으로 나갈경우 화면 우측 밖에 재배치

	if (m_vecPos.x <= -1280)
	{
		this->SetPos(WINSIZEX + 1280, WINSIZEY * 0.85);

	}

	/*if (m_vecPos.x <= -638)
	{
		this->SetPos(WINSIZEX + 640, WINSIZEY * 0.85);

	}*/
}

void CBottomCloud::Render()
{
	m_pImg = RESOURCE->LoadImg(L"BottomBackGround", L"Image\\Cloud.png");

	RENDER->Image(
		m_pImg,
		m_vecPos.x - m_pImg->GetWidth() * 0.5,
		m_vecPos.y - m_pImg->GetHeight() * 0.5,
		m_vecPos.x + m_pImg->GetWidth() * 0.5,
		m_vecPos.y + m_pImg->GetHeight() * 0.5);

}

void CBottomCloud::Release()
{
}

void CBottomCloud::OnCollisionEnter(CCollider* pOtherCollider)
{
}

void CBottomCloud::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CBottomCloud::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
