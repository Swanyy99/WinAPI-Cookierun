#pragma once
#include "CGameObject.h"
class CBackground : public CGameObject
{
public:
	CBackground();
	virtual ~CBackground();

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