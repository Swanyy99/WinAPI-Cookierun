#pragma once
#include "CScene.h"
#include "CImages.h"

class CPlayer;
class CPet;
class CImages;

class CSceneStage01 : public CScene
{
public:
	CSceneStage01();
	virtual ~CSceneStage01();

private:
	CPlayer* pPlayer;
	CPet* pPet;


	CImage* slideImage;
	CImage* jumpImage;

	CImages* CookierunTitle;
	CImages* HPIcon;
	CImages* HPBackBar;
	CImages* HPBar;
	CImages* HPProgressBar;
	CImages* HPEffect;

	CImage* Tear;

	CButton* RetryButton;
	CButton* ResumeButton;
	CButton* QuitButton;

	CImages* PauseImage;
	CImages* FailImage;
	CImages* SlideButtonImage;
	CImages* JumpButtonImage;

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
