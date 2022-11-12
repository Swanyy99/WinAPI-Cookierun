#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

class CPet : public CGameObject
{
public:
	CPet();
	virtual ~CPet();

private:
	CAnimator* m_pAnimatorp;
	CImage* m_pPetImage;
	CImage* m_pSkillImage;
	CImage* m_pDeathImage;

	Vector m_vecMoveDir;
	Vector m_vecLookDir;

	enum class PetState { IdleRun, Skill };
	PetState petState;

	float m_fSpeed = 200.0f;
	float m_fSkillCooltimeTimer;
	float m_fSkillTimer;


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