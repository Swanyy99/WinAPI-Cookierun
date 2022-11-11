#include "framework.h"
#include "CPet.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"

#include "CMissile.h"
#include "CGameObject.h"
#include "CDashFireEffect.h"
#include "CScene.h"
#include "CPetMissile.h"

bool skillOn;
wstring PetMotion;

extern bool isDead;
extern bool isMagnet;
extern bool isDash;
extern float playerHp;

extern float playerPosX;
extern float playerPosY;

extern int score;
extern wstring ScreenScore;
extern bool pause;

CPet::CPet()
{
	m_vecPos = Vector(playerPosX - 150, playerPosY);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Player;
	m_strName = L"∆Í";

	m_pPetImage = nullptr;
	m_pSkillImage = nullptr;

	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_fSkillTimer = 0;
	m_fSkillCooltimeTimer = 0;
	SkillUsed = false;
	skillOn = false;

}

CPet::~CPet()
{
}

void CPet::Init()
{
	m_pAnimator = new CAnimator;

	// ±‚∫ª ƒÌ≈∞ ∏º« ¿ÃπÃ¡ˆµÈ
	m_pPetImage = RESOURCE->LoadImg(L"PetrAnimation", L"Image\\Pet.png");
	m_pDeathImage = RESOURCE->LoadImg(L"PlayerDeath", L"Image\\Pet.png");

	m_pAnimator->CreateAnimation(L"IdleRun", m_pPetImage, Vector(0, 0), Vector(100, 100), Vector(100, 0.f), 0.1f, 4);

	m_pAnimator->CreateAnimation(L"Skill", m_pPetImage, Vector(100, 300), Vector(100, 100), Vector(100, 0.f), 0.1f, 7);

	m_pAnimator->CreateAnimation(L"Death", m_pPetImage, Vector(0, 942), Vector(100, 100), Vector(100, 0.f), 0.1f, 1, false);

	m_pAnimator->Play(L"IdleRun", false);
	AddComponent(m_pAnimator);


	petState = PetState::IdleRun;

	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, 0));

	m_fSkillTimer = 5;
	m_fSkillCooltimeTimer = 10;
	SkillUsed = false;
	skillOn = false;
	PetMotion = L"IdleRun";
}

void CPet::Update()
{

	m_fSkillCooltimeTimer -= ABSDT;

	if (m_fSkillCooltimeTimer <= 0)
	{
		skillOn = true;
	}
	

	//Ω∫≈≥ πﬂµø
	if (skillOn == true && isDead == false)
	{
		m_fSkillTimer -= ABSDT;
		PetMotion = L"Skill";

		m_vecPos.y -= (m_vecPos.y - (playerPosY - 100)) * DT * 3.5;
		m_vecPos.x -= (m_vecPos.x - (playerPosX + 180)) * DT * 3;

		if (SkillUsed == false)
		{
			SkillUsed = true;

			CPetMissile* pPetMissile = new CPetMissile();
			pPetMissile->SetPos(-200, WINSIZEY * 0.7);
			ADDOBJECT(pPetMissile);

			CPetMissile* pPetMissile2 = new CPetMissile();
			pPetMissile2->SetPos(-400, WINSIZEY * 0.7);
			ADDOBJECT(pPetMissile2);

			CPetMissile* pPetMissile3 = new CPetMissile();
			pPetMissile3->SetPos(-600, WINSIZEY * 0.7);
			ADDOBJECT(pPetMissile3);

			
		}
		if (m_fSkillTimer <= 0)
		{
			skillOn = false;
			SkillUsed = false;
			m_fSkillCooltimeTimer = 10;
			m_fSkillTimer = 5;
			PetMotion = L"IdleRun";
		}
	}

	// Ω∫≈≥ ƒ≈∏¿” ¡ﬂ
	if (skillOn == false)
		m_vecPos.y -= (m_vecPos.y - (playerPosY - 70)) * DT * 3.5;
		m_vecPos.x -= (m_vecPos.x - (playerPosX - 170)) * DT * 3;

	AnimatorUpdate();
}

void CPet::Render()
{

}

void CPet::Release()
{
}

void CPet::AnimatorUpdate()
{

	m_pAnimator->Play(PetMotion, false);

}

void CPet::OnCollisionEnter(CCollider* pOtherCollider)
{

	/*if (pOtherCollider->GetObjName() == L"¿Âæ÷π∞")
	{
		Logger::Debug(L"¿Âæ÷π∞ ∆ƒ±´!");
		score += 1000;
	}

	if (pOtherCollider->GetObjName() == L"¡©∏Æ")
	{
		Logger::Debug(L"¡©∏Æ ¡°ºˆ »πµÊ!");
		score += 1000;
	}

	if (pOtherCollider->GetObjName() == L"«œ∆Ææ∆¿Ã≈€")
	{
		Logger::Debug(L"ª˝∏Ìπ∞æ‡ »πµÊ!");
		playerHp += 20;
	}


	if (pOtherCollider->GetObjName() == L"¿⁄ºÆæ∆¿Ã≈€")
	{
		Logger::Debug(L"¿⁄ºÆæ∆¿Ã≈€ »πµÊ!");
		isMagnet = true;
	}

	if (pOtherCollider->GetObjName() == L"¥ÎΩ¨æ∆¿Ã≈€")
	{
		Logger::Debug(L"¥ÎΩ¨æ∆¿Ã≈€ »πµÊ!");
		isDash = true;
	}*/

}

void CPet::OnCollisionStay(CCollider* pOtherCollider)
{


}

void CPet::OnCollisionExit(CCollider* pOtherCollider)
{
}
