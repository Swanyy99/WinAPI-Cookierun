#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

class CPetMissile : public CGameObject
{
public:
	CPetMissile();
	virtual ~CPetMissile();

private:
	CAnimator* m_pAnimatorPetMissile;

	CImage* m_pPetMissileImage;

	wstring PetMissileImage;

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


