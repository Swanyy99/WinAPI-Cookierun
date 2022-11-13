#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

class CPetMissile2 : public CGameObject
{
public:
	CPetMissile2();
	virtual ~CPetMissile2();

private:
	CAnimator* m_pAnimatorPetMissile2;

	CImage* m_pPetMissile2Image;

	wstring PetMissile2Image;

	Vector m_vecDir;
	float m_fVelocity;

	float m_fWaterTimer;


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



