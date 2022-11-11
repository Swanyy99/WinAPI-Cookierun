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
	m_strName = L"�÷��̾�";

	m_pPetImage = nullptr;
	m_pSkillImage = nullptr;

	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_bIsMove = false;
	isDead = false;
	m_fSkillTimer = 0.4;

}

CPet::~CPet()
{
}

void CPet::Init()
{
	m_pAnimator = new CAnimator;

	// �⺻ ��Ű ��� �̹�����
	m_pPetImage = RESOURCE->LoadImg(L"PetrAnimation", L"Image\\Pet.png");
	m_pDeathImage = RESOURCE->LoadImg(L"PlayerDeath", L"Image\\Pet.png");

	m_pAnimator->CreateAnimation(L"IdleRun", m_pPetImage, Vector(0, 0), Vector(100, 100), Vector(100, 0.f), 0.1f, 4);

	m_pAnimator->CreateAnimation(L"Death", m_pPetImage, Vector(0, 942), Vector(100, 100), Vector(100, 0.f), 0.1f, 1, false);

	m_pAnimator->Play(L"IdleRun", false);
	AddComponent(m_pAnimator);


	petState = PetState::IdleRun;

	AddCollider(ColliderType::Rect, Vector(30, 30), Vector(0, 0));
}

void CPet::Update()
{
	m_fSkillTimer += DT;

	if (m_fSkillTimer >= 3)
	{

	}

	m_vecPos.y -= (m_vecPos.y - (playerPosY - 60)) * DT * 3.5;
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

	if (pOtherCollider->GetObjName() == L"��ֹ�")
	{
		Logger::Debug(L"��ֹ� �ı�!");
		score += 1000;
	}

	if (pOtherCollider->GetObjName() == L"����")
	{
		Logger::Debug(L"���� ���� ȹ��!");
		score += 1000;
	}

	if (pOtherCollider->GetObjName() == L"��Ʈ������")
	{
		Logger::Debug(L"������ ȹ��!");
		playerHp += 20;
	}


	if (pOtherCollider->GetObjName() == L"�ڼ�������")
	{
		Logger::Debug(L"�ڼ������� ȹ��!");
		isMagnet = true;
	}

	if (pOtherCollider->GetObjName() == L"�뽬������")
	{
		Logger::Debug(L"�뽬������ ȹ��!");
		isDash = true;
	}

}

void CPet::OnCollisionStay(CCollider* pOtherCollider)
{


	if (pOtherCollider->GetObjName() == L"����")
	{
	
	}

}

void CPet::OnCollisionExit(CCollider* pOtherCollider)
{
}
