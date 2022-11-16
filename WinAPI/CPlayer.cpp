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
#include "CGameObject.h"
#include "CDashFireEffect.h"
#include "CScene.h"
#include "CRespawnEffect.h"

#include "CPet3.h"

bool isMagnet;
bool isDash;
bool isHurt;
bool realHurt;

bool revive;

bool isJumping;
bool isJumpUp;
bool isSliding;
bool isDead;
wstring motion;
float playerHp;

float playerPosX;
float playerPosY;
float m_fDashTimer;
float m_fHurtTimer;

extern int myJem;
extern int myCoin;

extern int score;
extern wstring ScreenScore;
extern bool pause;
extern bool skillOn3;

extern int JemADD;
extern int CoinADD;

CPlayer::CPlayer()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Player;
	m_strName = L"�÷��̾�";

	m_pIdleImage = nullptr;
	m_pIdleDashImage = nullptr;
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
	realHurt = false;
	m_fJumpTimer = 0.4;
	m_fHurtTimer = 2.5;
	m_fMagnetTimer = 4;
	m_fDashTimer = 4;
	m_fDashEffectTimer = 0.3;

	MagnetBlueImage = nullptr;
	isMagnet = false;
	revive = false;

	playerHp = 100;

	isJumpUp = true;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	m_pAnimator = new CAnimator;
	
	// �⺻ ��Ű ��� �̹�����
	m_pIdleImage = RESOURCE->LoadImg(L"PlayerAnimation", L"Image\\BraveCookie.png");
	m_pIdleDashImage = RESOURCE->LoadImg(L"PlayerIdleDash", L"Image\\BraveCookie.png");
	m_pJumpImage = RESOURCE->LoadImg(L"PlayerJump", L"Image\\BraveCookie.png");
	m_pSlideImage = RESOURCE->LoadImg(L"PlayerSlide", L"Image\\BraveCookie.png");
	m_pDeathImage = RESOURCE->LoadImg(L"PlayerDeath", L"Image\\BraveCookie.png");

	HurtInvincibilityImage = RESOURCE->LoadImg(L"PlayerInvincibility", L"Image\\HurtInvincibility.png");

	HurtRedImage = RESOURCE->LoadImg(L"HurtRedScreen", L"Image\\HurtRedScreen.png");

	MagnetBlueImage = RESOURCE->LoadImg(L"MagnetBlueImage", L"Image\\MagnetBlueScreen.png");

	m_pAnimator->CreateAnimation(L"IdleRun", m_pIdleImage, Vector(0, 273), Vector(273, 273), Vector(273, 0.f), 0.08f, 4);
	m_pAnimator->CreateAnimation(L"IdleDash", m_pIdleDashImage, Vector(1092, 273), Vector(273, 273), Vector(273, 0.f), 0.06f, 4);

	m_pAnimator->CreateAnimation(L"Jump", m_pJumpImage, Vector(0, 0), Vector(273, 273), Vector(273, 0), 1, 1);
	m_pAnimator->CreateAnimation(L"JumpDown", m_pJumpImage, Vector(2184, 546), Vector(273, 273), Vector(273, 0), 1, 1);
	m_pAnimator->CreateAnimation(L"DoubleJump", m_pJumpImage, Vector(273, 0), Vector(273, 273), Vector(273, 0), 0.08f, 3);

	m_pAnimator->CreateAnimation(L"Slide", m_pJumpImage, Vector(2457, 0), Vector(273, 273), Vector(273, 0.f), 0.1f, 2);


	// �ǰ� �� ������ ��Ű ��� �̹�����
	m_pHurtIdleImage = RESOURCE->LoadImg(L"PlayerHurtAnimation", L"Image\\BraveCookieHurt.png");
	m_pHurtJumpImage = RESOURCE->LoadImg(L"PlayerHurtJump", L"Image\\BraveCookieHurt.png");
	m_pHurtSlideImage = RESOURCE->LoadImg(L"PlayerHurtSlide", L"Image\\BraveCookieHurt.png");
	m_pHurtDeathImage = RESOURCE->LoadImg(L"PlayerHurtDeath", L"Image\\BraveCookieHurt.png");

	m_pAnimator->CreateAnimation(L"HurtIdleRun", m_pHurtIdleImage, Vector(0, 273), Vector(273, 273), Vector(273, 0.f), 0.08f, 4);
	m_pAnimator->CreateAnimation(L"HurtDash", m_pHurtIdleImage, Vector(1092, 273), Vector(273, 273), Vector(273, 0.f), 0.06f, 4);

	m_pAnimator->CreateAnimation(L"HurtJump", m_pHurtJumpImage, Vector(0, 0), Vector(273, 273), Vector(273, 0), 1, 1);
	m_pAnimator->CreateAnimation(L"HurtJumpDown", m_pHurtJumpImage, Vector(2184, 546), Vector(273, 273), Vector(273, 0), 1, 1);
	m_pAnimator->CreateAnimation(L"HurtDoubleJump", m_pHurtJumpImage, Vector(273, 0), Vector(273, 273), Vector(273, 0), 0.08f, 3);

	m_pAnimator->CreateAnimation(L"HurtSlide", m_pHurtJumpImage, Vector(2457, 0), Vector(273, 273), Vector(273, 0.f), 0.1f, 2);


	m_pAnimator->CreateAnimation(L"Death", m_pDeathImage, Vector(2457, 1092), Vector(273, 273), Vector(273, 0.f), 0.1f, 1, false);

	m_pAnimator->Play(L"IdleRun", false);
	AddComponent(m_pAnimator);

	
	playerState = PlayerState::IdleRun;

	DashFireDom = RESOURCE->LoadImg(L"DashFireDom", L"Image\\DashFireDom.png");

	AddCollider(ColliderType::Rect, Vector(70, 120), Vector(10, 70));


	m_fJumpTimer = 0.4;
	m_fHurtTimer = 2.5;
	m_fMagnetTimer = 4;
	m_fDashTimer = 4;
	m_fDashEffectTimer = 0.3;
	isDash = false;
}

void CPlayer::Update()
{

	if (playerState == PlayerState::Slide)
	{
		playerPosX = m_vecPos.x + 80;
		playerPosY = m_vecPos.y + 110;
	}

	else
	{
		playerPosX = m_vecPos.x + 80;
		playerPosY = m_vecPos.y + 70;
	}


	if (pause == false)
	{

		switch (playerState)
		{

		case PlayerState::IdleRun:	// �⺻(�޸��� ��)
			SetColliderSize(Vector(70, 130), Vector(10, 70));

			if (isHurt == false && isDash == false)
				motion = L"IdleRun";
			else if (isDash == false && isHurt == true)
				motion = L"HurtIdleRun";
			else if (isDash == true && isHurt == true)
				motion = L"HurtDash";
			else if (isDash == true)
				motion = L"IdleDash";

			if (BUTTONDOWN(VK_SPACE)) // ����
			{
				playerState = PlayerState::Jump;
			}

			if (BUTTONDOWN(VK_DOWN) || BUTTONDOWN(VK_CONTROL)) // �����̵�
			{
				playerState = PlayerState::Slide;
			}

			if (isSliding == true)
			{
				playerState = PlayerState::Slide;
			}

			break;

		case PlayerState::Jump:	// 1�� ����
			SetColliderSize(Vector(70, 120), Vector(10, 70));

			if (isJumpUp == true)
			{
				if (m_fSpeed < 0)
					isJumpUp = false;

				if (m_fSpeed > 0)
				{

					isJumpUp = true;

					m_fSpeed -= ABSDT * 1200;

					if (isHurt == false)
						motion = L"Jump";
					else
						motion = L"HurtJump";

					m_fJumpTimer -= ABSDT;
					m_vecPos.y -= m_fSpeed * ABSDT;
					
				}
			}


			if (isJumpUp == false)
			{
				isJumpUp = false;

				m_fSpeed += ABSDT * 1200;
				m_vecPos.y += m_fSpeed * ABSDT;

				if (isHurt == false)
					motion = L"JumpDown";
				else
					motion = L"HurtJumpDown";

				if (BUTTONDOWN(VK_SPACE)) // �������� �߿� 2�� ���� ����
				{
					playerState = PlayerState::DoubleJump;
					m_fJumpTimer = 0.25;
					isJumpUp = true;
					m_fSpeed = 900;
					break;
				}
				
			}

			if (BUTTONDOWN(VK_SPACE)) // 2�� ���� ����
			{
				playerState = PlayerState::DoubleJump;
				m_fJumpTimer = 0.25;
				isJumpUp = true;
				m_fSpeed = 900;
				break;
			}

			break;

		case PlayerState::DoubleJump:	// 2�� ����
			SetColliderSize(Vector(70, 120), Vector(10, 70));

			if (isJumpUp == true)
			{
				if (m_fSpeed < 0)
					isJumpUp = false;

				if (m_fSpeed > 0)
				{

					isJumpUp = true;

					m_fSpeed -= ABSDT * 2100;

					if (isHurt == false)
						motion = L"DoubleJump";
					else
						motion = L"HurtDoubleJump";

					m_fJumpTimer -= ABSDT;
					m_vecPos.y -= m_fSpeed * ABSDT;

				}
			}


			if (isJumpUp == false)
			{
				isJumpUp = false;

				m_fSpeed += ABSDT * 2200;
				m_vecPos.y += m_fSpeed * ABSDT;

				if (isHurt == false)
					motion = L"DoubleJump";
				else
					motion = L"HurtDoubleJump";

			}

			break;

		case PlayerState::Slide:	// �����̵�

			SetColliderSize(Vector(120, 65), Vector(10, 100));

			if (isHurt == false)
				motion = L"Slide";
			else
				motion = L"HurtSlide";

			if (BUTTONUP(VK_DOWN) || BUTTONUP(VK_CONTROL)) // ��Ʈ��Ű�� ����
			{
				playerState = PlayerState::IdleRun;
			}

			break;

		case PlayerState::Death:	// ����

			
			if (playerHp <= 0 && isDead == false)
			{
				
				motion = L"Death";
				isDead = true;
				break;
			}
			
			if (playerHp > 0)
			{
				playerState = PlayerState::IdleRun;
				motion = L"IdleRun";
				isDead = false;
				
				m_fSpeed = 500;
				m_vecPos.y = WINSIZEY * 0.65f;
				isJumpUp = true;
				isGround = true;
				isHurt = true;
				isMagnet = true;
				m_fMagnetTimer = 2;
				m_fHurtTimer = 2;

				CRespawnEffect* pRespawnEffect = new CRespawnEffect();
				pRespawnEffect->SetPos(playerPosX, WINSIZEY * 0.68);
				ADDOBJECT(pRespawnEffect);
				
				break;
			}

			break;
		}

		AnimatorUpdate();
	}

	if (playerHp <= 0)
	{
		playerState = PlayerState::Death;
		playerHp = 0;
	}

	if (playerHp > 100)
	{
		playerHp = 100;
	}


	// �ǰ� �� ���� �� ��¦ �����ϴ� ���
	if (isHurt == true && isDead == false)
	{
		m_fHurtTimer -= ABSDT;

		if (realHurt == true)
		{
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
		}

		if (m_fHurtTimer <= 0)
		{
			isHurt = false;
			realHurt = false;
			m_fHurtTimer = 2.5;
		}
	}


	if (isMagnet == true && isDead == false)
	{
		m_fMagnetTimer -= ABSDT;

		if (m_fMagnetTimer <= 0)
		{
			isMagnet = false;
			m_fMagnetTimer = 4;
		}
	}

	if (skillOn3 == true)
	{
		isDash = true;
	}

	if (m_fDashTimer >= 4.1)
	{
		m_fDashTimer = 4;
	}

	if (isDash == true && isDead == false)
	{
		m_fDashTimer -= ABSDT;
		m_fDashEffectTimer += ABSDT;

		if (m_fDashEffectTimer > 0.12)
		{
			m_fDashEffectTimer -= 0.12;
			CDashFireEffect* pDashFireEffect = new CDashFireEffect();
			pDashFireEffect->SetPos(playerPosX - 120, playerPosY);
			ADDOBJECT(pDashFireEffect);
		}




		/*if (skillOn3 == true)
		{
			m_fDashTimer = 4;
			isHurt = false;
			m_fHurtTimer = 2.5;
		}*/

		if (m_fDashTimer <= 0)
		{
			isDash = false;
			isHurt = true;
			m_fHurtTimer = 2.5;
			
		}

	}

}

void CPlayer::Render()
{
	if (isHurt == true && isDead == false)
	{
		// �ǰ� �� ���� �ؽ�Ʈ �̹���
		RENDER->Image(
			HurtInvincibilityImage,
			m_vecPos.x + 11 - HurtInvincibilityImage->GetWidth() * 0.15,
			playerPosY - 95 - HurtInvincibilityImage->GetHeight() * 0.15,
			m_vecPos.x + 11 + HurtInvincibilityImage->GetWidth() * 0.15,
			playerPosY - 95 + HurtInvincibilityImage->GetHeight() * 0.15);

		// �ǰ� �� ȭ�� ������ �׵θ� �̹���
		if (realHurt == true)
		{
			RENDER->Image(
				HurtRedImage,
				-230, -200, WINSIZEX + 230, WINSIZEY + 200);
		}
	}

	// �ڼ� ȭ�� �Ķ��� �׵θ� �̹���
	if (isMagnet == true && isDead == false)
	{
		RENDER->Image(
			MagnetBlueImage,
			-230, -200, WINSIZEX + 230, WINSIZEY + 200);

	}

	// �뽬 �Ҳɵ� �̹���
	if (isDash == true && isDead == false)
	{
		RENDER->Image(
			DashFireDom,
			playerPosX - 110, playerPosY - 75, playerPosX - 10, playerPosY + 70);

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
	Logger::Debug(L"�̻��� �߻�!");

	CMissile* pMissile = new CMissile();
	pMissile->SetPos(m_vecPos.x + 20, m_vecPos.y + 50);
	pMissile->SetDir(Vector(1, 0));
	ADDOBJECT(pMissile);
}

void CPlayer::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�ٴ�")
	{
		isJumpUp = true;
		isGround = true;
		m_fSpeed = 500;
	}

	if (pOtherCollider->GetObjName() == L"��ֹ�" && isHurt == false && isDash == false)
	{
		Logger::Debug(L"�÷��̾ ��ֹ��� ����");
		playerHp -= 20;
		isHurt = true;
		realHurt = true;
	}

	if (pOtherCollider->GetObjName() == L"��ֹ�" && isDash == true)
	{
		Logger::Debug(L"�÷��̾ �뽬�߿� ��ֹ��� �μ�");
		score += 1000;
	}

	if (pOtherCollider->GetObjName() == L"����")
	{
		Logger::Debug(L"���� ���� ȹ��!");
		score += 1000;
	}

	if (pOtherCollider->GetObjName() == L"��")
	{
		Logger::Debug(L"���̾� ȹ��!");
		myJem += 100;
		JemADD += 100;
	}

	if (pOtherCollider->GetObjName() == L"����")
	{
		Logger::Debug(L"���� ȹ��!");
		myCoin += 100;
		CoinADD += 100;
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
		m_fMagnetTimer = 4;
	}

	if (pOtherCollider->GetObjName() == L"�뽬������" && m_fDashTimer != 4)
	{
		Logger::Debug(L"�뽬������ ȹ��!");
		isDash = true;
		m_fDashTimer += 4;
	}

	if (pOtherCollider->GetObjName() == L"�뽬������" && m_fDashTimer == 4)
	{
		Logger::Debug(L"�뽬������ ȹ��!");
		isDash = true;
		m_fDashTimer = 4;
	}

	if (pOtherCollider->GetObjName() == L"�ٴ�" && BUTTONDOWN(VK_CONTROL)) // �����̵�
	{
		playerState = PlayerState::Slide;

	}
	
	if (pOtherCollider->GetObjName() == L"�ٴ�" && BUTTONDOWN(VK_DOWN)) // �����̵�
	{
		playerState = PlayerState::Slide;
	}

	else if (pOtherCollider->GetObjName() == L"�ٴ�")
	{
		playerState = PlayerState::IdleRun;
	}
}

void CPlayer::OnCollisionStay(CCollider* pOtherCollider)
{

	if (pOtherCollider->GetObjName() == L"�ٴ�")
	{
		isGround = true;
		playerState = PlayerState::IdleRun;
		Logger::Debug(L"�÷��̾ ���� ����");
		m_vecPos.y -= 1;
	}

}

void CPlayer::OnCollisionExit(CCollider* pOtherCollider)
{
}
