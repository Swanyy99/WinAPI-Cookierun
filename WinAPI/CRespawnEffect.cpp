#include "framework.h"
#include "CRespawnEffect.h"
#include "framework.h"
#include "CJellyEatEffect.h"

extern bool isMagnet;
extern bool isDash;

extern float playerPosX;
extern float playerPosY;

CRespawnEffect::CRespawnEffect()
{
	m_vecScale = Vector(10, 10);
	m_strName = L"리스폰 이펙트";
	m_layer = Layer::RespawnEffect;
	m_vecDir = Vector(1, 0);
	m_fVelocity = 300;
	m_pAnimatorRespawnEffect = nullptr;
	m_pRespawnEffect = nullptr;

}

CRespawnEffect::~CRespawnEffect()
{
}

void CRespawnEffect::Init()
{
	m_pRespawnEffect = RESOURCE->LoadImg(L"RespawnEffects", L"Image\\Respawn.png");


	m_pAnimatorRespawnEffect = new CAnimator;
	m_pAnimatorRespawnEffect->CreateAnimation(L"RespawnEffect", m_pRespawnEffect, Vector(0, 0), Vector(344, 222), Vector(344, 0), 0.04f, 7, false);

	m_pAnimatorRespawnEffect->Play(L"RespawnEffect", false);
	AddComponent(m_pAnimatorRespawnEffect);


}

void CRespawnEffect::Update()
{

	m_vecPos -= m_vecDir * m_fVelocity * DT;


	effectTimer += ABSDT;

	if (effectTimer > 0.28)
		DELETEOBJECT(this);

	RespawnEffect = L"RespawnEffect";

	AnimatorUpdate();
}

void CRespawnEffect::Render()
{


}

void CRespawnEffect::Release()
{
}

void CRespawnEffect::AnimatorUpdate()
{
	//m_pAnimators->Play(obstacleImage, false);
	m_pAnimatorRespawnEffect->Play(RespawnEffect, false);
}


void CRespawnEffect::OnCollisionEnter(CCollider* pOtherCollider)
{

}

void CRespawnEffect::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CRespawnEffect::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CRespawnEffect::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CRespawnEffect::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
