#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

class CJelly1 : public CGameObject
{
public:
	CJelly1();
	virtual ~CJelly1();

private:
	CAnimator* m_pAnimatorJelly;
	CImage* m_pObstacle1Image;

	CImage* m_pJellyImage;

	wstring jellyImage;

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

