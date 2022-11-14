#pragma once
#include "CGameObject.h"
class CFloor : public CGameObject
{
public:
	CFloor();
	virtual ~CFloor();

private:
	Vector m_vecDir;
	float m_fVelocity;
	float m_fX;

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