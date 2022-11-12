#include "framework.h"
#include "CPetMissile.h"

extern float playerPosX;
extern float playerPosY;

extern bool isMagnet;
extern bool isDash;

extern bool skillOn;
extern int score;

CPetMissile::CPetMissile()
{
	m_vecScale = Vector(10, 10);
	m_strName = L"Æê¹Ì»çÀÏ";
	m_layer = Layer::PetMissile;
	m_vecDir = Vector(1, 0);
	m_fVelocity = 300;
	m_pAnimatorPetMissile = nullptr;
	m_pPetMissileImage = nullptr;



}

CPetMissile::~CPetMissile()
{
}

void CPetMissile::Init()
{
	m_pPetMissileImage = RESOURCE->LoadImg(L"PetMissiles", L"Image\\PetMissileImage.png");


	m_pAnimatorPetMissile = new CAnimator;
	m_pAnimatorPetMissile->CreateAnimation(L"PetMissile", m_pPetMissileImage, Vector(0, 1920), Vector(320, 319), Vector(320, 0.f), 0.08f, 4);

	m_pAnimatorPetMissile->Play(L"PetMissile", false);
	AddComponent(m_pAnimatorPetMissile);

	AddCollider(ColliderType::Rect, Vector(150, 150), Vector(0, 0));
	PetMissileImage = L"PetMissile";


}

void CPetMissile::Update()
{

	m_vecPos += m_vecDir * m_fVelocity * ABSDT;



	if (m_vecPos.x >= 1400)
		DELETEOBJECT(this);


	AnimatorUpdate();
}

void CPetMissile::Render()
{


}

void CPetMissile::Release()
{
}

void CPetMissile::AnimatorUpdate()
{
	//m_pAnimators->Play(obstacleImage, false);
	m_pAnimatorPetMissile->Play(PetMissileImage, false);
}


void CPetMissile::OnCollisionEnter(CCollider* pOtherCollider)
{
	
	if (pOtherCollider->GetObjName() == L"Àå¾Ö¹°" && skillOn == true)
	{
		score += 2000;
	}

	if (pOtherCollider->GetObjName() == L"Á©¸®" && skillOn == true)
	{
		Logger::Debug(L"¿Õ ÇÏÇÁ¹°¹üÀÌ Á©¸®¸¦ ¸Ô¾ú½À´Ï´Ù!");
		score += 2000;
	}

}

void CPetMissile::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CPetMissile::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CPetMissile::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CPetMissile::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
