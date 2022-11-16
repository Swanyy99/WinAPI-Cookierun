#include "framework.h"
#include "CCoin.h"
#include "CJellyEatEffect.h"

extern float playerPosX;
extern float playerPosY;

extern bool isMagnet;
extern bool isDash;
extern bool skillOn;


CCoin::CCoin()
{
	m_vecScale = Vector(1000, 1000);
	m_strName = L"코인";
	m_layer = Layer::Coin;
	m_vecDir = Vector(1, 0);
	m_fVelocity = 300;
	m_pAnimatorCoin = nullptr;
	m_pCoinImage = nullptr;

}

CCoin::~CCoin()
{
}

void CCoin::Init()
{
	m_pCoinImage = RESOURCE->LoadImg(L"Coin", L"Image\\CoinImage.png");


	m_pAnimatorCoin = new CAnimator;
	m_pAnimatorCoin->CreateAnimation(L"Coin", m_pCoinImage, Vector(0, 0), Vector(59, 61), Vector(59, 0.f), 0.1f, 5);

	m_pAnimatorCoin->Play(L"Coin", false);
	AddComponent(m_pAnimatorCoin);

	AddCollider(ColliderType::Rect, Vector(70, 70), Vector(0, 0));

}

void CCoin::Update()
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

	CoinImage = L"Coin";

	AnimatorUpdate();
}

void CCoin::Render()
{


}

void CCoin::Release()
{
}

void CCoin::AnimatorUpdate()
{
	//m_pAnimators->Play(obstacleImage, false);
	m_pAnimatorCoin->Play(CoinImage, false);
}


void CCoin::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"플레이어가 코인을 먹었습니다.");
		CJellyEatEffect* pJellyEffect = new CJellyEatEffect();
		pJellyEffect->SetPos(m_vecPos.x - 10, m_vecPos.y);
		ADDOBJECT(pJellyEffect);
		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"펫미사일" && skillOn == true)
	{
		Logger::Debug(L"왕 하프물범이 코인을 먹었습니다.");
		CJellyEatEffect* pJellyEffect = new CJellyEatEffect();
		pJellyEffect->SetPos(m_vecPos.x - 10, m_vecPos.y);
		ADDOBJECT(pJellyEffect);
		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"펫미사일2")
	{
		Logger::Debug(L"물보라가 코인을 먹었습니다.");
		CJellyEatEffect* pJellyEffect = new CJellyEatEffect();
		pJellyEffect->SetPos(m_vecPos.x - 10, m_vecPos.y);
		ADDOBJECT(pJellyEffect);
		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"펫미사일3")
	{
		Logger::Debug(L"빛의 우유 방패가 코인을 먹었습니다");
		CJellyEatEffect* pJellyEffect = new CJellyEatEffect();
		pJellyEffect->SetPos(m_vecPos.x - 10, m_vecPos.y);
		ADDOBJECT(pJellyEffect);
		DELETEOBJECT(this);
	}
}

void CCoin::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CCoin::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CCoin::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CCoin::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
