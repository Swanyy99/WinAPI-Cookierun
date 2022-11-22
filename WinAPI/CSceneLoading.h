#pragma once
#include "CScene.h"

class CSceneLoading : public CScene
{
public:
	CSceneLoading();
	virtual ~CSceneLoading();

private:
	CImage* LoadingBackgroundImage;

	float m_fLoadingTimer;

private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};