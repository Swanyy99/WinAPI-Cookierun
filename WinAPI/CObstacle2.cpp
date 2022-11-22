#include "framework.h"
#include "CObstacle2.h"
#include "CObstacleBoomEffect.h"

extern float playerPosX;
extern float playerPosY;

extern bool isMagnet;
extern bool isDash;
extern bool skillOn;
extern bool skillOn2;

CObstacle2::CObstacle2()
{
	m_vecScale = Vector(1000, 1000);
	m_strName = L"장애물";
	m_layer = Layer::Obstacle;
	m_vecDir = Vector(1, 0);
	m_fVelocity = 300;
	m_pAnimatorObstacle2 = nullptr;
	m_pObstacle2Image = nullptr;

}

CObstacle2::~CObstacle2()
{
}

void CObstacle2::Init()
{
	m_pObstacle2Image = RESOURCE->LoadImg(L"Obstacle2s", L"Image\\Obstacle2Ver2.png");


	m_pAnimatorObstacle2 = new CAnimator;
	m_pAnimatorObstacle2->CreateAnimation(L"Obstacle2", m_pObstacle2Image, Vector(440, 0), Vector(220, 201), Vector(220, 0.f), 0.15f, 4);

	m_pAnimatorObstacle2->Play(L"Obstacle2", false);
	AddComponent(m_pAnimatorObstacle2);

	AddCollider(ColliderType::Rect, Vector(50, 100), Vector(20, 40));

}

void CObstacle2::Update()
{

	m_vecPos -= m_vecDir * m_fVelocity * DT * 1;


	if (m_vecPos.x < -100)
		DELETEOBJECT(this);

	Obstacle2Image = L"Obstacle2";

	AnimatorUpdate();
}

void CObstacle2::Render()
{


}

void CObstacle2::Release()
{
}

void CObstacle2::AnimatorUpdate()
{
	//m_pAnimators->Play(obstacleImage, false);
	m_pAnimatorObstacle2->Play(Obstacle2Image, false);
}


void CObstacle2::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어" && isDash == true)
	{
		Logger::Debug(L"플레이어가 장애물을 부쉈습니다");
		CObstacleBoomEffect* pObstacleBoomEffect = new CObstacleBoomEffect();
		pObstacleBoomEffect->SetPos(playerPosX, playerPosY);
		ADDOBJECT(pObstacleBoomEffect);

		CSound* pSound = RESOURCE->LoadSound(L"Explosion", L"Sound\\Explosion.wav");
		SOUND->Play(pSound, 0.1f, false);

		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"펫미사일")
	{
		Logger::Debug(L"왕 하프물범이 장애물을 부쉈습니다 ");
		CObstacleBoomEffect* pObstacleBoomEffect = new CObstacleBoomEffect();
		pObstacleBoomEffect->SetPos(m_vecPos.x, m_vecPos.y);
		ADDOBJECT(pObstacleBoomEffect);

		CSound* pSound = RESOURCE->LoadSound(L"Explosion", L"Sound\\Explosion.wav");
		SOUND->Play(pSound, 0.08f, false);

		DELETEOBJECT(this);
	}
	if (pOtherCollider->GetObjName() == L"펫미사일2")
	{
		Logger::Debug(L"물보라가 장애물을 부쉈습니다");
		CObstacleBoomEffect* pObstacleBoomEffect = new CObstacleBoomEffect();
		pObstacleBoomEffect->SetPos(m_vecPos.x, m_vecPos.y);
		ADDOBJECT(pObstacleBoomEffect);

		CSound* pSound = RESOURCE->LoadSound(L"Explosion", L"Sound\\Explosion.wav");
		SOUND->Play(pSound, 0.08f, false);

		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"펫미사일3")
	{
		Logger::Debug(L"빛의 우유 방패가 장애물을 부쉈습니다");
		CObstacleBoomEffect* pObstacleBoomEffect = new CObstacleBoomEffect();
		pObstacleBoomEffect->SetPos(m_vecPos.x, m_vecPos.y);
		ADDOBJECT(pObstacleBoomEffect);

		CSound* pSound = RESOURCE->LoadSound(L"Explosion", L"Sound\\Explosion.wav");
		SOUND->Play(pSound, 0.08f, false);

		DELETEOBJECT(this);
	}
}

void CObstacle2::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CObstacle2::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CObstacle2::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CObstacle2::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
