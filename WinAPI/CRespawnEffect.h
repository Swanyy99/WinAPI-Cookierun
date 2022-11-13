#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

class CRespawnEffect : public CGameObject
{
public:
	CRespawnEffect();
	virtual ~CRespawnEffect();

private:
	CAnimator* m_pAnimatorRespawnEffect;
	CImage* m_pRespawnEffect;

	wstring RespawnEffect;

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


