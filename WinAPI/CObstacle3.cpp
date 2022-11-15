#include "framework.h"
#include "CObstacle3.h"
#include "framework.h"
#include "CObstacle2.h"
#include "CObstacleBoomEffect.h"

extern float playerPosX;
extern float playerPosY;

extern bool isMagnet;
extern bool isDash;
extern bool skillOn;
extern bool skillOn2;

CObstacle3::CObstacle3()
{
	m_vecScale = Vector(1000, 1000);
	m_strName = L"��ֹ�";
	m_layer = Layer::Obstacle;
	m_vecDir = Vector(1, 0);
	m_fVelocity = 300;
	m_pAnimatorObstacle3 = nullptr;
	m_pObstacle3Image = nullptr;

}

CObstacle3::~CObstacle3()
{
}

void CObstacle3::Init()
{
	m_pObstacle3Image = RESOURCE->LoadImg(L"Obstacle3s", L"Image\\Obstacle3.png");


	m_pAnimatorObstacle3 = new CAnimator;
	m_pAnimatorObstacle3->CreateAnimation(L"Obstacle3", m_pObstacle3Image, Vector(0, 0), Vector(114, 130), Vector(114, 0.f), 0.1f, 11, false);

	m_pAnimatorObstacle3->Play(L"Obstacle3", false);
	AddComponent(m_pAnimatorObstacle3);

	AddCollider(ColliderType::Rect, Vector(50, 40), Vector(0, 30));

}

void CObstacle3::Update()
{

	m_vecPos -= m_vecDir * m_fVelocity * DT;


	if (m_vecPos.x < -100)
		DELETEOBJECT(this);

	Obstacle3Image = L"Obstacle3";

	AnimatorUpdate();
}

void CObstacle3::Render()
{


}

void CObstacle3::Release()
{
}

void CObstacle3::AnimatorUpdate()
{
	//m_pAnimators->Play(obstacleImage, false);
	m_pAnimatorObstacle3->Play(Obstacle3Image, false);
}


void CObstacle3::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�÷��̾�" && isDash == true)
	{
		Logger::Debug(L"�÷��̾ ��ֹ��� �ν����ϴ�");
		CObstacleBoomEffect* pObstacleBoomEffect = new CObstacleBoomEffect();
		pObstacleBoomEffect->SetPos(playerPosX, playerPosY);
		ADDOBJECT(pObstacleBoomEffect);
		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"��̻���" && skillOn == true)
	{
		Logger::Debug(L"�� ���������� ��ֹ��� �ν����ϴ� ");
		CObstacleBoomEffect* pObstacleBoomEffect = new CObstacleBoomEffect();
		pObstacleBoomEffect->SetPos(m_vecPos.x, m_vecPos.y);
		ADDOBJECT(pObstacleBoomEffect);
		DELETEOBJECT(this);
	}
	if (pOtherCollider->GetObjName() == L"��̻���2")
	{
		Logger::Debug(L"������ ��ֹ��� �ν����ϴ�");
		CObstacleBoomEffect* pObstacleBoomEffect = new CObstacleBoomEffect();
		pObstacleBoomEffect->SetPos(m_vecPos.x, m_vecPos.y);
		ADDOBJECT(pObstacleBoomEffect);
		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"��̻���3")
	{
		Logger::Debug(L"���� ���� ���а� ��ֹ��� �ν����ϴ�");
		CObstacleBoomEffect* pObstacleBoomEffect = new CObstacleBoomEffect();
		pObstacleBoomEffect->SetPos(m_vecPos.x, m_vecPos.y);
		ADDOBJECT(pObstacleBoomEffect);
		DELETEOBJECT(this);
	}
}

void CObstacle3::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CObstacle3::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CObstacle3::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CObstacle3::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}