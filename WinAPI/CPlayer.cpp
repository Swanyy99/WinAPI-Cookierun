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
bool isDead;
wstring motion;
float playerHp;

extern int score;
extern wstring ScreenScore;
extern bool pause;

CPlayer::CPlayer()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Player;
	m_strName = L"플레이어";

	m_pIdleImage = nullptr;
	m_pJumpImage = nullptr;
	m_pSlideImage = nullptr;
	m_pDeathImage = nullptr;	

	m_pHurtIdleImage = nullptr;
	m_pHurtJumpImage = nullptr;
	m_pHurtSlideImage = nullptr;
	m_pHurtDeathImage = nullptr;

	HurtInvincibilityImage = nullptr;
	HurtRedImage = nullptr;

	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, -1);
	m_bIsMove = false;
	isDead = false;
	isHurt = false;
	m_fJumpTimer = 0.4;
	m_fHurtTimer = 2.5;

	playerHp = 100;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	m_pAnimator = new CAnimator;
	
	// 기본 쿠키 모션 이미지들
	m_pIdleImage = RESOURCE->LoadImg(L"PlayerAnimation", L"Image\\BraveCookie.png");
	m_pJumpImage = RESOURCE->LoadImg(L"PlayerJump", L"Image\\BraveCookie.png");
	m_pSlideImage = RESOURCE->LoadImg(L"PlayerSlide", L"Image\\BraveCookie.png");
	m_pDeathImage = RESOURCE->LoadImg(L"PlayerDeath", L"Image\\BraveCookie.png");

	HurtInvincibilityImage = RESOURCE->LoadImg(L"PlayerInvincibility", L"Image\\HurtInvincibility.png");

	HurtRedImage = RESOURCE->LoadImg(L"HurtRedScreen", L"Image\\HurtRedScreen.png");

	m_pAnimator->CreateAnimation(L"IdleRun", m_pIdleImage, Vector(0, 273), Vector(273, 273), Vector(273, 0.f), 0.08f, 4);
	m_pAnimator->CreateAnimation(L"Dash", m_pIdleImage, Vector(0, 0), Vector(0, 75.f), Vector(84.f, 0.f), 0.05f, 16);

	m_pAnimator->CreateAnimation(L"Jump", m_pJumpImage, Vector(0, 0), Vector(273, 273), Vector(273, 0), 1, 1);
	m_pAnimator->CreateAnimation(L"JumpDown", m_pJumpImage, Vector(2184, 546), Vector(273, 273), Vector(273, 0), 1, 1);
	m_pAnimator->CreateAnimation(L"DoubleJump", m_pJumpImage, Vector(273, 0), Vector(273, 273), Vector(273, 0), 0.1f, 3);

	m_pAnimator->CreateAnimation(L"Slide", m_pJumpImage, Vector(2457, 0), Vector(273, 273), Vector(273, 0.f), 0.1f, 2);


	// 피격 후 반투명 쿠키 모션 이미지들
	m_pHurtIdleImage = RESOURCE->LoadImg(L"PlayerHurtAnimation", L"Image\\BraveCookieHurt.png");
	m_pHurtJumpImage = RESOURCE->LoadImg(L"PlayerHurtJump", L"Image\\BraveCookieHurt.png");
	m_pHurtSlideImage = RESOURCE->LoadImg(L"PlayerHurtSlide", L"Image\\BraveCookieHurt.png");
	m_pHurtDeathImage = RESOURCE->LoadImg(L"PlayerHurtDeath", L"Image\\BraveCookieHurt.png");

	m_pAnimator->CreateAnimation(L"HurtIdleRun", m_pHurtIdleImage, Vector(0, 273), Vector(273, 273), Vector(273, 0.f), 0.08f, 4);
	m_pAnimator->CreateAnimation(L"HurtDash", m_pHurtIdleImage, Vector(0, 0), Vector(0, 75.f), Vector(84.f, 0.f), 0.05f, 16);

	m_pAnimator->CreateAnimation(L"HurtJump", m_pHurtJumpImage, Vector(0, 0), Vector(273, 273), Vector(273, 0), 1, 1);
	m_pAnimator->CreateAnimation(L"HurtJumpDown", m_pHurtJumpImage, Vector(2184, 546), Vector(273, 273), Vector(273, 0), 1, 1);
	m_pAnimator->CreateAnimation(L"HurtDoubleJump", m_pHurtJumpImage, Vector(273, 0), Vector(273, 273), Vector(273, 0), 0.1f, 3);

	m_pAnimator->CreateAnimation(L"HurtSlide", m_pHurtJumpImage, Vector(2457, 0), Vector(273, 273), Vector(273, 0.f), 0.1f, 2);




	m_pAnimator->CreateAnimation(L"Death", m_pDeathImage, Vector(2457, 1092), Vector(273, 273), Vector(273, 0.f), 0.1f, 1, false);

	m_pAnimator->Play(L"IdleRun", false);
	AddComponent(m_pAnimator);

	
	playerState = PlayerState::IdleRun;

	AddCollider(ColliderType::Rect, Vector(70, 120), Vector(10, 70));
}

void CPlayer::Update()
{

	if (pause == false)
	{

		if (playerHp <= 0)
		{
			playerState = PlayerState::Death;
		}

		switch (playerState)
		{

		case PlayerState::IdleRun:	// 기본(달리기 중)
			SetColliderSize(Vector(70, 130), Vector(10, 70));

			if (isHurt == false)
				motion = L"IdleRun";
			else
				motion = L"HurtIdleRun";

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
				if (isHurt == false)
					motion = L"Jump";
				else
					motion = L"HurtJump";

				m_fJumpTimer -= DT;
				m_vecPos.y -= m_fSpeed * DT * 1.9;
			}

			if (m_fJumpTimer < 0)
			{
				m_vecPos.y += m_fSpeed * DT * 2.3;

				if (isHurt == false)
					motion = L"JumpDown";
				else
					motion = L"HurtJumpDown";

				if (BUTTONDOWN(VK_SPACE)) // 내려오는 중에 2단 점프 진입
				{
					playerState = PlayerState::DoubleJump;
					m_fJumpTimer = 0.25;
					break;
				}
			}

			if (BUTTONDOWN(VK_SPACE)) // 2단 점프 진입
			{
				playerState = PlayerState::DoubleJump;
				m_fJumpTimer = 0.25;
				break;
			}

			break;



		case PlayerState::DoubleJump:	// 2단 점프
			SetColliderSize(Vector(70, 120), Vector(10, 70));
			if (m_fJumpTimer > 0)
			{
				if (isHurt == false)
					motion = L"DoubleJump";
				else
					motion = L"HurtDoubleJump";

				m_fJumpTimer -= DT;
				m_vecPos.y -= m_fSpeed * DT * 3.1;
			}

			if (m_fJumpTimer < 0)
			{
				m_vecPos.y += m_fSpeed * DT * 2.3;
			}

			break;

		case PlayerState::Slide:	// 슬라이드

			SetColliderSize(Vector(120, 65), Vector(10, 100));

			if (isHurt == false)
				motion = L"Slide";
			else
				motion = L"HurtSlide";

			if (BUTTONUP(VK_CONTROL)) // 컨트롤키를 떼면
			{
				playerState = PlayerState::IdleRun;
			}

			break;

		case PlayerState::Death:	// 죽음

			motion = L"Death";
			isDead = true;

		}

		AnimatorUpdate();
	}

	if (playerHp <= 0)
	{
		playerHp = 0;
		playerState = PlayerState::Death;
	}


	// 피격 후 무적 및 살짝 주춤하는 모션
	if (isHurt == true && isDead == false)
	{
		m_fHurtTimer -= DT;

		if (m_fHurtTimer <= 2.5 && m_fHurtTimer >= 2.44)
		{
			m_vecPos.x -= 0.1;
			m_vecPos.y -= 0.2;
		}

		if (m_fHurtTimer < 2.4 && m_fHurtTimer >= 2.34)
		{
			m_vecPos.x += 0.1;
			m_vecPos.y += 0.2;
		}

		if (m_fHurtTimer <= 0)
		{
			isHurt = false;
			m_fHurtTimer = 2.5;
		}
	}

	

	
}

void CPlayer::Render()
{
	if (isHurt == true && isDead == false)
	{
		// 피격 시 무적 텍스트 이미지
		RENDER->Image(
			HurtInvincibilityImage,
			m_vecPos.x - HurtInvincibilityImage->GetWidth() * 0.25,
			m_vecPos.y - 30 - HurtInvincibilityImage->GetHeight() * 0.25,
			m_vecPos.x + HurtInvincibilityImage->GetWidth() * 0.25,
			m_vecPos.y - 30 + HurtInvincibilityImage->GetHeight() * 0.25);

		// 피격 시 붉은색 테두리 이미지
		RENDER->Image(
			HurtRedImage,
			-230, -200, WINSIZEX + 230, WINSIZEY + 200);
	}
}

void CPlayer::Release()
{
}

void CPlayer::AnimatorUpdate()
{
	
	m_pAnimator->Play(motion, false);

}

void CPlayer::CreateMissile()
{

}

void CPlayer::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"바닥")
	{
		isGround = true;
	}

	if (pOtherCollider->GetObjName() == L"장애물" && isHurt == false)
	{
		Logger::Debug(L"플레이어가 장애물에 닿음");
		playerHp -= 20;
		isHurt = true;
	}

	if (pOtherCollider->GetObjName() == L"젤리")
	{
		Logger::Debug(L"젤리 점수 획득!");
		score += 1000;
	}


	if (pOtherCollider->GetObjName() == L"바닥" && BUTTONDOWN(VK_CONTROL)) // 슬라이드
	{
		playerState = PlayerState::Slide;
	}

	else if (pOtherCollider->GetObjName() == L"바닥")
	{
		playerState = PlayerState::IdleRun;
	}
}

void CPlayer::OnCollisionStay(CCollider* pOtherCollider)
{

	/*if (pOtherCollider->GetObjName() == L"GroundTile")
	{
		Logger::Debug(L"플레이어가 땅에 닿음");
		m_vecPos.y -= 1;
		m_fJumpTimer = 0.4;

	}*/

	if (pOtherCollider->GetObjName() == L"바닥")
	{
		isGround = true;
		playerState = PlayerState::IdleRun;
		Logger::Debug(L"플레이어가 땅에 닿음");
		m_vecPos.y -= 1;
		m_fJumpTimer = 0.4;
	}

}

void CPlayer::OnCollisionExit(CCollider* pOtherCollider)
{
}
