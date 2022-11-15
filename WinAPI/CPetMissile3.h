#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

class CPetMissile3 : public CGameObject
{
public:
	CPetMissile3();
	virtual ~CPetMissile3();

private:
	CAnimator* m_pAnimatorPetMissile3;

	CImage* m_pPetMissile3Image;

	wstring PetMissile3Image;

	Vector m_vecDir;
	float m_fVelocity;

	float m_fShieldTimer;


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




