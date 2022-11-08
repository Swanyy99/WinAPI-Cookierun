#pragma once
#include "CGameObject.h"
class CObstacleSky : public CGameObject
{
public:
	CObstacleSky();
	virtual ~CObstacleSky();

private:
	CAnimator* m_pAnimators;
	CImage* m_pObstacle1Image;

	CImage* m_pImg;

	Vector m_vecDir;
	float m_fVelocity;

	wstring obstacleImage;

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

