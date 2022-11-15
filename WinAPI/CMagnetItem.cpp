#include "framework.h"
#include "CMagnetItem.h"
#include "CJellyEatEffect.h"

extern bool isMagnet;
extern bool isDash;

extern float playerPosX;
extern float playerPosY;

CMagnetItem::CMagnetItem()
{
	m_vecScale = Vector(1000, 1000);
	m_strName = L"자석아이템";
	m_layer = Layer::MagnetItem;
	m_vecDir = Vector(1, 0);
	m_fVelocity = 300;
	m_pAnimatorMagnetItem = nullptr;
	m_pMagnetItemImage = nullptr;

}

CMagnetItem::~CMagnetItem()
{
}

void CMagnetItem::Init()
{
	m_pMagnetItemImage = RESOURCE->LoadImg(L"MagnetItem", L"Image\\MagnetItem.png");


	m_pAnimatorMagnetItem = new CAnimator;
	m_pAnimatorMagnetItem->CreateAnimation(L"MagnetItem", m_pMagnetItemImage, Vector(0, 0), Vector(61, 61), Vector(61, 0), 0.2f, 4);

	m_pAnimatorMagnetItem->Play(L"MagnetItem", false);
	AddComponent(m_pAnimatorMagnetItem);

	AddCollider(ColliderType::Rect, Vector(60, 60), Vector(0, 0));

}

void CMagnetItem::Update()
{

	m_vecPos -= m_vecDir * m_fVelocity * DT;

	if (isMagnet == true)
	{
		if (abs(m_vecPos.x - playerPosX) < 250 && abs(m_vecPos.y - playerPosY) < 250)
		{

			m_vecPos.x -= (m_vecPos.x - playerPosX) * DT * 3;
			m_vecPos.y -= (m_vecPos.y - playerPosY) * DT * 3;

		}
	}

	if (m_vecPos.x < -100)
		DELETEOBJECT(this);

	MagnetItemImage = L"MagnetItem";

	AnimatorUpdate();
}

void CMagnetItem::Render()
{


}

void CMagnetItem::Release()
{
}

void CMagnetItem::AnimatorUpdate()
{
	//m_pAnimators->Play(obstacleImage, false);
	m_pAnimatorMagnetItem->Play(MagnetItemImage, false);
}


void CMagnetItem::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"플레이어가 자석 아이템을 먹었습니다.");
		CJellyEatEffect* pJellyEffect = new CJellyEatEffect();
		pJellyEffect->SetPos(m_vecPos.x - 10, m_vecPos.y);
		ADDOBJECT(pJellyEffect);
		DELETEOBJECT(this);
	}


}

void CMagnetItem::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CMagnetItem::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CMagnetItem::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CMagnetItem::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
