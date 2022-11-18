#pragma once
#include "CScene.h"

class CSceneTitle : public CScene
{
public:
	CSceneTitle();
	virtual ~CSceneTitle();

private:
	CImage* TitleBackgroundImage;

	CSound* pSound = RESOURCE->LoadSound(L"TitleScene1", L"Sound\\TitleScene.wav");

private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
