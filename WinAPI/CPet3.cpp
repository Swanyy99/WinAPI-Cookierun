#include "framework.h"
#include "CPet3.h"

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
#include "CPetMissile3.h"

bool skillOn3;
wstring PetMotion3;

extern bool isDead;
extern bool isMagnet;
extern bool isDash;
extern bool isHurt;
extern float playerHp;

extern float playerPosX;
extern float playerPosY;
extern float m_fDashTimer;
extern float m_fHurtTimer;

extern int score;
extern bool pause;

float Pet3PosX;
float Pet3PosY;

CPet3::CPet3()
{
	m_vecPos = Vector(playerPosX - 150, playerPosY);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Pet;
	m_strName = L"펫3";

	m_pPetImage3 = nullptr;
	m_pSkillImage = nullptr;

	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_fSkillTimer = 7;
	m_fSkillCooltimeTimer = 13;
	m_fSkillTicTimer = 0;
	skillOn3 = false;

	skillNum = 0;

}

CPet3::~CPet3()
{
}

void CPet3::Init()
{
	CPetMissile3* pPetMissile3 = new CPetMissile3();
	pPetMissile3->SetPos(-300, WINSIZEY * 0.7);
	ADDOBJECT(pPetMissile3);
	DELETEOBJECT(pPetMissile3);

	m_pAnimatorp3 = new CAnimator;

	// 기본 쿠키 모션 이미지들
	m_pPetImage3 = RESOURCE->LoadImg(L"Pet3Animation", L"Image\\Pet3.png");

	m_pAnimatorp3->CreateAnimation(L"Pet3IdleRun", m_pPetImage3, Vector(0, 0), Vector(119, 119), Vector(119, 0.f), 0.1f, 4);

	m_pAnimatorp3->CreateAnimation(L"PetSkill3", m_pPetImage3, Vector(476, 0), Vector(119, 119), Vector(119, 0.f), 0.1f, 4);

	m_pAnimatorp3->Play(L"Pet3IdleRun", false);
	AddComponent(m_pAnimatorp3);


	petState = PetState::IdleRun;

	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, 0));


	m_fSkillTimer = 7;			// 펫 스킬 지속시간
	m_fSkillCooltimeTimer = 13;		// 펫 스킬 쿨타임
	skillOn3 = false;
	PetMotion3 = L"Pet3IdleRun";



}


void CPet3::Update()
{
	Pet3PosX = m_vecPos.x;
	Pet3PosY = m_vecPos.y;

	m_fSkillCooltimeTimer -= ABSDT;
	// 스킬 발동
	if (m_fSkillCooltimeTimer <= 0)
	{

		m_fSkillTicTimer += ABSDT;
		CPetMissile3* pPetMissile3 = new CPetMissile3();
		pPetMissile3->SetPos(playerPosX + 130, 300);
		ADDOBJECT(pPetMissile3);
		skillOn3 = true;
		isHurt = false;
		isDash = false;
		m_fDashTimer = 4;
		m_fSkillTimer = 7;
		m_fSkillCooltimeTimer = 20;	// 스킬 쿨은 쿨타임 + 지속 시간 으로 다시 초기화
		


	}

	// 스킬 발동 시
	if (skillOn3 == true)
	{
		PetMotion3 = L"PetSkill3";
		m_fSkillTimer -= ABSDT;

		if (m_fSkillTimer > 4)
		{
		m_fDashTimer = 3.9;
		isDash = true;
		}

		m_vecPos.y -= (m_vecPos.y - (playerPosY - 85)) * DT * 3.5;
		m_vecPos.x -= (m_vecPos.x - (playerPosX + 300)) * DT * 3;


		if (m_fSkillTimer <= 0)
		{
			skillNum = 0;
			isHurt = true;
			m_fHurtTimer = 2.5;
			skillOn3 = false;
			PetMotion3 = L"Pet3IdleRun";
		}
	}

	// 스킬 쿨타임 중
	else if (skillOn3 == false)
		m_vecPos.y -= (m_vecPos.y - (playerPosY - 70)) * DT * 3.5;
		m_vecPos.x -= (m_vecPos.x - (playerPosX - 170)) * DT * 3;

	AnimatorUpdate();
}

void CPet3::Render()
{

}

void CPet3::Release()
{
}

void CPet3::AnimatorUpdate()
{

	m_pAnimatorp3->Play(PetMotion3, false);

}

void CPet3::OnCollisionEnter(CCollider* pOtherCollider)
{


}

void CPet3::OnCollisionStay(CCollider* pOtherCollider)
{


}

void CPet3::OnCollisionExit(CCollider* pOtherCollider)
{
}
