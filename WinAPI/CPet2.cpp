#include "framework.h"
#include "CPet2.h"

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
#include "CPetMissile2.h"

bool skillOn2;
wstring PetMotion2;

extern bool isDead;
extern bool isMagnet;
extern bool isDash;
extern float playerHp;

extern float playerPosX;
extern float playerPosY;

extern int score;
extern bool pause;

CPet2::CPet2()
{
	m_vecPos = Vector(playerPosX - 150, playerPosY);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Pet;
	m_strName = L"펫2";

	m_pPetImage2 = nullptr;
	m_pSkillImage = nullptr;

	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_fSkillTimer = 0;
	m_fSkillCooltimeTimer = 0;
	m_fSkillTicTimer = 0;
	skillOn2 = false;

	skillNum = 0;

}

CPet2::~CPet2()
{
}

void CPet2::Init()
{
	CPetMissile2* pPetMissile2 = new CPetMissile2();
	pPetMissile2->SetPos(-300, WINSIZEY * 0.7);
	ADDOBJECT(pPetMissile2);
	DELETEOBJECT(pPetMissile2);

	m_pAnimatorp2 = new CAnimator;

	// 기본 쿠키 모션 이미지들
	m_pPetImage2 = RESOURCE->LoadImg(L"Pet2Animation", L"Image\\Pet2.png");

	m_pAnimatorp2->CreateAnimation(L"Pet2IdleRun", m_pPetImage2, Vector(0, 0), Vector(119, 120), Vector(119, 0.f), 0.1f, 4);

	m_pAnimatorp2->CreateAnimation(L"PetSkill2", m_pPetImage2, Vector(480, 0), Vector(119, 120), Vector(119, 0.f), 0.1f, 4);

	m_pAnimatorp2->Play(L"Pet2IdleRun", false);
	AddComponent(m_pAnimatorp2);


	petState = PetState::IdleRun;

	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, 0));


	m_fSkillTimer = 1.55;			// 펫 스킬 지속시간
	m_fSkillCooltimeTimer = 7.5;		// 펫 스킬 쿨타임
	skillOn2 = false;
	PetMotion2 = L"Pet2IdleRun";



}


void CPet2::Update()
{
	m_fSkillCooltimeTimer -= ABSDT;
	// 스킬 발동
	if (m_fSkillCooltimeTimer <= 0)
	{

		m_fSkillTicTimer += ABSDT;

		if (m_fSkillTicTimer >= 0.25 && skillNum == 0)
		{
			skillOn2 = true;
			skillNum += 1;
			playerHp += 5;
			CPetMissile2* pPetMissile1 = new CPetMissile2();
			pPetMissile1->SetPos(WINSIZEX * 0.55, WINSIZEY * 0.58);
			ADDOBJECT(pPetMissile1);
			m_fSkillTicTimer -= 0.25;
		}

		if (m_fSkillTicTimer >= 0.25 && skillNum == 1)
		{
			skillNum += 1;
			CPetMissile2* pPetMissile2 = new CPetMissile2();
			pPetMissile2->SetPos(WINSIZEX * 0.75, WINSIZEY * 0.58);
			ADDOBJECT(pPetMissile2);
			m_fSkillTicTimer -= 0.25;
		}

		if (m_fSkillTicTimer >= 0.25 && skillNum == 2)
		{
			CPetMissile2* pPetMissile3 = new CPetMissile2();
			pPetMissile3->SetPos(WINSIZEX * 0.95, WINSIZEY * 0.58);
			ADDOBJECT(pPetMissile3);
			skillNum = 0;
			m_fSkillCooltimeTimer = 6.8;	// 스킬 쿨은 쿨타임 + 지속 시간 으로 다시 초기화
		}


	}

	// 스킬 발동 시
	if (skillOn2 == true)
	{
		PetMotion2 = L"PetSkill2";
		m_fSkillTimer -= ABSDT;

		m_vecPos.y -= (m_vecPos.y - (playerPosY - 70)) * DT * 3.5;
		m_vecPos.x -= (m_vecPos.x - (playerPosX - 170)) * DT * 3;

		if (m_fSkillTimer <= 0)
		{
			skillOn2 = false;
			m_fSkillTimer = 1.55;
			PetMotion2 = L"Pet2IdleRun";
		}
	}

	// 스킬 쿨타임 중
	else if (skillOn2 == false)
		m_vecPos.y -= (m_vecPos.y - (playerPosY - 70)) * DT * 3.5;
		m_vecPos.x -= (m_vecPos.x - (playerPosX - 170)) * DT * 3;

	AnimatorUpdate();
}

void CPet2::Render()
{

}

void CPet2::Release()
{
}

void CPet2::AnimatorUpdate()
{

	m_pAnimatorp2->Play(PetMotion2, false);

}

void CPet2::OnCollisionEnter(CCollider* pOtherCollider)
{


}

void CPet2::OnCollisionStay(CCollider* pOtherCollider)
{


}

void CPet2::OnCollisionExit(CCollider* pOtherCollider)
{
}
