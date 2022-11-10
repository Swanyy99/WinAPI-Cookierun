#pragma once
#include "CGameObject.h"

class CImage;

class CDashFireEffect : public CGameObject
{
public:
	CDashFireEffect();
	virtual ~CDashFireEffect();

private:
	Vector m_vecDir;
	float m_fVelocity;
	CImage* DashEffectImage;

	float m_fEffectRemoveTimer;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

public:
	void SetDir(Vector dir);
	void SetVelocity(float velocity);
};