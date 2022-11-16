#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

class CCoin : public CGameObject
{
public:
	CCoin();
	virtual ~CCoin();

private:
	CAnimator* m_pAnimatorCoin;

	CImage* m_pCoinImage;

	wstring CoinImage;

	Vector m_vecDir;
	float m_fVelocity;


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


