#include "framework.h"
#include "CObstacleSky.h"


CObstacleSky::CObstacleSky()
{
	m_vecScale = Vector(100, 100);
	m_strName = L"장애물";
	m_layer = Layer::Obstacle;
	m_vecDir = Vector(1, 0);
	m_fVelocity = 300;
	m_pAnimators = nullptr;
	m_pObstacle1Image = nullptr;

	m_pImg = nullptr;
}

CObstacleSky::~CObstacleSky()
{
}

void CObstacleSky::Init()
{

	AddCollider(ColliderType::Rect, Vector(60, 570), Vector(0, 0));

}

void CObstacleSky::Update()
{

	m_vecPos -= m_vecDir * m_fVelocity * DT;

	if (m_vecPos.x < - 200)
		DELETEOBJECT(this);

	//obstacleImage = L"IdleObstacle";
}

void CObstacleSky::Render()
{
	m_pImg = RESOURCE->LoadImg(L"ObstacleSky", L"Image\\ObstacleSky1.png");

	RENDER->Image(
		m_pImg,
		m_vecPos.x - m_pImg->GetWidth() * 0.6,
		m_vecPos.y - m_pImg->GetHeight() * 0.6,
		m_vecPos.x + m_pImg->GetWidth() * 0.6,
		m_vecPos.y + m_pImg->GetHeight() * 0.6);
}

void CObstacleSky::Release()
{
}

void CObstacleSky::AnimatorUpdate()
{
	//m_pAnimators->Play(obstacleImage, false);
}


void CObstacleSky::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"미사일")
	{
		DELETEOBJECT(this);
	}
}

void CObstacleSky::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CObstacleSky::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CObstacleSky::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CObstacleSky::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
