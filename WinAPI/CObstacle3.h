#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

class CObstacle3 : public CGameObject
{
public:
	CObstacle3();
	virtual ~CObstacle3();

private:
	CAnimator* m_pAnimatorObstacle3;

	CImage* m_pObstacle3Image;

	wstring Obstacle3Image;

	Vector m_vecDir;
	float m_fVelocity;

	float m_fJemBoxDropTimer;


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



