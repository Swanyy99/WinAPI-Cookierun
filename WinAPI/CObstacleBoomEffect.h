#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

class CObstacleBoomEffect : public CGameObject
{
public:
	CObstacleBoomEffect();
	virtual ~CObstacleBoomEffect();

private:
	CAnimator* m_pAnimatorObstacleBoomEffect;
	CImage* m_pObstacleBoomEffect;

	wstring ObstacleBoomEffect;

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

