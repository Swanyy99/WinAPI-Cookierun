#include "framework.h"
#include "CObstacle.h"


CObstacle::CObstacle()
{
	m_vecScale = Vector(100, 100);
	m_strName = L"��ֹ�";
	m_layer = Layer::Obstacle;
	m_vecDir = Vector(1, 0);
	m_fVelocity = 300;
	m_pAnimators = nullptr;
	m_pObstacle1Image = nullptr;

	m_pImg = nullptr;
}

CObstacle::~CObstacle()
{
}

void CObstacle::Init()
{

	AddCollider(ColliderType::Rect, Vector(15, 60), Vector(0, 10));

}

void CObstacle::Update()
{

	m_vecPos -= m_vecDir * m_fVelocity * DT;

	if (m_vecPos.x < 0)
		DELETEOBJECT(this);

	obstacleImage = L"IdleObstacle";
}

void CObstacle::Render()
{
	m_pImg = RESOURCE->LoadImg(L"Obstacle1", L"Image\\Obstacle1.png");

	RENDER->Image(
		m_pImg,
		m_vecPos.x - m_pImg->GetWidth() * 0.3 ,
		m_vecPos.y - m_pImg->GetHeight() * 0.3,
		m_vecPos.x + m_pImg->GetWidth() * 0.3,
		m_vecPos.y + m_pImg->GetHeight() * 0.3);
}

void CObstacle::Release()
{
}

void CObstacle::AnimatorUpdate()
{
	//m_pAnimators->Play(obstacleImage, false);
}


void CObstacle::OnCollisionEnter(CCollider* pOtherCollider)
{
}

void CObstacle::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CObstacle::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CObstacle::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CObstacle::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
