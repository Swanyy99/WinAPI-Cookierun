#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

class CPet2 : public CGameObject
{
public:
	CPet2();
	virtual ~CPet2();

private:
	CAnimator* m_pAnimatorp2;
	CImage* m_pPetImage2;
	CImage* m_pSkillImage;

	Vector m_vecMoveDir;
	Vector m_vecLookDir;

	enum class PetState { IdleRun, Skill };
	PetState petState;

	float m_fSpeed = 200.0f;
	float m_fSkillCooltimeTimer;
	float m_fSkillTimer;
	float m_fSkillTicTimer;

	int skillNum;


private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};
