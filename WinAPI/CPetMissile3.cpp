#include "framework.h"
#include "CPetMissile3.h"

extern float playerPosX;
extern float playerPosY;

extern bool isMagnet;
extern bool isDash;

extern bool skillOn;
extern int score;
extern float playerHp;

extern float Pet3PosX;
extern float Pet3PosY;

CPetMissile3::CPetMissile3()
{
	m_vecScale = Vector(10, 10);
	m_strName = L"��̻���3";
	m_layer = Layer::PetMissileEatHp;
	m_vecDir = Vector(1, 0);
	m_fVelocity = 300;
	m_pAnimatorPetMissile3 = nullptr;
	m_pPetMissile3Image = nullptr;
	m_fShieldTimer = 0;

}

CPetMissile3::~CPetMissile3()
{
}

void CPetMissile3::Init()
{
	m_pPetMissile3Image = RESOURCE->LoadImg(L"PetMissiles3", L"Image\\Pet3SkillImage.png");


	m_pAnimatorPetMissile3 = new CAnimator;
	m_pAnimatorPetMissile3->CreateAnimation(L"PetMissile3Appear", m_pPetMissile3Image, Vector(0, 0), Vector(626, 507), Vector(626, 0.f), 0.08f, 7, false);
	m_pAnimatorPetMissile3->CreateAnimation(L"PetMissile3Ing", m_pPetMissile3Image, Vector(0, 507), Vector(626, 507), Vector(626, 0.f), 0.08f, 7);
	m_pAnimatorPetMissile3->CreateAnimation(L"PetMissile3Disappear", m_pPetMissile3Image, Vector(0, 1014), Vector(626, 507), Vector(626, 0.f), 0.08f, 5, false);

	m_pAnimatorPetMissile3->Play(L"PetMissile3Appear", false);
	AddComponent(m_pAnimatorPetMissile3);

	PetMissile3Image = L"PetMissile3Appear";


}

void CPetMissile3::Update()
{

	m_vecPos.x = Pet3PosX + 60;
	m_vecPos.y = Pet3PosY - 20;

	m_fShieldTimer += ABSDT;

	if (m_fShieldTimer > 0 && m_fShieldTimer < 0.56)
	{
		PetMissile3Image = L"PetMissile3Appear";
	}

	if (m_fShieldTimer > 0.56 && m_fShieldTimer < 6.7)
	{
		AddCollider(ColliderType::Rect, Vector(350, 450), Vector(0, 0));
		PetMissile3Image = L"PetMissile3Ing";
	}

	if (m_fShieldTimer > 6.8 && m_fShieldTimer < 7.2)
	{
		PetMissile3Image = L"PetMissile3Disappear";
	}

	if (m_fShieldTimer > 7.2)
		DELETEOBJECT(this);


	AnimatorUpdate();
}

void CPetMissile3::Render()
{


}

void CPetMissile3::Release()
{
}

void CPetMissile3::AnimatorUpdate()
{
	//m_pAnimators->Play(obstacleImage, false);
	m_pAnimatorPetMissile3->Play(PetMissile3Image, false);
}


void CPetMissile3::OnCollisionEnter(CCollider* pOtherCollider)
{

	if (pOtherCollider->GetObjName() == L"��ֹ�")
	{
		score += 2000;
	}

	if (pOtherCollider->GetObjName() == L"����")
	{
		score += 2000;
	}

	if (pOtherCollider->GetObjName() == L"��Ʈ������")
	{
		playerHp += 20;
	}

}

void CPetMissile3::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CPetMissile3::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CPetMissile3::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CPetMissile3::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
