#include "framework.h"
#include "CPlayer.h"

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

bool isJumping;
bool isSliding;
wstring motion;

CPlayer::CPlayer()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Player;
	m_strName = L"플레이어";

	m_pIdleImage = nullptr;
	m_pJumpImage = nullptr;
	m_pSlideImage = nullptr;

	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_bIsMove = false;
	m_fJumpTimer = 0.4;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	m_pIdleImage = RESOURCE->LoadImg(L"PlayerAnimation", L"Image\\BraveCookie.png");
	m_pJumpImage = RESOURCE->LoadImg(L"PlayerJump", L"Image\\BraveCookie.png");
	m_pSlideImage = RESOURCE->LoadImg(L"PlayerSlide", L"Image\\BraveCookie.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IdleRun", m_pIdleImage, Vector(0, 273), Vector(273, 273), Vector(273, 0.f), 0.08f, 4);
	m_pAnimator->CreateAnimation(L"Dash", m_pIdleImage, Vector(0, 0), Vector(0, 75.f), Vector(84.f, 0.f), 0.05f, 16);

	m_pAnimator->CreateAnimation(L"Jump", m_pJumpImage, Vector(0, 0), Vector(273, 273), Vector(273, 0), 1, 1);
	m_pAnimator->CreateAnimation(L"JumpDown", m_pJumpImage, Vector(2184, 546), Vector(273, 273), Vector(273, 0), 1, 1);
	m_pAnimator->CreateAnimation(L"DoubleJump", m_pJumpImage, Vector(273, 0), Vector(273, 273), Vector(273, 0), 0.1f, 3);

	m_pAnimator->CreateAnimation(L"Slide", m_pJumpImage, Vector(2457, 0), Vector(273, 273), Vector(273, 0.f), 0.1f, 2);

	m_pAnimator->Play(L"IdleRun", false);
	AddComponent(m_pAnimator);

	
	playerState = PlayerState::IdleRun;

	AddCollider(ColliderType::Rect, Vector(70, 120), Vector(10, 70));
}

void CPlayer::Update()
{

	switch (playerState)
	{

	case PlayerState::IdleRun:	// 기본(달리기 중)
		SetColliderSize(Vector(70, 130), Vector(10, 70));
		motion = L"IdleRun";
		//RemoveCollider();

		if (BUTTONDOWN(VK_SPACE)) // 점프
		{
			playerState = PlayerState::Jump;
		}

		if (BUTTONDOWN(VK_CONTROL)) // 슬라이드
		{
			playerState = PlayerState::Slide;
		}

		break;

	case PlayerState::Jump:	// 1단 점프
		SetColliderSize(Vector(70, 120), Vector(10, 70));
		if (m_fJumpTimer > 0)
		{
			motion = L"Jump";

			m_fJumpTimer -= DT;
			m_vecPos.y -= m_fSpeed * DT * 1.6;
		}

		if (m_fJumpTimer < 0)
		{
			m_vecPos.y += m_fSpeed * DT * 2.3;
			motion = L"JumpDown";

			if (BUTTONDOWN(VK_SPACE)) // 2단 점프
			{
				playerState = PlayerState::DoubleJump;
				m_fJumpTimer = 0.2;
				break;
			}
		}

		if (BUTTONDOWN(VK_SPACE)) // 2단 점프
		{
			playerState = PlayerState::DoubleJump;
			m_fJumpTimer = 0.2;
			break;
		}

		break;

		

	case PlayerState::DoubleJump:	// 2단 점프
		SetColliderSize(Vector(70, 120), Vector(10, 70));
		if (m_fJumpTimer > 0)
		{
			motion = L"DoubleJump";
			m_fJumpTimer -= DT;
			m_vecPos.y -= m_fSpeed * DT * 3.2;
		}

		if (m_fJumpTimer < 0)
		{
			m_vecPos.y += m_fSpeed * DT * 2.3;
		}

		break;

	case PlayerState::Slide:	// 슬라이드

		SetColliderSize(Vector(120, 65), Vector(10, 100));

		motion = L"Slide";

		if (BUTTONUP(VK_CONTROL)) // 슬라이드
		{
			playerState = PlayerState::IdleRun;
		}

		break;



	}


	//if (BUTTONDOWN(VK_SPACE))
	//{
	//	CreateMissile();
	//}

	AnimatorUpdate();
}

void CPlayer::Render()
{
}

void CPlayer::Release()
{
}

void CPlayer::AnimatorUpdate()
{
	//if (m_vecMoveDir.Length() > 0)
	//m_vecLookDir = m_vecMoveDir;


	m_pAnimator->Play(motion, false);
}

void CPlayer::CreateMissile()
{
	Logger::Debug(L"미사일 생성");

	CMissile* pMissile = new CMissile();
	pMissile->SetPos(m_vecPos);
	pMissile->SetDir(Vector(1, 0));
	ADDOBJECT(pMissile);

	CMissile* pMissile1 = new CMissile();
	pMissile1->SetPos(m_vecPos);
	pMissile1->SetDir(Vector(1, -1));
	ADDOBJECT(pMissile1);

	CMissile* pMissile2 = new CMissile();
	pMissile2->SetPos(m_vecPos);
	pMissile2->SetDir(Vector(1, 1));
	ADDOBJECT(pMissile2);

	CMissile* pMissile3 = new CMissile();
	pMissile3->SetPos(m_vecPos);
	pMissile3->SetDir(Vector(3, 1));
	ADDOBJECT(pMissile3);

	CMissile* pMissile4 = new CMissile();
	pMissile4->SetPos(m_vecPos);
	pMissile4->SetDir(Vector(3, -1));
	ADDOBJECT(pMissile4);
}

void CPlayer::OnCollisionEnter(CCollider* pOtherCollider)
{
	isGround = true;

	

	if (BUTTONDOWN(VK_CONTROL)) // 슬라이드
	{
		playerState = PlayerState::Slide;
	}

	else
	{
		playerState = PlayerState::IdleRun;
	}
}

void CPlayer::OnCollisionStay(CCollider* pOtherCollider)
{
	isGround = true;
	playerState = PlayerState::IdleRun;

	if (pOtherCollider->GetObjName() == L"GroundTile")
	{
		Logger::Debug(L"플레이어가 땅에 닿음");
		m_vecPos.y -= 1;
		m_fJumpTimer = 0.4;

	}

	if (pOtherCollider->GetObjName() == L"바닥")
	{
		Logger::Debug(L"플레이어가 땅에 닿음");
		m_vecPos.y -= 1;
		m_fJumpTimer = 0.4;
	}
}

void CPlayer::OnCollisionExit(CCollider* pOtherCollider)
{
}
