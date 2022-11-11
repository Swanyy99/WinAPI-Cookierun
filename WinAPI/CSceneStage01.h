#pragma once
#include "CScene.h"

class CPlayer;
class CPet;

class CSceneStage01 : public CScene
{
public:
	CSceneStage01();
	virtual ~CSceneStage01();

private:
	CPlayer* pPlayer;
	CPet* pPet;

	CImage* CookierunTitle;

	CImage* pauseImage;
	CImage* failImage;
	CImage* slideImage;
	CImage* jumpImage;

	CImage* HPIcon;
	CImage* HPBackBar;
	CImage* HPBar;
	CImage* HPProgressBar;
	CImage* HPEffect;

	CImage* Tear;

	float obstacleTimer;
	float HpTimer;


public:



private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
