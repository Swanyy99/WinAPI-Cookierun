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
extern bool pause;

CPet::CPet()
{
	m_vecPos = Vector(playerPosX - 150, playerPosY);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Pet;
	m_strName = L"펫";

	m_pPetImage = nullptr;
	m_pSkillImage = nullptr;

	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_fSkillTimer = 0;
	m_fSkillCooltimeTimer = 0;
	skillOn = false;

}

CPet::~CPet()
{
}

void CPet::Init()
{
	CPetMissile* pPetMissile1 = new CPetMissile();
	pPetMissile1->SetPos(-200, WINSIZEY * 0.7);
	ADDOBJECT(pPetMissile1);
	DELETEOBJECT(pPetMissile1);

	m_pAnimatorp = new CAnimator;

	// 기본 쿠키 모션 이미지들
	m_pPetImage = RESOURCE->LoadImg(L"PetAnimation", L"Image\\Pet.png");
	m_pDeathImage = RESOURCE->LoadImg(L"PetDeath", L"Image\\Pet.png");

	m_pAnimatorp->CreateAnimation(L"IdleRun", m_pPetImage, Vector(0, 0), Vector(100, 100), Vector(100, 0.f), 0.1f, 4);

	m_pAnimatorp->CreateAnimation(L"Skill", m_pPetImage, Vector(100, 300), Vector(100, 100), Vector(100, 0.f), 0.1f, 7);

	m_pAnimatorp->CreateAnimation(L"Death", m_pPetImage, Vector(0, 942), Vector(100, 100), Vector(100, 0.f), 0.1f, 1, false);

	m_pAnimatorp->Play(L"IdleRun", false);
	AddComponent(m_pAnimatorp);


	petState = PetState::IdleRun;

	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, 0));


	m_fSkillTimer = 6;			// 펫 스킬 지속시간
	m_fSkillCooltimeTimer = 12;		// 펫 스킬 쿨타임
	skillOn = false;
	PetMotion = L"IdleRun";

	

}


void CPet::Update()
{

	m_fSkillCooltimeTimer -= ABSDT;

	// 스킬 발동
	if (m_fSkillCooltimeTimer <= 0)
	{
		CPetMissile* pPetMissile1 = new CPetMissile();
		pPetMissile1->SetPos(-200, WINSIZEY * 0.7);
		ADDOBJECT(pPetMissile1);

		CPetMissile* pPetMissile2 = new CPetMissile();
		pPetMissile2->SetPos(-400, WINSIZEY * 0.7);
		ADDOBJECT(pPetMissile2);

		m_fSkillCooltimeTimer = 18;	// 스킬 쿨은 쿨타임 + 지속 시간 으로 다시 초기화
		skillOn = true;

		CSound* pSound = RESOURCE->LoadSound(L"Pet1SkillOn", L"Sound\\Pet1SkillOn.wav");
		SOUND->Play(pSound, 0.15f, false);
	}
	

	// 스킬 발동 시
	if (skillOn == true)
	{
		PetMotion = L"Skill";
		m_fSkillTimer -= ABSDT;

		m_vecPos.y -= (m_vecPos.y - (playerPosY - 100)) * DT * 3.5;
		m_vecPos.x -= (m_vecPos.x - (playerPosX + 180)) * DT * 3;

		if (m_fSkillTimer <= 0)
		{
			skillOn = false;
			m_fSkillTimer = 6;
			PetMotion = L"IdleRun";
		}
	}

	// 스킬 쿨타임 중
	else if (skillOn == false)
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

	m_pAnimatorp->Play(PetMotion, false);

}

void CPet::OnCollisionEnter(CCollider* pOtherCollider)
{


}

void CPet::OnCollisionStay(CCollider* pOtherCollider)
{


}

void CPet::OnCollisionExit(CCollider* pOtherCollider)
{
}
