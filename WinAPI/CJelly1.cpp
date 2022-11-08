#include "framework.h"
#include "CJelly1.h"



CJelly1::CJelly1()
{
	m_vecScale = Vector(1000, 1000);
	m_strName = L"����";
	m_layer = Layer::Jelly;
	m_vecDir = Vector(1, 0);
	m_fVelocity = 300;
	m_pAnimatorJelly = nullptr;
	m_pObstacle1Image = nullptr;

}

CJelly1::~CJelly1()
{
}

void CJelly1::Init()
{
	m_pJellyImage = RESOURCE->LoadImg(L"FlowerJelly", L"Image\\RabbitJelly.png");


	m_pAnimatorJelly = new CAnimator;
	m_pAnimatorJelly->CreateAnimation(L"Jelly1", m_pJellyImage, Vector(0, 0), Vector(84, 89), Vector(84, 0.f), 0.2f, 2);

	m_pAnimatorJelly->Play(L"Jelly1", false);
	AddComponent(m_pAnimatorJelly);

	AddCollider(ColliderType::Rect, Vector(70, 70), Vector(0, 0));

}

void CJelly1::Update()
{

	m_vecPos -= m_vecDir * m_fVelocity * DT;

	if (m_vecPos.x < -100)
		DELETEOBJECT(this);

	jellyImage = L"Jelly1";

	AnimatorUpdate();
}

void CJelly1::Render()
{


}

void CJelly1::Release()
{
}

void CJelly1::AnimatorUpdate()
{
	//m_pAnimators->Play(obstacleImage, false);
	m_pAnimatorJelly->Play(jellyImage, false);
}


void CJelly1::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
	{
		Logger::Debug(L"�÷��̾ ������ �Ծ����ϴ�.");
		DELETEOBJECT(this);
	}
}

void CJelly1::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CJelly1::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CJelly1::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CJelly1::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
