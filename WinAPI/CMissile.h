#pragma once
#include "CGameObject.h"

class CImage;

class CMissile : public CGameObject
{
public:
	CMissile();
	virtual ~CMissile();

private:
	Vector m_vecDir;
	float m_fVelocity;
	CImage* missileImage;

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