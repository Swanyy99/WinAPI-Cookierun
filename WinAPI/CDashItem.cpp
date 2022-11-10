#include "framework.h"
#include "CDashItem.h"
#include "CDashFireEffect.h"

extern bool isMagnet;
extern bool isDash;

extern float playerPosX;
extern float playerPosY;

CDashItem::CDashItem()
{
	m_vecScale = Vector(1000, 1000);
	m_strName = L"대쉬아이템";
	m_layer = Layer::DashItem;
	m_vecDir = Vector(1, 0);
	m_fVelocity = 300;
	m_pAnimatorDashItem = nullptr;
	m_pDashItemImage = nullptr;

}

CDashItem::~CDashItem()
{
}

void CDashItem::Init()
{
	m_pDashItemImage = RESOURCE->LoadImg(L"DashItem", L"Image\\DashItem.png");


	m_pAnimatorDashItem = new CAnimator;
	m_pAnimatorDashItem->CreateAnimation(L"DashItem", m_pDashItemImage, Vector(0, 0), Vector(71, 72), Vector(71, 0), 0.2f, 4);

	m_pAnimatorDashItem->Play(L"DashItem", false);
	AddComponent(m_pAnimatorDashItem);

	AddCollider(ColliderType::Rect, Vector(60, 60), Vector(0, 0));

}

void CDashItem::Update()
{


	m_vecPos -= m_vecDir * m_fVelocity * DT;



	if (isMagnet == true)
	{
		if (abs(m_vecPos.x - playerPosX) < 200 && abs(m_vecPos.y - playerPosY) < 200)
		{

			m_vecPos.x -= (m_vecPos.x - playerPosX) * DT * 3.5;
			m_vecPos.y -= (m_vecPos.y - playerPosY) * DT * 3.5;

		}
	}

	if (m_vecPos.x < -100)
		DELETEOBJECT(this);

	DashItemImage = L"DashItem";

	AnimatorUpdate();
}

void CDashItem::Render()
{


}

void CDashItem::Release()
{
}

void CDashItem::AnimatorUpdate()
{
	//m_pAnimators->Play(obstacleImage, false);
	m_pAnimatorDashItem->Play(DashItemImage, false);
}


void CDashItem::OnCollisionEnter(CCollider* pOtherCollider)
{
	

	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"플레이어가 대쉬 아이템을 먹었습니다.");
		DELETEOBJECT(this);
	}
}

void CDashItem::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CDashItem::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CDashItem::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CDashItem::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
