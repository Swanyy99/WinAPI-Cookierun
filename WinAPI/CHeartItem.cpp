#include "framework.h"
#include "CHeartItem.h"

extern bool isMagnet;
extern bool isDash;

extern float playerPosX;
extern float playerPosY;

CHeartItem::CHeartItem()
{
	m_vecScale = Vector(1000, 1000);
	m_strName = L"하트아이템";
	m_layer = Layer::HeartItem;
	m_vecDir = Vector(1, 0);
	m_fVelocity = 300;
	m_pAnimatorHeartItem = nullptr;
	m_pHeartItemImage = nullptr;

}

CHeartItem::~CHeartItem()
{
}

void CHeartItem::Init()
{
	m_pHeartItemImage = RESOURCE->LoadImg(L"HeartItem", L"Image\\HeartItem.png");


	m_pAnimatorHeartItem = new CAnimator;
	m_pAnimatorHeartItem->CreateAnimation(L"HeartItem", m_pHeartItemImage, Vector(0, 0), Vector(89, 89), Vector(89, 0), 0.2f, 4);

	m_pAnimatorHeartItem->Play(L"HeartItem", false);
	AddComponent(m_pAnimatorHeartItem);

	AddCollider(ColliderType::Rect, Vector(80, 80), Vector(0, 0));

}

void CHeartItem::Update()
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

	HeartItemImage = L"HeartItem";

	AnimatorUpdate();
}

void CHeartItem::Render()
{


}

void CHeartItem::Release()
{
}

void CHeartItem::AnimatorUpdate()
{
	//m_pAnimators->Play(obstacleImage, false);
	m_pAnimatorHeartItem->Play(HeartItemImage, false);
}


void CHeartItem::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"플레이어가 생명물약을 먹었습니다.");
		DELETEOBJECT(this);
	}
}

void CHeartItem::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CHeartItem::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CHeartItem::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CHeartItem::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
