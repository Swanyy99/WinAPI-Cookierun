#pragma once
#include "CTile.h"
class CGroundTile : public CTile
{
public:
	CGroundTile();
	virtual ~CGroundTile();

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	void OnCollisionEnter(CCollider* pOther) override;
	void OnCollisionStay(CCollider* pOther) override;
	void OnCollisionExit(CCollider* pOther) override;
};

