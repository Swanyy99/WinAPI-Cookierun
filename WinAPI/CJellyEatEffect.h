#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

class CJellyEatEffect : public CGameObject
{
public:
	CJellyEatEffect();
	virtual ~CJellyEatEffect();

private:
	CAnimator* m_pAnimatorJellyEatEffect;
	CImage* m_pJellyEatEffect;

	wstring JellyEatEffect;

	Vector m_vecDir;
	float m_fVelocity;

	float effectTimer;

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();


	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

public:
	void SetDir(Vector dir);
	void SetVelocity(float velocity);
};

