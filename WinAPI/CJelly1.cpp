#include "framework.h"
#include "CJelly1.h"
#include "CJellyEatEffect.h"

extern float playerPosX;
extern float playerPosY;

extern bool isMagnet;
extern bool isDash;
extern bool skillOn;

extern int choiceJelly;

Vector DistanceGap;

CJelly1::CJelly1()
{
	m_vecScale = Vector(1000, 1000);
	m_strName = L"Á©¸®";
	m_layer = Layer::Jelly;
	m_vecDir = Vector(1, 0);
	m_fVelocity = 300;
	m_pAnimatorJelly1 = nullptr;
	m_pAnimatorJelly2 = nullptr;
	m_pAnimatorJelly3 = nullptr;
	m_pObstacle1Image = nullptr;

}

CJelly1::~CJelly1()
{
}

void CJelly1::Init()
{
	if (choiceJelly == 1)
	{
		m_pJellyImage = RESOURCE->LoadImg(L"RabbitJelly", L"Image\\RabbitJelly.png");
		m_pAnimatorJelly1 = new CAnimator;
		m_pAnimatorJelly1->CreateAnimation(L"Jelly1", m_pJellyImage, Vector(0, 0), Vector(84, 89), Vector(84, 0.f), 0.2f, 2);
		m_pAnimatorJelly1->Play(L"Jelly1", false);
		AddComponent(m_pAnimatorJelly1);


	}

	if (choiceJelly == 2)
	{
		m_pJellyImage = RESOURCE->LoadImg(L"CuteJelly", L"Image\\CuteJelly.png");
		m_pAnimatorJelly2 = new CAnimator;

		m_pAnimatorJelly2->CreateAnimation(L"Jelly2", m_pJellyImage, Vector(0, 0), Vector(87.5, 80), Vector(87.5, 0.f), 0.11f, 7);
		m_pAnimatorJelly2->Play(L"Jelly2", false);
		AddComponent(m_pAnimatorJelly2);

	}

	if (choiceJelly == 3)
	{
		m_pJellyImage = RESOURCE->LoadImg(L"LibraryJelly", L"Image\\LibraryJelly.png");
		m_pAnimatorJelly3 = new CAnimator;

		m_pAnimatorJelly3->CreateAnimation(L"Jelly3", m_pJellyImage, Vector(0, 0), Vector(88.5, 88), Vector(88.5, 0.f), 0.1f, 8);
		m_pAnimatorJelly3->Play(L"Jelly3", false);
		AddComponent(m_pAnimatorJelly3);

	}

	if (choiceJelly == 4)
	{
		m_pJellyImage = RESOURCE->LoadImg(L"UFOJelly", L"Image\\UFOJelly.png");
		m_pAnimatorJelly4 = new CAnimator;

		m_pAnimatorJelly4->CreateAnimation(L"Jelly4", m_pJellyImage, Vector(0, 0), Vector(133, 97), Vector(133, 0.f), 0.1f, 8);
		m_pAnimatorJelly4->Play(L"Jelly4", false);
		AddComponent(m_pAnimatorJelly4);

	}

	if (choiceJelly == 5)
	{
		m_pJellyImage = RESOURCE->LoadImg(L"Christmasjelly", L"Image\\Christmasjelly.png");
		m_pAnimatorJelly5 = new CAnimator;

		m_pAnimatorJelly5->CreateAnimation(L"Jelly5", m_pJellyImage, Vector(0, 0), Vector(80.5, 91), Vector(80.5, 0.f), 0.15f, 6);
		m_pAnimatorJelly5->Play(L"Jelly5", false);
		AddComponent(m_pAnimatorJelly5);

	}
		


	AddCollider(ColliderType::Rect, Vector(70, 70), Vector(0, 0));

}

void CJelly1::Update()
{


	m_vecPos -= m_vecDir * m_fVelocity * DT;


	if (isMagnet == true)
	{
		if (abs(m_vecPos.x - playerPosX) < 200 && abs(m_vecPos.y - playerPosY) < 200)
		{

			m_vecPos.x -= (m_vecPos.x - playerPosX) * DT * 2.3;
			m_vecPos.y -= (m_vecPos.y - playerPosY) * DT * 2.3;

		}

	}

	if (m_vecPos.x < -100)
		DELETEOBJECT(this);

	if (choiceJelly == 1)
		jellyImage = L"Jelly1";

	if (choiceJelly == 2)
		jellyImage = L"Jelly2";

	if (choiceJelly == 3)
		jellyImage = L"Jelly3";

	if (choiceJelly == 4)
		jellyImage = L"Jelly4";

	if (choiceJelly == 5)
		jellyImage = L"Jelly5";

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
	if (choiceJelly == 1)
		m_pAnimatorJelly1->Play(jellyImage, false);

	if (choiceJelly == 2)
		m_pAnimatorJelly2->Play(jellyImage, false);

	if (choiceJelly == 3)
		m_pAnimatorJelly3->Play(jellyImage, false);

	if (choiceJelly == 4)
		m_pAnimatorJelly4->Play(jellyImage, false);

	if (choiceJelly == 5)
		m_pAnimatorJelly5->Play(jellyImage, false);
}


void CJelly1::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"ÇÃ·¹ÀÌ¾î")
	{
		Logger::Debug(L"ÇÃ·¹ÀÌ¾î°¡ Á©¸®¸¦ ¸Ô¾ú½À´Ï´Ù.");
		CJellyEatEffect* pJellyEffect = new CJellyEatEffect();
		pJellyEffect->SetPos(m_vecPos.x - 10, m_vecPos.y);
		ADDOBJECT(pJellyEffect);
		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"Æê¹Ì»çÀÏ" && skillOn == true)
	{
		Logger::Debug(L"¿Õ ÇÏÇÁ¹°¹üÀÌ Á©¸®¸¦ ¸Ô¾ú½À´Ï´Ù.");
		CJellyEatEffect* pJellyEffect = new CJellyEatEffect();
		pJellyEffect->SetPos(m_vecPos.x - 10, m_vecPos.y);
		ADDOBJECT(pJellyEffect);
		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"Æê¹Ì»çÀÏ2")
	{
		Logger::Debug(L"¹°º¸¶ó°¡ Á©¸®¸¦ ¸Ô¾ú½À´Ï´Ù.");
		CJellyEatEffect* pJellyEffect = new CJellyEatEffect();
		pJellyEffect->SetPos(m_vecPos.x - 10, m_vecPos.y);
		ADDOBJECT(pJellyEffect);
		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"Æê¹Ì»çÀÏ3")
	{
		Logger::Debug(L"ºûÀÇ ¿ìÀ¯ ¹æÆÐ°¡ Á©¸®¸¦ ¸Ô¾ú½À´Ï´Ù");
		CJellyEatEffect* pJellyEffect = new CJellyEatEffect();
		pJellyEffect->SetPos(m_vecPos.x - 10, m_vecPos.y);
		ADDOBJECT(pJellyEffect);
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
