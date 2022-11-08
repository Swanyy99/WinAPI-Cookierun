#include "framework.h"
#include "CHeartItem.h"



CHeartItem::CHeartItem()
{
	m_vecScale = Vector(1000, 1000);
	m_strName = L"��Ʈ������";
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
	m_pAnimatorHeartItem->CreateAnimation(L"HeartItem", m_pHeartItemImage, Vector(0, 0), Vector(88, 89), Vector(88, 0), 0.2f, 4);

	m_pAnimatorHeartItem->Play(L"HeartItem", false);
	AddComponent(m_pAnimatorHeartItem);

	AddCollider(ColliderType::Rect, Vector(80, 80), Vector(0, 0));

}

void CHeartItem::Update()
{

	m_vecPos -= m_vecDir * m_fVelocity * DT;

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
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
	{
		Logger::Debug(L"�÷��̾ ���������� �Ծ����ϴ�.");
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