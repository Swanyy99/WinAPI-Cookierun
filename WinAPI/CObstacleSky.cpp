#include "framework.h"
#include "CObstacleSky.h"
#include "CObstacleBoomEffect.h"

extern bool isDash;
extern float playerPosX;
extern float playerPosY;
extern bool skillOn;
extern bool skillOn2;

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
	m_pImg = RESOURCE->LoadImg(L"ObstacleSky", L"Image\\ObstacleSky2.png");

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

	if (pOtherCollider->GetObjName() == L"플레이어" && isDash == true)
	{
		Logger::Debug(L"플레이어가 장애물을 부쉈습니다");
		CObstacleBoomEffect* pObstacleBoomEffect = new CObstacleBoomEffect();
		pObstacleBoomEffect->SetPos(playerPosX + 30, playerPosY - 70);
		ADDOBJECT(pObstacleBoomEffect);

		CSound* pSound = RESOURCE->LoadSound(L"Explosion", L"Sound\\Explosion.wav");
		SOUND->Play(pSound, 0.1f, false);

		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"펫미사일")
	{
		Logger::Debug(L"왕 하프물범이 장애물을 부쉈습니다");
		CObstacleBoomEffect* pObstacleBoomEffect = new CObstacleBoomEffect();
		pObstacleBoomEffect->SetPos(m_vecPos.x, m_vecPos.y + 230);
		ADDOBJECT(pObstacleBoomEffect);

		CSound* pSound = RESOURCE->LoadSound(L"Explosion", L"Sound\\Explosion.wav");
		SOUND->Play(pSound, 0.08f, false);

		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"펫미사일2")
	{
		Logger::Debug(L"물보라가 장애물을 부쉈습니다");
		CObstacleBoomEffect* pObstacleBoomEffect = new CObstacleBoomEffect();
		pObstacleBoomEffect->SetPos(m_vecPos.x, m_vecPos.y + 100);
		ADDOBJECT(pObstacleBoomEffect);

		CSound* pSound = RESOURCE->LoadSound(L"Explosion", L"Sound\\Explosion.wav");
		SOUND->Play(pSound, 0.08f, false);

		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"펫미사일3")
	{
		Logger::Debug(L"빛의 우유 방패가 장애물을 부쉈습니다");
		CObstacleBoomEffect* pObstacleBoomEffect = new CObstacleBoomEffect();
		pObstacleBoomEffect->SetPos(m_vecPos.x, m_vecPos.y + 100);
		ADDOBJECT(pObstacleBoomEffect);

		CSound* pSound = RESOURCE->LoadSound(L"Explosion", L"Sound\\Explosion.wav");
		SOUND->Play(pSound, 0.08f, false);

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
