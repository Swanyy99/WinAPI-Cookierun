#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

class CObstacle2 : public CGameObject
{
public:
	CObstacle2();
	virtual ~CObstacle2();

private:
	CAnimator* m_pAnimatorObstacle2;

	CImage* m_pObstacle2Image;

	wstring Obstacle2Image;

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


