#pragma once
#include "CGameObject.h"
class CBottomCloud : public CGameObject
{
public:
	CBottomCloud();
	virtual ~CBottomCloud();

private:
	Vector m_vecDir;
	float m_fVelocity;

	CImage* m_pImg;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;

public:
	void SetDir(Vector dir);
	void SetVelocity(float velocity);
};