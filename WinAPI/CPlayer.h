#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

class CPlayer : public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer();

private:
	CAnimator* m_pAnimator;
	CImage* m_pIdleImage;
	CImage* m_pJumpImage;
	CImage* m_pSlideImage;
	CImage* m_pDeathImage;

	CImage* m_pHurtIdleImage;
	CImage* m_pHurtJumpImage;
	CImage* m_pHurtSlideImage;
	CImage* m_pHurtDeathImage;

	CImage* HurtInvincibilityImage;

	Vector m_vecMoveDir;
	Vector m_vecLookDir;
	bool m_bIsMove;
	bool isGround;
	bool isHurt;

	enum class PlayerState { IdleRun, Jump, DoubleJump, Slide, Death };
	PlayerState playerState;

	float m_fSpeed = 200.0f;
	float m_fJumpTimer;
	float m_fHurtTimer;

	

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();
	void CreateMissile();

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};