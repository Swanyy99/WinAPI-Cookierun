#include "framework.h"
#include "CObstacle3.h"
#include "CObstacleBoomEffect.h"
#include "CJemBottle.h"

extern float playerPosX;
extern float playerPosY;

extern bool isMagnet;
extern bool isDash;

extern bool skillOn;
extern bool skillOn2;
extern bool skillOn3;

CObstacle3::CObstacle3()
{
	m_vecScale = Vector(1000, 1000);
	m_strName = L"장애물";
	m_layer = Layer::Obstacle;
	m_vecDir = Vector(1, 0);
	m_fVelocity = 300;
	m_pAnimatorObstacle3 = nullptr;
	m_pObstacle3Image = nullptr;
	m_fJemBoxDropTimer = 0;
}

CObstacle3::~CObstacle3()
{
}

void CObstacle3::Init()
{
	m_pObstacle3Image = RESOURCE->LoadImg(L"Obstacle3s", L"Image\\Obstacle3Ver2.png");


	m_pAnimatorObstacle3 = new CAnimator;
	m_pAnimatorObstacle3->CreateAnimation(L"Obstacle3", m_pObstacle3Image, Vector(0, 0), Vector(114, 130), Vector(114, 0.f), 0.09f, 11, false);

	m_pAnimatorObstacle3->Play(L"Obstacle3", false);
	AddComponent(m_pAnimatorObstacle3);

	AddCollider(ColliderType::Rect, Vector(50, 40), Vector(0, 30));

}

void CObstacle3::Update()
{

	m_vecPos -= m_vecDir * m_fVelocity * DT;

	m_fJemBoxDropTimer += DT;

	if (skillOn3 == false)
	{
		if (m_fJemBoxDropTimer > 1)
		{
			m_fJemBoxDropTimer -= 100;
			CJemBottle* Jem = new CJemBottle();
			Jem->SetPos(m_vecPos.x - 100, m_vecPos.y + 30);
			ADDOBJECT(Jem);
		}
	}

	else if (skillOn3 == true)
	{
		if (m_fJemBoxDropTimer > 1.5)
		{
			m_fJemBoxDropTimer -= 100;
			CJemBottle* Jem = new CJemBottle();
			Jem->SetPos(m_vecPos.x - 100, m_vecPos.y + 30);
			ADDOBJECT(Jem);
		}
	}


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
