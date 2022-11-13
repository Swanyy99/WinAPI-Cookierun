#include "framework.h"
#include "CPetMissile2.h"

extern float playerPosX;
extern float playerPosY;

extern bool isMagnet;
extern bool isDash;

extern bool skillOn;
extern int score;
extern float playerHp;

CPetMissile2::CPetMissile2()
{
	m_vecScale = Vector(10, 10);
	m_strName = L"Æê¹Ì»çÀÏ2";
	m_layer = Layer::PetMissile;
	m_vecDir = Vector(1, 0);
	m_fVelocity = 300;
	m_pAnimatorPetMissile2 = nullptr;
	m_pPetMissile2Image = nullptr;
	m_fWaterTimer = 0;

}

CPetMissile2::~CPetMissile2()
{
}

void CPetMissile2::Init()
{
	m_pPetMissile2Image = RESOURCE->LoadImg(L"PetMissiles2", L"Image\\Pet2SkillImage.png");


	m_pAnimatorPetMissile2 = new CAnimator;
	m_pAnimatorPetMissile2->CreateAnimation(L"PetMissile2", m_pPetMissile2Image, Vector(0, 0), Vector(351, 404), Vector(351, 0.f), 0.1f, 8);

	m_pAnimatorPetMissile2->Play(L"PetMissile2", false);
	AddComponent(m_pAnimatorPetMissile2);

	AddCollider(ColliderType::Rect, Vector(340, 400), Vector(0, 0));
	PetMissile2Image = L"PetMissile2";


}

void CPetMissile2::Update()
{

	m_vecPos -= m_vecDir * m_fVelocity * DT;

	m_fWaterTimer += ABSDT;

	if (m_fWaterTimer > 0.8)
	{
		DELETEOBJECT(this);
	}


	AnimatorUpdate();
}

void CPetMissile2::Render()
{


}

void CPetMissile2::Release()
{
}

void CPetMissile2::AnimatorUpdate()
{
	//m_pAnimators->Play(obstacleImage, false);
	m_pAnimatorPetMissile2->Play(PetMissile2Image, false);
}


void CPetMissile2::OnCollisionEnter(CCollider* pOtherCollider)
{

	if (pOtherCollider->GetObjName() == L"Àå¾Ö¹°")
	{
		score += 2000;
	}

	if (pOtherCollider->GetObjName() == L"Á©¸®")
	{
		score += 2000;
	}

}

void CPetMissile2::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CPetMissile2::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CPetMissile2::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CPetMissile2::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
