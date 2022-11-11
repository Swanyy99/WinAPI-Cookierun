#include "framework.h"
#include "CObstacleBoomEffect.h"


extern bool isMagnet;
extern bool isDash;

extern float playerPosX;
extern float playerPosY;

CObstacleBoomEffect::CObstacleBoomEffect()
{
	m_vecScale = Vector(10, 10);
	m_strName = L"Àå¾Ö¹° ÆøÆÄ ÀÌÆåÆ®";
	m_layer = Layer::ObstacleBoomEffect;
	m_vecDir = Vector(1, 0);
	m_fVelocity = 300;
	m_pAnimatorObstacleBoomEffect = nullptr;
	m_pObstacleBoomEffect = nullptr;

}

CObstacleBoomEffect::~CObstacleBoomEffect()
{
}

void CObstacleBoomEffect::Init()
{
	m_pObstacleBoomEffect = RESOURCE->LoadImg(L"ObstacleBoomEffects", L"Image\\ObstacleBoomImage2.png");


	m_pAnimatorObstacleBoomEffect = new CAnimator;
	m_pAnimatorObstacleBoomEffect->CreateAnimation(L"ObstacleBoomEffect", m_pObstacleBoomEffect, Vector(0, 0), Vector(225, 231), Vector(225, 0), 0.1f, 7, false);

	m_pAnimatorObstacleBoomEffect->Play(L"ObstacleBoomEffect", false);
	AddComponent(m_pAnimatorObstacleBoomEffect);


}

void CObstacleBoomEffect::Update()
{

	m_vecPos -= m_vecDir * m_fVelocity * DT;


	effectTimer += ABSDT;

	if (effectTimer > 0.5)
		DELETEOBJECT(this);

	ObstacleBoomEffect = L"ObstacleBoomEffect";

	AnimatorUpdate();
}

void CObstacleBoomEffect::Render()
{


}

void CObstacleBoomEffect::Release()
{
}

void CObstacleBoomEffect::AnimatorUpdate()
{
	//m_pAnimators->Play(obstacleImage, false);
	m_pAnimatorObstacleBoomEffect->Play(ObstacleBoomEffect, false);
}


void CObstacleBoomEffect::OnCollisionEnter(CCollider* pOtherCollider)
{

}

void CObstacleBoomEffect::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CObstacleBoomEffect::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CObstacleBoomEffect::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CObstacleBoomEffect::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
