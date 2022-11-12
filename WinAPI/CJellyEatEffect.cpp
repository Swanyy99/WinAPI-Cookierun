#include "framework.h"
#include "CJellyEatEffect.h"

extern bool isMagnet;
extern bool isDash;

extern float playerPosX;
extern float playerPosY;

CJellyEatEffect::CJellyEatEffect()
{
	m_vecScale = Vector(10, 10);
	m_strName = L"Á©¸® ¸ÔÀº ÀÌÆåÆ®";
	m_layer = Layer::JellyEatEffect;
	m_vecDir = Vector(1, 0);
	m_fVelocity = 300;
	m_pAnimatorJellyEatEffect = nullptr;
	m_pJellyEatEffect = nullptr;

}

CJellyEatEffect::~CJellyEatEffect()
{
}

void CJellyEatEffect::Init()
{
	m_pJellyEatEffect = RESOURCE->LoadImg(L"JellyEatEffects", L"Image\\JellyEatEffect.png");


	m_pAnimatorJellyEatEffect = new CAnimator;
	m_pAnimatorJellyEatEffect->CreateAnimation(L"JellyEatEffect", m_pJellyEatEffect, Vector(0, 0), Vector(301, 287), Vector(301, 0), 0.05f, 7, false);

	m_pAnimatorJellyEatEffect->Play(L"JellyEatEffect", false);
	AddComponent(m_pAnimatorJellyEatEffect);


}

void CJellyEatEffect::Update()
{

	m_vecPos -= m_vecDir * m_fVelocity * DT;


	effectTimer += ABSDT;

	if (effectTimer > 0.35)
		DELETEOBJECT(this);

	JellyEatEffect = L"JellyEatEffect";

	AnimatorUpdate();
}

void CJellyEatEffect::Render()
{


}

void CJellyEatEffect::Release()
{
}

void CJellyEatEffect::AnimatorUpdate()
{
	//m_pAnimators->Play(obstacleImage, false);
	m_pAnimatorJellyEatEffect->Play(JellyEatEffect, false);
}


void CJellyEatEffect::OnCollisionEnter(CCollider* pOtherCollider)
{

}

void CJellyEatEffect::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CJellyEatEffect::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CJellyEatEffect::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CJellyEatEffect::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
